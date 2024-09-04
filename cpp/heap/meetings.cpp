//252 Meeting Rooms
//https://www.youtube.com/watch?v=TEeiVVVTzOE&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=23

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//times = [[start, end], [start, end]]
bool canAttendAll(vector<vector<int>>& times){
  sort(times.begin(), times.end());
  int latest=-1;
  for(auto& time: times){
    if(latest!=-1){
      if(time[0]>=latest){
        latest = time[1];
      }else{
        return false;
      }
    }else{
      latest = time[1];
    }
  }
  if(latest != -1){
    return true;
  }else{
    return false;
  }
}

int main (int argc, char *argv[]) {
  vector<vector<int>> times = {{2, 4}, {1, 3}, {7, 10}};
  bool output = canAttendAll(times);
  cout << "can attend all : " << output << endl;
  return 0;
}
