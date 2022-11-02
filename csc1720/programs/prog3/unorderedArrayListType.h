/*
Matt Burton
csc1720
3/21/21
A class for unordered list of T type
*/
#ifndef UnorderedArrayList_TYPE
#define UnorderedArrayList_TYPE   
#include "arrayListType.h" 
using namespace std;

template<typename T>
class unorderedArrayListType: public arrayListType
{
	using arrayListType<T>::maxSize;
	using arrayListType<T>::length;
	using arrayListType<T>::list;
   public:
      //Constructor
      unorderedArrayListType(int size = 100);

      /* insertAt Function to insert insertItem at list[location]
         Precondition: A list object exists and it is not already full
         Postcondition: list[location] = insertItem;
      */
     void insertAt(int location, T insertItem);
 
      /* insertEnd Function to insert insertItem at the end of the list
         Precondition: A list object exists and it is not already full
         Postcondition: list[length] = insertItem; and length++;
								If the list is full, an appropriate
								message is displayed.
      */
     void insertEnd(T insertItem);

      /* replaceAt Function to override list[location] with repItem
			Precondition: A list object exists and it is not already full
         Postcondition: list[location] = repItem
      */
      void replaceAt(int location, T repItem);
  
      /* seqSearh Function check a list for the first occurance of a number
         Precondition: A list object exists with data in it
         Postcondition: The index of location where searchItem was found
								is returned
      */
      int seqSearch(T searchItem) const;

}; 
#include "unorderedArrayListType.cpp"
#endif
