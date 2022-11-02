/*
Matt Burton
csc1720
3/22/21
A class for handling days outside of their respective months day's.
*/
#ifndef INVALID_DAY
#define INVALID_DAY
#include <string>
using namespace std;

class invalidDay
{
	private:

		string message;

	public:

		//Constructor
		invalidDay()
		{
			message = "The day entered is invalid.";
		}

		//Parameterized constructor for custom error messages
		invalidDay(int maxDays)
		{
			message = "The day entered must be less than ";
			message += maxDays;
		}

		//Function for returning the error message
		string what()
		{
			return message;
		}
};

#endif
