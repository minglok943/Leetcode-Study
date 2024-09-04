//198 rob interval house with most money
//
#include <iostream>
#include <vector>

using namespace std;
int rob(vector<int>& nums){
  int prev1=0, prev2=0;
  int n = nums.size();
  if(n==0){
    return 0;
  }
  if(n == 1){
    return nums[1];
  }
  //important
  for(int num: nums){
    int temp = prev1;
    prev1 = max(prev2+num, prev1);
    prev2 = temp;
  }
  return prev1;
}

int main (int argc, char *argv[]) {
  vector<int> input = {2, 7, 9, 3, 1, 3};
  int output = rob(input);
  cout << "output : " << output << endl;
  return 0;
}
