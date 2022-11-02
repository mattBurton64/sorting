/*
Matt Burton
csc1720
3/22/21
A class for handling months outside of 1-12.
*/
#ifndef INVALID_MONTH
#define INVALID_MONTH
#include <string>
using namespace std;

class invalidMonth
{
	private:

		string message;

	public:

		//Constructor
		invalidMonth()
		{
			message = "The month entered is invalid.";
		}

		//Function for returning the error message
		string what()
		{
			return message;
		}
};

#endif
