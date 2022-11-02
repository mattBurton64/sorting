/* Name: Matt Burton
   Date: 2/9/21
   Class: csc1720
   Location: students/mburton/csc1720/labs/lab05/autoMain.cpp

	tests the methods of autoType and hybridType

	compile with
		g++ -Wall autoMain.cpp autoType.cpp hybridType.cpp
*/
#include "autoType.h"
#include "hybridType.h"
#include <iomanip>

int main()
{ 

   autoType dodgeRam(201, 10.32, 19.1);

	cout << dodgeRam.getAutoSpecs() << endl;
	cout << " Requesting to drive 400 miles." << endl;
   dodgeRam.drive(400);
	cout << dodgeRam.getAutoSpecs() << endl;
	
	cout << " Setting the odometer to 0." << endl;
	dodgeRam.setAutoSpecs(0, 10, 10);
	cout << " Adding -5 gallons of fuel. addFuel(-5)" << endl;
	dodgeRam.addFuel(-5);
	cout << " Adding 100 gallons of fuel. addFuel(100)" << endl;
	dodgeRam.addFuel(100);

   return 0;
}
