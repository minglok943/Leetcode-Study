#include <iostream>
#include <vector>
#include <algorithm>
//https://leetcode.com/problems/longest-repeating-character-replacement/
using namespace std;

int charReplacement(string s, int k){
  //k is the number of characters can be replaced
  int left=0, right=1, maxLen=1;
  vector<int> freq(26, 0); //a-z contains 26 characters, to record number of occurs in substring
  while(right<s.length()){
    freq[s[right]-'A']++;
    //deference iterator returned by max_element
    int maxFreq = *max_element(freq.begin(), freq.end());    

    //highlight: if the substring length - max occurs bigger than k
    //for example AABAB = 5, maxFreq = 3, > k
    if(right-left+1 - maxFreq > k){
      freq[s[left]] --;
      left ++;
    }
    maxLen = max(maxLen, right-left+1);
    right++;
  }
  return maxLen;
}
int main (int argc, char *argv[]) {
  string s = "AABABBA";
  int len = charReplacement(s, 1);
  cout << "len: " << len << endl;
  return 0;
}
