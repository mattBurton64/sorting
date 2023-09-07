#include <iostream>
using namespace std;

void sub(int &a, int &b)
{
    a = 10;
    b = 12;
    return;
}

int main () {
    int p1 = 6;
    int arr [13] = {0,0,0,0,0,0,17,0,0,0,0,0,0};

    cout << arr[p1] << " " << p1 << endl;

    sub(arr[p1], p1);

    cout << arr[p1] << " " << p1 << endl;

    return 0;
}

