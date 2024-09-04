#include <cctype>
#include <iostream>

using namespace std;

bool isPalindrome(string s){
  int left=0, right=s.length()-1;

  while(left<right){
    //important left<right to prevent overflow
    while(left<right && !isalnum(s[left]))
      left++;

    while(left<right && !isalnum(s[right]))
      right --;

    if(tolower(s[left]) != tolower(s[right]))
      return false;

    left++, right--;
  }
  return true;
}

int main (int argc, char *argv[]) {
  string s = "A man, a plan, a canal: Panama";
  bool is = isPalindrome(s);
  cout << "palindrome: " << is << endl;
  return 0;
}
