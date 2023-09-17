// This program is intended to investigate the properties of scope in C++
#include <iostream>
using namespace std;

int integer = -1; // declaring a global variable

void sub(int &integer) // declaring a subroutine which takes in an integer parameter by reference
{
    integer = 0; // alter the value
}

int main () {
    int integer = 1; // declaring a local variable with the same name as the global variable "integer"

    // Display the value of integer before and after being passed into the subroutine
    cout << "Integer\n=======" << endl;
    cout << "before: " << integer << endl;
    sub(integer);
    cout << " after: " << integer << endl;
}