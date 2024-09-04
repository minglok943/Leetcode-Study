#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
bool containsDuplicate(vector<int>& nums){
  bool result = false;
  unordered_set<int> set;
  for (int i=0; i<nums.size(); i++) {
    if(set.count(nums[i])){
      return true;
    }
    set.insert(nums[i]);
  }

  return result;
}
int main (int argc, char *argv[]) {
  vector<int> input = {1,2,3};
  bool output = containsDuplicate(input);
  cout << boolalpha << output << endl;
  
  return 0;
}
