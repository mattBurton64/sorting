/*
Matt Burton
csc1720 02
03/31/21

an error hanndling class for invalid exponent values.
*/
#ifndef INVALID_POWER
#define INVALID_POWER
#include <string>
using namespace std;

class invalidPower
{
	private:

		string message;

	public:

		//Constructor
		invalidPower()
		{
			message = "The base must be positive.";
		}

		//Parameterizede constructor
		invalidPower(string what)
		{
			message = what;
		}
		//Function for returning the error message
		string what()
		{
			return message;
		}
};

#endif
