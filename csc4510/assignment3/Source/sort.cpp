// This program is intended to sort any type of data including colors
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
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
    vector<string> values;

    // Read values from cin (standard input)
    string line;
    while (getline(cin, line)) {
        values.push_back(line);
    }

    cout << "vector before sorting..." << endl;
    outVector(values);
    MySort(values);
    cout << "vector after sorting..." << endl;
    outVector(values);

    return 0;
}