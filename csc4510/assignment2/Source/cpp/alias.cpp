// This program is intended to investigate the properties of aliasing in C++
#include <iostream>
using namespace std;

void sub(int &integer) // declaring a subroutine which takes in an integer parameter by reference
{
    integer = 0; // alter the value
}

int main () {
    int integer = 1; // declaring an integer
    int* pointer = &integer; // decalring a pointer that references the memory address of "integer"

    // Display the value of integer before and after being passed into the subroutine
    cout << "Integer\n=======" << endl;
    cout << "before: " << integer << endl;
    sub(integer);
    cout << " after: " << integer << endl;

    cout << "\nPointer\n=======" << endl;
    cout << "before: " << *pointer << endl;
    sub(*pointer);
    cout << " after: " << *pointer << endl;
}