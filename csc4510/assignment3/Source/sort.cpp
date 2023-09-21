// This program is intended to sort any type of data including a custom type: color
#include <iostream>
#include <algorithm> // provides access to the sort method
#include <vector> // dynamic arrays
#include <string>
using namespace std;

enum COLOR {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET}; // Declare an enumeration for COLORS that ranges from RED to VIOLET

// Method for sorting using templates and the standard sort algorithm
template<typename T>
void MySort(vector<T>& values){
    sort(values.begin(), values.end());
}

// Method for iterating through vectors of any type and outputting the contents of each item to the command line
template<typename T>
void OutVector (vector<T> values){
    for (int i = 0; i < values.size(); ++i)
    {
        cout << values[i] << endl;
    }
    cout << endl;
}

// Declare a specific output method for handling COLOR type
void OutVector(vector<COLOR> values) {
    const string colorNames[] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "VIOLET"}; // used for converting from enum ints to strings so we can output the color's name to the command line
    for (int i = 0; i < values.size(); ++i) {
        cout << colorNames[values[i]] << endl;
    }
    cout << endl;
}

// Method for handling the output of vectors before and after being sorted
template<typename T>
void CallSort(vector<T> values)
{
    cout << "Vector before sorting..." << endl;
    OutVector(values);
    MySort(values);
    cout << "Vector after sorting..." << endl;
    OutVector(values);
}

// Method for initializing a vector of T data type from the standard input stream
template<typename T>
vector<T> HandleInput() {
    vector<T> values;
    T value;
    while (cin >> value) {
        values.push_back(value);
    }
    return values;
}

// Method for initializing a vector of colors
vector<COLOR> HandleColorInput() {
    vector<COLOR> values;
    string color;
    while (cin >> color) { // converts from strings to their corresponding color enum
        if (color == "RED") {
            values.push_back(RED);
        } else if (color == "ORANGE") {
            values.push_back(ORANGE);
        } else if (color == "YELLOW") {
            values.push_back(YELLOW);
        } else if (color == "GREEN") {
            values.push_back(GREEN);
        } else if (color == "BLUE") {
            values.push_back(BLUE);
        } else if (color == "INDIGO") {
            values.push_back(INDIGO); 
        } else if (color == "VIOLET") {
            values.push_back(VIOLET);
        } else {
            cerr << "Invalid color value: " << color << endl;
        }
    }
    return values;
}

int main (int argc, char* argv[]) { // program takes in arguments

    string dataType = argv[1]; // the first and only argument is used to define the expected dataType of the input test file

    if (dataType == "character") 
    {
        vector<char> characterValues = HandleInput<char>();
        CallSort(characterValues);
    }
    else if (dataType == "color") 
    {
        vector<COLOR> colorValues = HandleColorInput();
        CallSort(colorValues);
    }
    else if (dataType == "float") 
    {
        vector<float> floatValues = HandleInput<float>();
        CallSort(floatValues);
    }
    else if (dataType == "integer") 
    {
        vector<int> integerValues = HandleInput<int>();
        CallSort(integerValues);
    }
    else if (dataType == "string") 
    {
        vector<string> stringValues = HandleInput<string>();
        CallSort(stringValues);
    }
    else {
        cerr << "Invalid dataType" << endl;
    }
    
    return 0;
}