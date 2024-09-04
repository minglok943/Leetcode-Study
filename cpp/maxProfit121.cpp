#include <climits>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
int maxProfit(vector<int>& nums){
  /*
  *   Greedy algorithm
  *   loop , keep track min 
  */
  int maxProfit = 0;
  int minPrice = INT_MAX;

  for (int i=0; i<nums.size(); i++) {
    if(nums[i]<minPrice){
      minPrice = nums[i];
    }else if(nums[i] - minPrice > maxProfit){
      maxProfit = nums[i] - minPrice;
    }
  }
  return maxProfit;
}

int main (int argc, char *argv[]) {
  vector<int> prices = {7,1,5,3,6,4};
  cout << "Max profit: " << maxProfit(prices) << endl;
  return 0;
}
