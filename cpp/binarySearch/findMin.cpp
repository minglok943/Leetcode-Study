#include <iostream>
#include <vector>

using namespace std;

//leetcode 153; find minimum in rotated sorted array
//
int findMin(vector<int> &nums){
  int lowIndex = 0;
  int highIndex = nums.size()-1;

  while(lowIndex<highIndex){
    int mid = lowIndex + (highIndex-lowIndex)/2;
    //use Math.floor(low + (high-low)/2 ) in javascript 
    //use int( low + (high-low)/2 ) in python
    //because in c, variable of int type will auto change 1.5 to 1
    if(nums[mid] > nums[highIndex]){
      lowIndex = mid+1;
    }else{
      highIndex = mid;
    }
  }

  return nums[lowIndex];
}

int main (int argc, char *argv[]) {
  vector<int> input = {11, 13, 15, 17};
  int output = findMin(input);
  cout << "output: " << output << endl;
  return 0;
}
