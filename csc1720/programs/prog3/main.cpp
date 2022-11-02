/*
Matt Burton
csc1720
03/15/21

compile with g++ -Wall *.cpp
I get a load of errors still from the templating and could not resolve this issue.

execute with ./a.out < fileName.txt
*/
#include <iostream>
#include <string>
#include "arrayListType.h"
#include "unorderedArrayListType.h"
#include "uniqueListType.h"
using namespace std;

template<typename T>
void load(unorderedArrayListType<T>&);

int main()
{
	double price, expenses;
	uniqueListType<string> winnerList(4);

	cout << "The winner of a set of 4 movie passes at the Palladium Regal Theater is " << winnerList.getAt(0) << "." << endl;
	
	cout << "The winner of a $100 Amazon gift card is " << winnerList.getAt(1) << "." << endl;
	cout << "The winner of a set of 4 passes to Wet and Wild is " << winnerList.getAt(2) << "." << endl;
	cout << "The winner of a dinner for two at Blue Water Grille is " << winnerList.getAt(3) << "." << endl;
	cout << "The winner of the grand prize of a Playstation 5 is " << winnerList.getAt(4) << "." << endl;

	cout << "Enter the price per ticket: " << endl;
	cin >> price;
	while (price < 0)
	{
		cout << "The price must be greater than zero. Enter the price per ticket: " << endl;
		cin >> price;
	}		

	cout << "Enter the total expenses: " << endl;
	cin >> expenses;
	while (expenses < 0)
	{
		cout << "The expenses must be greater than zero. Enter the total expenses: " << endl;
		cin >> expenses;
	}		

	cout << "The total profits made by the raffle were $" << showpoint(2) << -expenses + price * 10 << endl;
	return 0;
}
/*
 	load
	____

	used to read input and append new data at the end of the list
	as long as not EOF or full
	pre condition: A list exists which is not full and 
						a .txt file is being input
	post condition: An updated list is returned with all input values
						now included in the list and the length adjusted 
						appropriately
*/
template<typename T>
void load(unorderedArrayListType<T> &list)
{
	T iData;

	getLine(cin, iData);
	while(!list.isFull() or iData == EOF)
	{
		list.insertEnd(iData);
		getLine(cin, iData)
	}
}
