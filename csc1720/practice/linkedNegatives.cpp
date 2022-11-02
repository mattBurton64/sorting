//Function for counting how many negative numbers are in a linked list

template <class Type>
int unorderedLinkedList<Type>::negCount()
{
	nodeType<Type> *curPtr;
	curPtr = this->first->link;
	int count = 0;

	while (curPtr != nullptr)
	{
		if(curPtr-> < 0)
		{
			count++;
		}
		curPtr = curPtr->link;
	}
	delete curPtr;
	return count;
}
