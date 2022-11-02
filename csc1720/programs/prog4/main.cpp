/*
Matt Burton
csc1720 02
03/30/21
___________

Calculates the power of j^k using recursion with input validation and overflow protection.

COMPILE
_______

	g++ -Wall *.cpp -o power

EXECUTE
_______

	./power.out
*/


#include "invalidPower.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <cstdlib>
using namespace std;


/*
AGAIN
_____

	Calls the input() and repower() repeatedly.
*/
void again();


/*
INPUT
_____

	Takes user input for base j and exponent k.
	Throws an error if j < 1 and calls input().
*/
void input(int& j, int& k);


/*
REPOWER
_______

	If k < 0 then 1 / (repower(j, -k)) is returned.
	If k = 0 then 1 is returned.
	If k = 1 then j is returned.
	If k > 1 then j^k is returned.
	Returns an error if j^k is too big.
*/
double repower(int j, int k);


int main()
{
	again();
	return 0;
}


void again()
{
	int j, k;

	input(j, k);
	cout << j << "^" << k << " = " << fixed << repower(j, k) << endl;

	again();
}


void input(int& j, int& k)
{

	try
	{
		cout << "Enter base: ";
		cin >> j;
		
		if(j < 1)
			throw invalidPower();
	}
	catch (invalidPower powerObj)
	{
		cout << "message: " << powerObj.what() << endl;
		input(j,k);
	}
	
	cout << "Enter power: ";
	cin >> k;
}


double repower(int j, int k)
{
	if (k < 1)
		return (1 / repower(j, -k));

	if (k == 0)
		return 1;

	if (k == 1)
		return j;

	if (k > 1)
	{
		long int result;

		try
		{
			result = (j * repower(j, k - 1));

			if (abs(result) > INT_MAX)
				throw invalidPower("The answer is too big.");	
		}
		catch(invalidPower powerObj)
		{
			cout << "message: " << powerObj.what() << endl;
			again();
		}
		
		return result;
	}
}
