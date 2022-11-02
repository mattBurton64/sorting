#include <iostream>
#include <fstream>
#include "arrayListType.h"
#include "unorderedArrayListType.h"
#include "uniqueListType.h"
using namespace std;

void load(unorderedArrayListType&);

int main()
{
	uniqueListType list(16);
	load(list);
	list.print();
	return 0;
}

void load(unorderedArrayListType& list)
{
	int i = 0;
	string iString;

	cin >> iString;
	list.insertAt(0, iString);

	while(cin && !list.isFull())
	{
		cin >> iString;
		list.insertEnd(iString);
		i++;
	}
}
