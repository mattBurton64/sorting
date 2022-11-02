#include "counterType.h"
using namespace std;

void counterType::initializeCounter()
{
   counter = 0;	
}

void counterType::setCounter(int num)
{
	if (num >= 0) //prevent negatives
		counter = num;
	else
		counter = 0;
}

int counterType::getCounter() const
{
	return counter;
}

void counterType::incrementCounter()
{
	counter++;
}

void counterType::decrementCounter()
{
	if (counter > 0) //prevent negatives
		counter--;
}
void counterType::displayCounter() const
{
	cout << counter;
}

counterType::counterType(int num)
{
	if (num >= 0) //prevents negatives
		counter = num;
	else
		counter = 0;
}

counterType::counterType()
{
	counter = 0;
}
