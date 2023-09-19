// This program is intended to sort any type of data including colors
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

enum COLOR {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

template<typename T>
void MySort(vector<T>& vector){
    sort(vector.begin(), vector.end());
}

template<typename T>
void outVector (vector<T> vector){
    for (const auto& item : vector)
    {
        cout << item << endl;
    }
    cout << endl;
}

int main () {
    vector<float> floats = {0.0, -1.2, -5.8, 1.1, 9.72, 2.264, -2.353, 3.14, 0.2141, 6.32, -7.293};
    vector<int> integers = {-8, 5, 1, 99, -32, 213, 40, 2, -2, 723, -9402};
    vector<bool> booleans = {false, true, true, false, false, false, true, true, false, true};
    vector<char> characters = {'t', 'f', '9', '0', '{', ']', 's', 'v', '`', ':', 'n', 'S', 'e', 'V', 'c', '1', 'a', 'x', 'Z', '!', '.', '%'};
    vector<COLOR> colors = {ORANGE, RED, BLUE, GREEN, INDIGO, YELLOW, RED, VIOLET, ORANGE, BLUE, BLUE, YELLOW};

    cout << "Float vector before sorting..." << endl;
    outVector(floats);
    MySort(floats);
    cout << "Float vector after sorting..." << endl;
    outVector(floats);

    cout << "Integer vector before sorting..." << endl;
    outVector(integers);
    MySort(integers);
    cout << "Integer vector after sorting..." << endl;
    outVector(integers);

    cout << "Boolean vector before sorting..." << endl;
    outVector(booleans);
    MySort(booleans);
    cout << "Boolean vector after sorting..." << endl;
    outVector(booleans);

    cout << "Character vector before sorting..." << endl;
    outVector(characters);
    MySort(characters);
    cout << "Character vector after sorting..." << endl;
    outVector(characters);

    cout << "Color vector before sorting..." << endl;
    outVector(colors);
    MySort(colors);
    cout << "Color vector after sorting..." << endl;
    outVector(colors);

    return 0;
}