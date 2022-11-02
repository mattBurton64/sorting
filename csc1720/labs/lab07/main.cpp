#include "arrayListType.h"
#include "unorderedArrayListType.h"
#include <iostream>
using namespace std;

int main()
{
	unorderedArrayListType myList;


	cout << "  Testing isEmpty() on an empty list." << endl;
	if (myList.isEmpty())
		cout << "The list is empty" << endl;
	else
		cout << "The list is not empty" << endl;


	cout << "  Testing isFull() on a list which is not full." << endl;
	if (myList.isFull())
		cout << "The list is full." << endl;
	else
		cout << "The list is not full." << endl;


	cout << "  Testing insertAt() inserting 1 at 0." << endl;
	myList.insertAt(0,1);
	myList.print();


	cout << "  Testing insertAt() inserting 1 at -1." << endl;
	myList.insertAt(-1,1);
	myList.print();


	cout << "  Testing insertFirst() inserting 2, 3, 4, 5 and 6." << endl;
	myList.insertFirst(2);
	myList.insertFirst(3);
	myList.insertFirst(4);
	myList.insertFirst(5);
	myList.insertFirst(6);
	myList.print();


	cout << "  Testing insertEnd() inserting 100 at the end." << endl;
	myList.insertEnd(100);
	myList.print();


	cout << "  Testing replaceAt() replacing 1 at 1." << endl;
	myList.replaceAt(1,1);
	myList.print();


	cout << "  Testing seqSearch() for 1." << endl;
	int result = myList.seqSearch(1);
	if (result > -1)
		cout << "1 was found in the list at " << result << "." << endl;
	else
		cout << "1 was not found in the list." << endl;


	cout << "  Testing seqSearch() for 10." << endl;
	result = myList.seqSearch(10);
	if (result > -1)
		cout << "10 was found in the list at " << result << "." << endl;
	else
		cout << "10 was not found in the list." << endl;

	
	cout << "  Testing listSize()." << endl;
	cout << "The list has a size of " << myList.listSize() << "." << endl;


	cout << "  Testing maxListSize() on a list with a default maxSize of 100." << endl;
	cout << "The list has a maxSize of " << myList.maxListSize() << "." << endl;


	cout << "  Testing findMax()." << endl;
	cout << "The maximum value in the list is " << myList.findMax() << "." << endl;


	cout << "  Testing removeAt() at 0." << endl;
	myList.removeAt(0);
	myList.print();


	cout << "  Testing removeAt() at 0." << endl;
	myList.removeAt(0);
	myList.print();


	cout << "  Testing findMax()." << endl;
	cout << "The maximum value in the list is " << myList.findMax() << "." << endl;


	cout << "  Testing clearList()." << endl;
	myList.clearList();
	myList.print();

	return 0;
}
