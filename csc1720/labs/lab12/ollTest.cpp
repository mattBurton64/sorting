/*
Matt Burton
csc1720
04/07/21

Program to test the various operations on an ordered linked list

to compile: g++ -o testOrdered ollTest.cpp

to execute: ./testOrdered
*/
  
#include <iostream>
#include "orderedLinkedList.h"
 
using namespace std;
 
template<class Type>
double findAvg(orderedLinkedList<Type> list);

int main()
{
   orderedLinkedList<int> list1, list2;        
   int num;                                    

   cout << "Creating list with input 77 11 44 99 33 55" << endl ;

   list1.insertLast(77);                      
   list1.insertLast(11);
   list1.insertLast(44);
   list1.insertLast(99);        
   list1.insertLast(33);
   list1.insertLast(55);

   cout << endl;                               

   cout << "list1: ";                  
   list1.print();                             
   cout << endl;                               

   list2 = list1; //test the assignment operator 

   cout << "list2: ";                 
   list2.print();                              
   cout << endl;                              

	cout << "Finding the average of list1: " << findAvg(list1) << endl;

   cout << "Enter the number to be " << "deleted: ";                        
   cin >> num;                               
   cout << endl;                               

   list2.deleteNode(num);                     

   cout << "After deleting " << num << endl;
   cout << "list2: " ;         
   list2.print();                              
   cout<<endl<<endl;  

	cout << "Deleting the largest number" << endl;                        

   list2.deleteLargest();

	cout << "list2: " ;         
   list2.print();                              
   cout<<endl;  

   cout << endl << "Output list1 " << "using an iterator:" << endl;            

   linkedListIterator<int> it;                  

   for (it = list1.begin(); it != list1.end(); ++it)                  
       cout << *it << " ";                        
   cout << endl;          

   return 0;					
}

template<class Type>
double findAvg(orderedLinkedList<Type> list)
{
	double average = 0.0;
	linkedListIterator<int> itr;

	for (itr = list.begin(); itr != list.end(); ++itr)
	{
		average += *itr;
	}

	average /= static_cast<double>(list.length());

	return average;
}
