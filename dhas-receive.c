#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void sleep_ms(int milliseconds)
{
    // Convert milliseconds to microseconds
    usleep(milliseconds * 1000);
}

long millis(){
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec*1000)+(ts.tv_nsec/1000000);
}

enum{
  HEADER1,
  HEADER2,
  LENGTH,
  PAYLOAD,
  CHECK
};

enum{
  DRIVE_STATUS=0x21,
  DRIVE_DATA,
  BATTERY_INFO,
  CELL_VOLTAGE
};

typedef struct{ // 0-normal, 1-fault
  uint8_t offline_fault  :1;
  uint8_t overcurrent  :1;
  uint8_t overvoltage  :1;
  uint8_t undervoltage :1;
  uint8_t overheating  :1;
}DriveStatusBits;

struct{
  union{
    uint8_t left_front_wheel;
    DriveStatusBits lf_bits;
  };
  union{
    uint8_t right_front_wheel;
    DriveStatusBits rf_bits;
  };
  union{
    uint8_t left_rear_wheel;
    DriveStatusBits lr_bits;
  };
  union{
    uint8_t right_rear_wheel;
    DriveStatusBits rr_bits;
  };
}DriveStatus;//0 left front; 1 right front; 2 left rear; 3 right rear
                
struct{
  int vehicle_running_speed;  // Unit mm/s
  int vehicle_steering_speed; // Unit mrad/s
  int left_wheel_speed;       // Unit mm/s
  int right_wheel_speed;      // Unit mm/s
  int left_wheel_mileage;     // Unit mm
  int right_wheel_mileage;    // Unit mm
}DriveData;

struct{
  float total_voltage; //Accuracy 0.01
  float total_current; //Accuracy 0.01
  uint8_t remaining_power;
  union{
    uint8_t failure_alarm;
    struct{
      uint8_t offline_fault :1;
    };
  };
}BatteryInfo;

int main(int argc, char *argv[])
{
    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;

  // Read in existing settings, and handle any error
  if(tcgetattr(serial_port, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
  }

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B115200);
  cfsetospeed(&tty, B115200);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
  }

  printf("Serial initialized, start sending\n");

  long start = millis();
  uint8_t byte;
  uint8_t bytes[30];
  uint8_t state=HEADER1;
  uint8_t remaining;
  uint8_t xor;
  while(1){
    /*
    long current = millis();
    if(current-start>=20){
        start = current;
        uint8_t msg[13];
        msg[0] = 0xAA; //Head 1
        msg[1] = 0x55; //Head 2
        msg[2] = 9;    //length
        msg[3] = 0x02; //Uid
        memcpy(&msg[4], &linear, 4);
        memcpy(&msg[8], &angular, 4);
        uint8_t checksum = msg[2];
        for(int i = 3; i<12; i++){
          checksum ^= msg[i];
        }
        msg[12] = checksum;
        write(serial_port, msg, 13);
    }
    */
      if(read(serial_port, &byte, 1)){
        switch(state){
          case HEADER1:
            if(byte==0xAA)
              state = HEADER2;
            break;
          case HEADER2:
            if(byte==0x55)
              state = LENGTH;
            else
              state = HEADER1;
            break;
          case LENGTH:
            bytes[0] = byte;
            remaining = byte;
            xor = byte;
            state = PAYLOAD;
            break;
          case PAYLOAD:;
            uint8_t total = bytes[0];;
            bytes[1+total-remaining] = byte;
            xor ^= byte;
            remaining --;
            if(remaining==0)
              state = CHECK;
            break;
          case CHECK:
            if(byte == xor){
              switch(bytes[1]){//Uid
                case DRIVE_STATUS:
                  DriveStatus.left_front_wheel  = bytes[2];
                  DriveStatus.right_front_wheel = bytes[3];
                  DriveStatus.left_rear_wheel   = bytes[4];
                  DriveStatus.right_rear_wheel  = bytes[5];
                  printf("_____Drive Status_____\n");
                  printf("Left  front: 0b "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bytes[2]));
                  printf("Right front: 0b "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bytes[3]));
                  printf("Left   rear: 0b "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bytes[4]));
                  printf("Right  rear: 0b "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bytes[5]));
                  break;
                case DRIVE_DATA:
                  DriveData.vehicle_running_speed  = *((int *)&bytes[2]); //inference 4 bytes
                  DriveData.vehicle_steering_speed = *((int *)&bytes[6]); //inference 4 bytes
                  DriveData.left_wheel_speed       = *((int *)&bytes[10]); //inference 4 bytes
                  DriveData.right_wheel_speed      = *((int *)&bytes[14]); //inference 4 bytes
                  DriveData.left_wheel_mileage     = *((int *)&bytes[18]); //inference 4 bytes
                  DriveData.right_wheel_mileage    = *((int *)&bytes[22]); //inference 4 bytes
                  printf("_____Drive Data_____\n");
                  printf("running speed      : %d mm/s\n",   DriveData.vehicle_running_speed);
                  printf("steering speed     : %d mrad/s\n", DriveData.vehicle_steering_speed);
                  printf("left wheel speed   : %d mm/s\n",   DriveData.left_wheel_speed);
                  printf("right wheel speed  : %d mm/s\n",   DriveData.right_wheel_speed);
                  printf("left wheel mileage : %d mm\n",     DriveData.left_wheel_mileage);
                  printf("right wheel mileage: %d mm\n",     DriveData.right_wheel_mileage);
                  break;
                case BATTERY_INFO:
                  BatteryInfo.total_voltage = (float)(*((uint16_t *)&bytes[2]))/100.0;
                  BatteryInfo.total_current = (float)(*((uint16_t *)&bytes[4]))/100.0;
                  BatteryInfo.remaining_power = bytes[6];
                  BatteryInfo.failure_alarm = bytes[7];
                  printf("_____Battery Info_____\n");
                  printf("Total voltage   : %f V\n",   BatteryInfo.total_voltage);
                  printf("Total current   : %f A\n",   BatteryInfo.total_current);
                  printf("Remaining power : %d %%\n",   BatteryInfo.remaining_power);
                  break;
                default:
                  printf("UID not match\n");
                  break;
              }
            }
            state = HEADER1;
            memset(bytes, 0, 30);
            break;
        }
        
      }

  // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.

  }

  close(serial_port);
  return 0;
}
