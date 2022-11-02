/*
Matt Burton
csc1720 02
3/22/21

to compile use:
	g++ -Wall *.cpp

to execute use:
	./a.out
*/
#include "invalidMonth.h"
#include "invalidDay.h"
#include <string>
#include <iostream>
using namespace std;

struct dateType
{
	string name;
	int month;
	int day;
	int year;
	int maxDays;
};

/*
inputDate
_________
	Used to call the input date functions for day, month and year.
	Also calls the check functions for each to ensure the data is useable.
*/
dateType inputDate(dateType&);

/*
checkMonth
__________
	Throws an error if month is not between 1-12.
	Prompts the user to re-enter month until it's
	sufficient.
*/
void checkMonth(dateType&);

/*
checkDay
________
	Throws an error if day is not between 1-maxDays.
	Prompts the user to re-enter day until it's
	sufficient.
*/
void checkDay(dateType&);

/*
checkYear
_________
	Throws an error if year is less than 1582.
	Prompts the user to re-enter year until it's
	greater than 1582.
*/
void checkYear(dateType&);

/*
monthAttributes
_______________
	Used to determine the month name and
	maximum days in the appropriate month.
*/
void monthAttributes(dateType&);

/*
isLeap
______
	Used to determine if a year is a leap year.
	Returns true if year is a leap year.
	Returns false if year is not a leap year.
*/
bool isLeap(dateType);

/*
printDate
_________
	Used to output the date in proper format.
*/
void printDate(dateType);

int main()
{
	dateType date;

	//takes the input
	inputDate(date);

	//outputs the date in the proper format
	printDate(date);

	return 0;
}

dateType inputDate(dateType& date)
{
	cout << "Enter the date in the format MM-DD-YYYY." << endl;

	//stores the month
	cin >> date.month;
	getchar();
	//stores the day
	cin >> date.day;
	getchar();
	//stores the day
	cin >> date.year;

	//errors and input validation
	checkMonth(date);
	checkDay(date);
	checkYear(date);

	return date;
}

void checkMonth(dateType& date)
{
	monthAttributes(date);

	try
	{
		if(date.month < 1 || date.month > 12)
			throw invalidMonth();
	}
	catch (invalidMonth monthObj)
	{
		cout << "message: " << monthObj.what() << endl;

		while(date.month < 1 || date.month > 12)
		{
			cout << "Re-enter month so that it is between 1-12." << endl;
			cin >> date.month;
			monthAttributes(date);
		}
	}
}

void checkDay(dateType& date)
{
	try
	{
		if (date.day < 1 || date.day > date.maxDays)
			throw invalidDay(date.maxDays);
	}
	catch (invalidDay dayObj)
	{
		cout << "message: " << dayObj.what() << date.maxDays << endl;

		while(date.day < 1 || date.day > date.maxDays)
		{
			cout << "Re-enter day so that it is between 1-" << date.maxDays << "." << endl;
			cin >> date.day;
		}
	}
}
void checkYear(dateType& date)
{
	try
	{
		if (date.year < 1582)
			throw date.year;
	}
	catch (int year)
	{
		cout << "message: " << date.year << " is an invalid year." << endl;

		while (date.year < 1582)
		{
			cout << "Re-enter year so that it is greater than 1582." << endl;
			cin >> date.year;
		}
	}
}

void monthAttributes(dateType& date)
{
	//Assignemnt of month names and respective maximum days
	switch(date.month)
	{
		case 1: 	date.name = "January";
					date.maxDays = 31;
			break;
		case 2:	date.name = "Februrary";
					if (isLeap(date))
						date.maxDays = 29;
					else
						date.maxDays = 28;
			break;
		case 3: 	date.name = "March";
					date.maxDays = 31;
			break;
		case 4: 	date.name = "April";
					date.maxDays = 30;
			break;
		case 5: 	date.name = "May";
					date.maxDays = 31;
			break;
		case 6: 	date.name = "June";
					date.maxDays = 30;
			break;
		case 7: 	date.name = "July";
					date.maxDays = 31;
			break;
		case 8: 	date.name = "August";
					date.maxDays = 31;
			break;
		case 9: 	date.name = "September";
					date.maxDays = 30;
			break;
		case 10:	date.name = "October";
					date.maxDays = 31;
			break;
		case 11: date.name = "November";
					date.maxDays = 30;
			break;
		case 12: date.name = "December";
					date.maxDays = 31;
			break;
	}
}

bool isLeap(dateType date)
{
	bool leapYear = false;

	if (date.year % 4 == 0)
	{
   	if (date.year % 100 == 0)
		{
      	if (date.year % 400 == 0)
         	leapYear = true;
      }
      else
         leapYear = true;
   }

	return leapYear;
}

void printDate(dateType date)
{
	cout << date.name << " " << date.day << ", " << date.year << endl;
}
