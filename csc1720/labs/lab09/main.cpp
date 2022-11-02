/*
Matt Burton
csc1720
3/17/21

to compile:
	g++ -Wall *.cpp

to execute:
	./a.out
*/
#include "arrayListType.h"
#include "orderedArrayListType.h"
#include <iostream>
using namespace std;

int main()
{
	orderedArrayListType oList;

	cout << "InsertAt(2,3)" << endl;
	oList.insertAt(2,3);
	oList.print();
	
	cout << "InsertEnd(5)" << endl;
	oList.insertEnd(5);
	oList.print();
	cout << endl;

/* used for testing a full list, doesnt work with the rest of my tests though
	cout << "InsertAt(3,4) in a full list" << endl;
	oList.insertAt(3,4);
	oList.print();
		
	cout << "InsertEnd(6) in a full list" << endl;
	oList.insertEnd(6);
	oList.print();
*/
	cout << "seqSearch(5)" << endl;
	int loc = oList.seqSearch(5);
	if (loc >= 0)
		cout << "5 found at " << loc << "." << endl;
	else
		cout << "5 was not found in the list." << endl;

	cout << "seqSearch(2)" << endl;
   loc = oList.seqSearch(2);
	if (loc >= 0)
		cout << "2 found at " << loc << "." << endl;
	else
		cout << "2 was not found in the list." << endl;
	cout << endl;

	cout << "Copying list." << endl;
	orderedArrayListType copyList(oList);
	cout << "Original list:" << endl;
	oList.print();
	cout << "Copied list:" << endl;
	copyList.print();

	cout << "InsertEnd(1) into the newly copied list." << endl;
	copyList.insertEnd(1);

	cout << "Original list:" << endl;
	oList.print();
	cout << "Copied list:" << endl;
	copyList.print();
	cout << endl;

	cout << "Testing the overloaded = operator." << endl;
	copyList = oList;

	cout << "Original list:" << endl;
	oList.print();
	cout << "Copied list:" << endl;
	copyList.print();

	cout << "InsertEnd(4) into the newly copied list." << endl;
	copyList.insertEnd(4);

	cout << "Original list:" << endl;
	oList.print();
	cout << "Copied list:" << endl;
	copyList.print();
	cout << endl;

	cout << "Testing the overloaded << operator." << endl;
	cout << "Original list:" << endl;
	cout << oList;
	cout << "Copied list:" << endl;
	cout << copyList;

	return 0;
}
