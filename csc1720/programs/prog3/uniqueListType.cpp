#include "unorderedArrayListType.h"
using namespace std;

template<typename T>
uniqueListType<T>::uniqueListType(int size)
	: unorderedArrayListType<T>(size)
{
}

template<typename T>
void uniqueListType<T>::insertAt(int location, T insertItem)
{
	if (unorderedArrayListType<T>::seqSearch(insertItem) == -1)
		unorderedArrayListType<T>::insertAt(location, insertItem);
}

template<typename T>
void uniqueListType<T>::insertEnd(T insertItem)
{
	if (unorderedArrayListType<T>::seqSearch(insertItem) == -1)
		unorderedArrayListType<T>::insertEnd(insertItem);
}

template<typename T>
void uniqueListType<T>::replaceAt(int location, T repItem)
{
	if (unorderedArrayListType<T>::seqSearch(repItem) == -1)
		unorderedArrayListType<T>::replaceAt(location, repItem);
}
