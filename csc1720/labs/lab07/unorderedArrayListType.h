#ifndef UnorderedArrayList_TYPE
#define UnorderedArrayList_TYPE
   
#include "arrayListType.h" 

class unorderedArrayListType: public arrayListType
{
   public:
      //Constructor
      unorderedArrayListType(int size = 100);

      /* insertAt Function to insert insertItem at list[location]
         Precondition: A list object exists and it is not already full
         Postcondition: list[location] = insertItem;
      */
      void insertAt(int location, int insertItem);
 
      /*insertFirst Function to insert insertItem an item at the beginning of 
        the list. Note that this is an abstract function.
        Postcondition: list[0] = insertItem; and length++;
		  					  list elements are shifted right 1.
                       If the list is full, an appropriate 
                       message is displayed.
      */
      void insertFirst(int insertItem);

      /* insertEnd Function to insert insertItem at the end of the list
         Precondition: A list object exists and it is not already full
         Postcondition: list[length] = insertItem; and length++;
								If the list is full, an appropriate
								message is displayed.
      */
      void insertEnd(int insertItem);

      /* replaceAt Function to override list[location] with repItem
			Precondition: A list object exists and it is not already full
         Postcondition: list[location] = repItem
      */
      void replaceAt(int location, int repItem);
  
      /* seqSearh Function check a list for the first occurance of a number
         Precondition: A list object exists with data in it
         Postcondition: The index of location where searchItem was found
								is returned
      */
      int seqSearch(int searchItem) const;
	
      /* removeAt Function to remove any number within a list
         Precondition: A list object exists and with data in it
         Postcondition: list[location] = list[length - 1]; and length--;
		*/
		void removeAt(int location);
			
		/*findMax Function to find the largest number in the list.
			Note this is an abstract function
			Postcondition: The greatest list element is returned.
		*/
		int findMax();
}; 

#endif
