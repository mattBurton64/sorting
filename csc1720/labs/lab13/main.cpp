/*
Matt Burton
csc1720 02
04/13/21

Use a load function to load two unorderedLinkedLists with words from .txt files
Merge the two unorderedLinkedLists together and empty the second list

compile with: g++ main.cpp -o merge.out

execute with: ./merge.out
*/

#include "linkedList.h"
#include "unorderedLinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;

void load(unorderedLinkedList<string>& list);
/* 
	LOAD
	____

	Function used to fill an unorderedLinkedList with strings
	Precondition: An unorderedLinkedList type object is passed in
					  and the user inputs a file name in the command line
	Postcondition:The unorderedLinkedList is filled with the strings
					  from the passed in file

*/

int main()
{
	unorderedLinkedList<string> listA, listB;
	load(listA);
	load(listB);
	cout << endl;

	cout << "List 1: " << endl;
	listA.print();
	cout << endl << endl;

	cout << "List 2: " << endl;
	listB.print();
	cout << endl << endl;

	cout << "Merged list: " << endl;
	listA.merge(listB);
	listA.forwardPrint();
	cout << endl << endl;

	cout << "Reversed list: " << endl;
	listA.reversePrint();
	cout << endl;

	return 0;
}

void load(unorderedLinkedList<string>& list)
{
	string file;
	string temp;

	cout << "Enter the data file name: ";
	cin >> file;

	ifstream inFile;
	inFile.open(file);
	
	inFile >> temp;
	while(inFile)
	{
		list.insertLast(temp);
		inFile >> temp;
	}

	inFile.close();
}
