//377. Combination Sum IV
//https://www.youtube.com/watch?v=JyNRAEuPxT0&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=27

#include <iostream>
#include <vector>

using namespace std;

int combinationSum4(vector<int>& nums, int target){
  vector<int> dp(target+1, 0);
  dp[0] = 1;
  for(int i=1; i<= target; i++){
    for(int num: nums){
      if(num<=i){
        dp[i] += dp[i-num];
      }
    }
  }
  return dp[target];
}

int main (int argc, char *argv[]) {
  vector<int> input = {1, 2, 3};
  int output = combinationSum4(input, 4);
  cout << "output: " << output << endl;
  return 0;
}
