#ifndef OrderedArrayList_TYPE
#define OrderedArrayList_TYPE

#include <iostream>  
#include "arrayListType.h" 
using namespace std;

class orderedArrayListType: public arrayListType
{
   public:
      //Constructor
      orderedArrayListType(int size = 100);

      /* insertAt		
			inserts insertItem into the calling
			orderedArrayListType object in 
			ascending order
			precondition: the list isnt full already
			postcondition: insertItem is added to the
								list in order
		*/
      void insertAt(int location, int insertItem);
  
      /* insertEnd Function ...
     		inserts insertItem into the calling
			orderedArrayListType object in 
			ascending order      
			precondition: the list isnt full already
			postcondition: insertItem is added to the
								list in order
		*/
      void insertEnd(int insertItem);

		/* replaceAt Function
			replaces an element in a list
         Precondition: location is an int between 0-length
         Postcondition: list[location] = repItem;
      */
      void replaceAt(int location, int repItem);
  
      /* seqSearh 
			finds searchItem in a list, terminates it
			starts reading values greater than searchItem
         Precondition: a list with data is input
         Postcondition: returns the index of searchItem
								or -1 if not found
      */
      int seqSearch(int searchItem) const;
		
		/* insert
			inserts insertItem into the calling
			orderedArrayListType object in 
			ascending order
			precondition: the list isnt full already
			postcondition: insertItem is added to the
								list in order
		*/
		void insert(int insertItem);
		
		/* overloaded =
			takes an empty orderedArrayListType
			object and makes a deep copy based on
			an existing list
		*/
		const orderedArrayListType& operator=(const orderedArrayListType& rightObject);

		/* overloaded <<
			takes a orderedArrayListType object and 
			inserts each array element to the ostream
		*/
		friend ostream& operator<<(ostream &os, const orderedArrayListType& list);

}; 

#endif
