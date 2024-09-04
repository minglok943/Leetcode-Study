//https://www.youtube.com/watch?v=l0o5w_h7a8I&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=26
//300 Longest increasing subsequence
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int lengthLIS(vector<int>& nums){
  vector<int> dp(nums.size(), 1);
  /*
  *      2, 5, 3, 7, 101
  * dp   1, 2, 2, 3, 4
  *
  */
  for(int i=1; i<nums.size(); i++){
    for(int j=0; j<i; j++){
      if(nums[i] > nums[j]){
        dp[i] = max(dp[i], dp[j]+1);
      }
    }
  }
  return *max_element(dp.begin(), dp.end());
}

int main (int argc, char *argv[]) {
  vector<int> input = {10, 9, 2, 5, 3, 7, 101, 18};
  int output = lengthLIS(input);
  cout << "length: " << output << endl;
  return 0;
}
