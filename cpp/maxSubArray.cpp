#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// Kadane's Algorithm
int maxSubArray(vector<int> &nums) {
  int max_ending_here = nums[0], max_so_far = nums[0];
  int start = 0, end = 0;
  for (int i = 1; i < nums.size(); i++) {
    //max_ending_here = max(nums[i], max_ending_here+nums[i]);
    if(nums[i] > max_ending_here+nums[i]){
      max_ending_here = nums[i];
      start = i;
    }else{
      max_ending_here = max_ending_here+nums[i];
    }

    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
      end = i;
    }
    
  }

  // Extract the subarray
  vector<int> subarray(nums.begin() + start, nums.begin() + end + 1);
  cout << "[";
  for (auto v : subarray)
    cout << v << ", ";
  cout << "]" << endl;

  cout << "max sum: " << max_so_far << endl;
  return max_so_far;
}

int main(int argc, char *argv[]) {
  vector<int> input = {5, 4, -1, 7, 8};
  //vector<int> input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int output = maxSubArray(input);
  return 0;
}
