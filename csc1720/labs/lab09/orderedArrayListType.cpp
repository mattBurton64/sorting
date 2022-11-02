#include <iostream>
#include "orderedArrayListType.h" 

using namespace std; 

orderedArrayListType::orderedArrayListType(int size)
                      : arrayListType(size)
{
}  //end constructor

void orderedArrayListType::insertAt(int location, int insertItem) 
{
	insert(insertItem);
}  //end insertAt

void orderedArrayListType::insertEnd(int insertItem)
{
 	insert(insertItem);
}  //end insertEnd

void orderedArrayListType::replaceAt(int location, int repItem)
{
   if (location < 0 || location >= length)
      cout << "The location of the item to be "
           << "replaced is out of range." << endl;
   else
      list[location] = repItem;
} //end replaceAt

int orderedArrayListType::seqSearch(int searchItem) const
{
   int loc;
   bool found = false;

   loc = 0;

   while (loc < length && !found && list[loc] <= searchItem)
      if (list[loc] == searchItem)
         found = true;
      else
         loc++;

   if (found)
      return loc;
   else
      return -1;
} //end seqSearch

void orderedArrayListType::insert(int insertItem)
{
	//list empty?
	if (length == 0)
		list[length++] = insertItem;
	else if (length == maxSize)
		cout << "Cannot insert in a full list." << endl;
	else 
	{
		//Find the location in the list where to insert
		//insertItem. Keep in items are in ascending order. 
		int loc = 0;
		bool found = false;
		while (!found && loc < length)
		{
			if (list[loc] >= insertItem)
				found = true;
			else
				loc++;
		}

	//Now, move elements down to make space for insertItem
	for (int i = length; i > loc; i--)
		list[i] = list[i - 1];

	//loc is the location in the array for insertItem
	list[loc] = insertItem;
	length++; }
} //end insert

const orderedArrayListType& orderedArrayListType::operator=(const orderedArrayListType& rightObject)
{
	//local declaration, if any
	//avoid self-assignment with an if statement 
	if (this != &rightObject) 
	{
		//algorithm to copy rightObject into this object
		//NOTE – similar to the copy constructor in arrayListType 
		maxSize = rightObject.maxSize;
		length = rightObject.length;

		list = new int[maxSize]; 	//create the array

		for (int j = 0; j < length; j++)  //copy otherList
			list [j] = rightObject.list[j];

	}
	//Return the object assigned.
	return *this; 
}

ostream& operator<<(ostream& os, const orderedArrayListType& list)
{
	for(int i = 0; i < list.length; i++)
		os << list.list[i] << " ";
	os << endl;
	return os;
}
