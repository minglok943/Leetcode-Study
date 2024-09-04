//https://www.youtube.com/watch?v=qIACm3XktDc&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=12
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int longestSubstring(string s){
  int left=0, right=0, maxLen=0;
  set<char> unique;
  while(right<s.length()){
    if(unique.find(s[right]) == unique.end()){
      //not found
      unique.insert(s[right++]);
      maxLen = max(maxLen, (int)unique.size());
    }else{
      unique.erase(s[left++]);
    } 
  }
  return maxLen;
}

int main (int argc, char *argv[]) {
  string s = "abcabcbb";
  int len = longestSubstring(s);
  cout << "len: " << len << endl;
  return 0;
}
