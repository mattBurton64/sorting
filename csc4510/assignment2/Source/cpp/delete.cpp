// This program is intended to investigate what happens if you delete a memory location in C++
#include <iostream>
using namespace std;

int main() {
    int* pointer = new int(1); // decalring a pointer that references a dynamically created integer whose memory is stored in the heap
    
    delete pointer; // deleting the memory location

    cout << "Dangling Pointer: " << *pointer << endl; // acccessing the memory location after deleting its reference

    return 0;
}
