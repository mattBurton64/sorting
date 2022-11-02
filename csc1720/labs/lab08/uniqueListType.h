#ifndef UniqueList_TYPE
#define UniqueList_TYPE
   
#include "unorderedArrayListType.h" 
#include <string>
using namespace std;

class uniqueListType: public unorderedArrayListType
{
   public:
      //Constructor
      uniqueListType(int size = 100);

      /* insertAt Function to insert a string in a list
         Precondition: the list is not full, the location is
								within the range of 0-maxListSize, and
								insertItem is a string, the string in
								insertItem is not in the list already
         Postcondition: The list is updated so that insertItem
								is now at list[location] = insertItem
								and all elements whose index is
								>= location are shifted right 1.
								Also the length is increased by 1
      */
      void insertAt(int location, string insertItem);
  
      /* insertEnd Function to insert a srting at the end of a list
         Precondition: The list is not full, and
								insertItem is a string.
								insertItem is not in the list already.
         Postcondition: list[length] = insertItem; length++
      */
      void insertEnd(string insertItem);

      /* replaceAt Function to replace an element in a list
         Precondition: The list does not contain repItem in
								itself anywhere and location is an
								int between 0-length
         Postcondition: list[location] = repItem;
      */
      void replaceAt(int location, string repItem);
}; 

#endif
