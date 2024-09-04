//https://www.youtube.com/watch?v=SmE14dKf-8M&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=SmE14dKf-8M
#include <iostream>
#include <vector>

using namespace std;

string longestPalindrome(string s){
  int n = s.length();
  int start = 0;
  int maxLength = 1;

  vector<vector<bool>> dp(n, vector<bool>(n, false));
  for(int i = n-1; i>=0; i--){
    dp[i][i] = true;
    for(int j = i+1; j<n; j++){
      //j-i = 1 means connected side by side
      /* examples kacca
      *  0 0 0 0 0 
      *  0 1 0 0 1  dp[i+1][j-1]  | ---> j
      *  0 0 1 1 0                v   
      *  0 0 0 1 0                i 
      *  0 0 0 0 1
      */
      if(s[i] == s[j] && (j-i == 1 || dp[i+1][j-1])){
        dp[i][j] = true;
        if(j-i+1 > maxLength){
          maxLength = j-i+1;
          start = i;
        }
      }
    }
  }

  return s.substr(start, maxLength);
}

int main (int argc, char *argv[]) {
  string input = "babba";
  string output = longestPalindrome(input);
  cout << "output : " << output << endl;
  return 0;
}
