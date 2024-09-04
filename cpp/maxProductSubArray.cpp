#include <iostream>
#include <vector>

using namespace std;

int maxProductSubArray(vector<int> &nums){
  int maxProduct = nums[0];
  int minProduct = nums[0];
  int output = nums[0];

  for(int i=1; i<nums.size(); i++){
    if(nums[i] < 0) swap(maxProduct, minProduct);
    maxProduct = max(nums[i], maxProduct*nums[i]);
    minProduct = min(nums[i], minProduct*nums[i]);
    output = max(output, maxProduct);
  }
  return output;
}

int main (int argc, char *argv[]) {
  vector<int> input = {2, 3, -2, 4};
  int output = maxProductSubArray(input);
  cout << "output: " << output << endl;
  return 0;
}
