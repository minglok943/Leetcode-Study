//https://www.youtube.com/watch?v=4Xe8YmSDnBk&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs){
  unordered_map<string, vector<string>> groups;
  for(auto str:  strs){
    string sorted = str;
    sort(sorted.begin(), sorted.end());
    groups[sorted].push_back(str);
  }
  vector<vector<string>> output;
  for(auto& group: groups){
    output.push_back(group.second);
  }
  return output;
}

int main (int argc, char *argv[]) {
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> output = groupAnagrams(strs);

  return 0;
}
