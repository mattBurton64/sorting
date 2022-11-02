/*
Matt Burton
csc1720
01/19/21

Write a counter class that allows you to manipulate a count variable and print its value through public methods and an implimentation file
*/

#include <iostream>

#ifndef COUNTER_TYPE
#define COUNTER_TYPE

class counterType
{
	private:
		int counter;
	public:
		void initializeCounter();
		void setCounter(int num = 0);
		int getCounter() const;
		void incrementCounter();
		void decrementCounter();
		void displayCounter() const;
		counterType(int num);
		counterType();
};

#endif
