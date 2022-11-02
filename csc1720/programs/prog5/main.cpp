/*
Matt Burton
csc1720 02
04/13/21

Use a load function to load two unorderedLinkedLists with words from .txt files
Merge the two unorderedLinkedLists together and empty the second list

compile with: g++ -Wall *.cpp

execute with: ./a.out
*/

#include "linkedList.h"
#include "orderedLinkedList.h"
#include "stuType.h"
#include <iostream>
#include <fstream>
using namespace std;

void load(orderedLinkedList<stuType>& list);
/* 
	LOAD
	____

	Function used to fill an orderedLinkedList with stuType objects
	Precondition: An orderedLinkedList type object is passed in
					  and the user inputs a file name in the command line
	Postcondition:The orderedLinkedList is filled with the stuTypes
					  from the passed in file

*/
double findAvg(orderedLinkedList<stuType> list);
/* 
	FIND AVERAGE
	____________

	Function used to find tthe average gpa of students in an orderedLinkedList
	Precondition: An orderedLinkedList type object is passed in
					  with data
	Postcondition:the average gpa is returned

*/

int main()
{
	//create empty lists
	orderedLinkedList<stuType> juniors, seniors;
	//load the lists from files
	load(juniors);
	load(seniors);
   cout << endl;

	//print juniors list
	cout << "Juniors: " << endl;
	juniors.print();
	cout << endl << endl;

	//print seniors list
	cout << "Seniors: " << endl;
	seniors.print();
	cout << endl << endl;

	//merge juniors and seniors and print the new list
	cout << "Merged list: " << endl;
	juniors.merge(seniors);
	juniors.forwardPrint();
	cout << endl << endl;

	//find the average of the newly merged list
	cout << "GPA average: " << endl;
	cout << findAvg(juniors) << endl;

	return 0;
}

void load(orderedLinkedList<stuType>& list)
{
	string file;
	string iFirst;
	string iLast;
	double igpa;

	cout << "Enter the data file name: ";
	cin >> file;

	ifstream inFile;
	inFile.open(file);

	inFile >> iFirst >> iLast >> igpa;
	while(inFile)
	{
		stuType stu(iFirst, iLast, igpa);
		list.insert(stu);
		inFile >> iFirst >> iLast >> igpa;
	}

	inFile.close();
}

double findAvg(orderedLinkedList<stuType> list)
{
  double average = 0;
  double count = 0;
  linkedListIterator<stuType> itr;

  for (itr = list.begin(); itr != list.end(); ++itr)
  {
    average += (*itr).getGPA();
    count++;
  }

  return average / count;
}
