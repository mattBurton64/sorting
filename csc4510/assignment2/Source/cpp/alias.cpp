// This program is intended to investigate the properties of aliasing and side effects in C++
#include <iostream>
using namespace std;

void sub(int &integer) // declaring a subroutine which takes in an integer parameter by reference
{
    integer = 0; // alter the value
}

int main () {
    int integer = 1; // declaring an integer
    int* pointer = &integer; // decalring a pointer that references the memory address of "integer"
    int& reference = integer; // declaring a reference to the memory location of "integer"

    // Display the value of integer before and after being passed into the subroutine
    cout << "  Integer before: " << integer << endl;
    cout << "  Pointer before: " << *pointer << endl;
    cout << "Reference before: " << reference << endl;

    sub(integer);
    cout << "   Integer after: " << integer << endl;

    sub(*pointer);
    cout << "   Pointer after: " << *pointer << endl;

    sub(reference);
    cout << " Reference after: " << reference << endl;
}