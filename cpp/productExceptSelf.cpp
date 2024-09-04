#include <iostream>
#include <vector>
using namespace std;
//238 Product except self
//
// Time complexity O(n), Space Complexity O(n)
vector<int> productExceptSelf(vector<int>& nums){
  vector<int> output;

  vector<int> left(nums.size(), 1); //initialize all to 1
  vector<int> right(nums.size(), 1);

  /*
   * prefix array technique but not inclusive
   * [1, 2, 3, 4] nums
   * [1, 1, 1, 1] left
   * [1, 1, 1, 1] i = 1
   * [1, 1, 2, 1] i = 2
   * [1, 1, 2, 6] i = 3
  */
  for(int i=1; i < nums.size(); i++){ 
    // i start from 1 because not inclusive
    left[i] = left[i-1] * nums [i-1];
  }

  /*
   * [1, 2, 3, 4] nums
   * [1, 1, 1, 1] right
   * [1, 1, 4, 1] i = 2
   * [1, 12, 4, 1] i = 1
   * [24, 12, 4, 1] i = 0
  */
  for(int i=nums.size()-2; i <= 0; i--){
    right[i]  = right[i+1] * nums[i+1];
  }

  for(int i=0; i<nums.size(); i++){
    output[i] = left[i] * right[i];
  }
  return output;
}

// Time complexity O(n), Space Complexity O(1)
vector<int> productExceptSelfOptimized(vector<int>& nums){
  vector<int> output(nums.size(), 1);

  /*
   * prefix array technique but not inclusive
   * [1, 2, 3, 4] nums
   * [1, 1, 1, 1] left
   * [1, 1, 1, 1] i = 1
   * [1, 1, 2, 1] i = 2
   * [1, 1, 2, 6] i = 3
  */
  for(int i=1; i < nums.size(); i++){ 
    // i start from 1 because not inclusive
    output[i] = output[i-1] * nums [i-1];
  }
  /* right = 4
    * [1, 1, 8, 6] right = 12
    * [1, 12, 8, 6] right = 24
    * [24, 12, 8, 6]
    */
  int right=nums[nums.size()-1];
  for(int i=nums.size()-2; i>=0; i--){
    output[i] *= right;
    right *= nums[i];
  }
  return output;
}
