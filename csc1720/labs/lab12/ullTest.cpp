/*Matt Burton
csc1720
04/07/21

Program to test the various operations on an unordered linked list

to compile: g++ -o testUnordered ullTest.cpp

to execute: ./testUnordered
*/

#include<iostream>
#include"unorderedLinkedList.h"

using namespace std; 

template<class Type>
double findAvg(const unorderedLinkedList<Type>);

int main()
{
   unorderedLinkedList<int> listA, listB;          
   int num;                                        

   cout << "Creating list with input 22 7 48 93 14 2 " << endl ;

   listA.insertLast(22);                      
   listA.insertLast(7);
   listA.insertLast(48);
   listA.insertLast(93);        
   listA.insertLast(14);
   listA.insertLast(2);
  	listA.insertLast(-5);
	listA.insertLast(-8);

   cout << endl;                                   

   cout << "listA: ";                      
   listA.print();                                  
   cout << endl;                                   

	cout << "Number of negatives in listA: " << listA.negCount() << endl;

   cout << "Length of listA: " << listA.length() << endl;                 

   listB = listA;	   //test the assignment operator 

   cout << endl;
   cout << "listB: ";                     
   listB.print();                                  
   cout << endl;                                   

   cout << "Length of listB: " << listB.length() << endl;                 
   cout << endl;

	cout << "Finding the average of listB: " << findAvg(listB) << endl;

   cout << "Enter the number to be " << "deleted: ";                           
   cin >> num;                                     

   listB.deleteNode(num);                          
	
	cout << "After deleting " << num << endl;
   cout << "listB: " ;                     
   listB.print();                                  
   cout << endl;                                

	cout << "Deleting the largest number." << endl;
	listB.deleteLargest();

   cout << "After deleting " << num << endl;
   cout << "listB: " ;                     
   listB.print();                                  
   cout << endl;                                

   cout << "Length of listB: " << listB.length() << endl;              
   cout << endl;

   cout << "Output listA " << "using an iterator:" << endl;            

   linkedListIterator<int> it;                  

   for (it = listA.begin(); it != listA.end(); ++it)                  
       cout << *it << " ";                        
   cout << endl;

   unorderedLinkedList<char> listC;          
   char x;                                 

   cout << endl << "Creating list with input A K M G ! C " << endl ;

   listC.insertLast('A');                      
   listC.insertLast('K');
   listC.insertLast('M');
   listC.insertLast('G');        
   listC.insertLast('!');
   listC.insertLast('C');
       
   cout << endl;                                   

   cout << "listC: ";                      
   listC.print();                                  
   cout << endl;                                   
   cout << "Length of listC: " << listC.length() << endl;  

   cout<< endl << "Enter the character to be " << "deleted: ";                           
   cin >> x;                                     

   listC.deleteNode(x);                          
	
   cout << "After deleting " << x << endl;
   cout << "listC: " ;                     
   listC.print();                                  
   cout << endl;                         

   return 0;					
}

template<class Type>
double findAvg(unorderedLinkedList<Type> list)
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
