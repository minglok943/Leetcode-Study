//https://leetcode.com/problems/container-with-most-water/description/
#include <iostream>
#include <vector>

using namespace std;

int mostWater(vector<int> &height){
  int maxArea = 0;
  int low = 0;
  int high = height.size()-1;
  while(low < high){
    int h = min(height[low], height[high]);
    int width = high - low;
    maxArea =  max(maxArea, h*width);
    if(height[low] < height[high]) low++;
    else high --;
  }
  return maxArea;
}

int main (int argc, char *argv[]) {
  vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

  int output = mostWater(height);
  cout << "output: " << output << endl;
  return 0;
}
