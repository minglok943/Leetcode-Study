#include <iostream>
#include <vector>

using namespace std;

bool canJump(vector<int>& nums){
  int last = nums.size()-1;
  for(int i=nums.size()-2; i>=0; i--){
    if(nums[i]+i >= last){
      last = i;
    }
  }
  return (last==0);
}

int main (int argc, char *argv[]) {
  vector<int> input = {4, 3, 2, 1, 1, 1};
  bool output = canJump(input);

  cout << "output : " << output << endl;
  return 0;
}
