#ifndef UnorderedArrayList_TYPE
#define UnorderedArrayList_TYPE
   
#include "arrayListType.h" 
#include <string>
using namespace std;

class unorderedArrayListType: public arrayListType
{
   public:
      //Constructor
      unorderedArrayListType(int size = 100);

      /* insertAt Function ...
         Precondition: 
         Postcondition: 
      */
      void insertAt(int location, string insertItem);
  
      /* insertEnd Function ...
         Precondition: 
         Postcondition: 
      */
      void insertEnd(string insertItem);

      /* replaceAt Function ...
         Precondition: 
         Postcondition: 
      */
      void replaceAt(int location, string repItem);
  
      /* seqSearh Function ...
         Precondition: 
         Postcondition: 
      */
      int seqSearch(string searchItem) const;

}; 

#endif
