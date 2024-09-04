#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
  /*
   * hash table 
   * complement = target - array number
   * iterate through array, check if complement value exist
   */

  //Initialize empty hash table
  unordered_map <int, int> comp;
  //python hash = {}
  //javascript hash = {}
  //java   Map<Integer, Integer> hash = new HashMap<>();
  
  //Loop, calculate complement 
  for(int i=0; i<nums.size(); i++){
    int complement = target-nums[i];
    //python if nums[i] in comp
    //javascript if nums[i] in map
    //java   if comp.containsKey(nums[i])
    if(comp.find(nums[i])!=comp.end()){
      return {i, comp[nums[i]]};
      //python return [i, comp[nums[i]]] same as javascript
      //java   return new int[]{i, comp.get(nums[i])}
    }else{
      comp[complement] = i;
      //python same
      //java   comp.put(key, value);
    }
  }
  return {};
  //python return []
  //Java   return new int[] {};
}

int main (int argc, char *argv[]) {
  vector<int> input = {2, 11, 7, 5};
  /* hash table {complement: index}
  *   {7: 0, -2: 1, }
  *
  *
  */
  vector<int> output = twoSum(input, 9);
  cout << "the indexes are " << endl;
  for(auto a: output){
    cout << a << ", ";
  }
  cout << endl;
  return 0;
}
