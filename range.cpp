#include <iostream>
#include <vector>

using namespace std;
int main (int argc, char *argv[]) {
  vector<int> a = {1, 2 ,3 ,4};
  vector<int>b(a.begin()+1, a.begin()+2);
  for(auto v: b)
    cout << v << ", ";
  cout << endl;
  return 0;
}
