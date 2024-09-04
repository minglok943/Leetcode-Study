#include <iostream>

using namespace std;
int main(){
    int i = 3; 

    // A pointer to variable i or "stores the address of i"
    int *ptr = &i; 

    // A reference (or alias) for i.
    int &ref = i; 

    cout << "poi: " << &ptr << endl; 
    cout << "ref: " << &ref << endl; 
    cout << "i  : " << &i   << endl;
    return 0;
}
