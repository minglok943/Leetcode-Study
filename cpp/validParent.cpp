#include <iostream>
#include <stack>

using namespace std;
//20 Valid parenthesis
//https://www.youtube.com/watch?v=SK-JVuX8mKk&list=PLPERBdDHWLi1x0ZxbnCd5t8yxEudSrxxH&index=16
bool isMatching(char open, char close){
  return (open == '(' && close == ')') ||\
         (open == '{' && close == '}') ||\
         (open == '[' && close == ']');
}
bool isValid(string s){
  //python stk = []
  //java Stack<Character> stack = new Stack<Character>();
  stack<char> stk;
  //python     for c in s:
  //javascript for(const c of s){}
  //java       for( c: s.toCharArray() ){}
  for(char c: s){
    if(c == '(' || c == '{' || c == '['){
      //python stk.append(c)
      stk.push(c);
    }else if(c == ')' || c == '}' || c == ']'){
      //python      if not stk: empty, stk[-1] last element
      //java        if(stk.isEmpty())
      //javascript  if(stk.legnth === 0)
      if(stk.empty() || !isMatching(stk.top(), c)){
        return false;
      }else{
        //python stk.pop():
        //  
        stk.pop();
      }
    }
  }
  return stk.empty(); //important
}

int main (int argc, char *argv[]) {
  string s = "() [] {}";
  bool output = isValid(s);
  cout << "is valid parenthesis: " << output << endl;
  return 0;
}
