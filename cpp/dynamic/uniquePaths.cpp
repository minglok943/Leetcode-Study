//62 Unique Paths
//https://www.youtube.com/watch?v=E_f7zyK1XFk&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=22
#include <iostream>
#include <vector>
using namespace std;

//robot can only move down and right, unique paths from [0][0] to [m-1][n-1]
int uniquePaths(int m, int n){
  //m = row, n = column
  vector<vector<int>> dp(m, vector<int>(n));
  //calculate sum of left and top number for each cell
  for(int i=0; i<m; i++){
    dp[i][0] = 1; //set first column of each row to 1, because only one method to reach
  }
  for(int i=0; i<n; i++){
    dp[0][i] = 1;
  }

  for(int i=1; i<m; i++){
    for(int j=1; j<n; j++){
      //           top           left
      dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
  }

  return dp[m-1][n-1];
}

int main (int argc, char *argv[]) {
  int output = uniquePaths(3, 7);
  cout << "unique paths: " << output << endl;
  return 0;
}
