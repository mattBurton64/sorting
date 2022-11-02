#include "unorderedArrayListType.h"
#include "uniqueListType.h"
using namespace std;

uniqueListType::uniqueListType(int size)
	: unorderedArrayListType(size)
{
}


void uniqueListType::insertAt(int location, string insertItem)
{
	if (unorderedArrayListType::seqSearch(insertItem) == -1)
		unorderedArrayListType::insertAt(location, insertItem);
}


void uniqueListType::insertEnd(string insertItem)
{
	if (unorderedArrayListType::seqSearch(insertItem) == -1)
		unorderedArrayListType::insertEnd(insertItem);
}


void uniqueListType::replaceAt(int location, string repItem)
{
	if (unorderedArrayListType::seqSearch(repItem) == -1)
		unorderedArrayListType::replaceAt(location, repItem);
}
