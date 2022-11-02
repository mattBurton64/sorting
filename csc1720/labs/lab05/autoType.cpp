/* Name: Matt Burton
   Date: 2/9/21
   Class: csc1720
   Location: students/mburton/csc1720/labs/lab05/autoType.cpp

   Impliments the autoType class
*/

#include "autoType.h"
#include <iomanip>

autoType::autoType(double od_in, double fl_in, double mpg_in, double fc_in)
{
   fuelCap = fc_in;
	setAutoSpecs(od_in, fl_in, mpg_in);
}

void autoType::setAutoSpecs(double od_in, double fl_in, double mpg_in)
{	
	if(od_in >= odometer && fl_in > 0 && fl_in <= fuelCap && mpg_in > 0)
   {
		fuelLevel = fl_in;
	   mpg = mpg_in;
		odometer = od_in;
	} else {
		if (od_in < 0)
			cerr << "  Err: 'odometer' must be a positive double." << endl;
		if (od_in < odometer)
			cerr << "  Err: 'odometer' must be greater than the previous odometer reading." << endl;
		if (fl_in < 0 || fl_in > fuelCap)
			cerr << "  Err: 'fuel' must be a positive double less than." << fuelCap << endl;
		if (mpg_in < 0)
			cerr << "  Err: 'mpg' must be a positive double." << endl;
	}
}

string autoType::getAutoSpecs(void)const
{
   ostringstream sout;

   sout << fixed << showpoint << setprecision(2);
   sout << "Miles = " << odometer;
   sout << ", Fuel Level = " << fuelLevel;
   sout << ", Efficiency = " << mpg;
	sout << ", Fuel Capacity = " << fuelCap;

   return sout.str();
}
     
void autoType::drive(double distance)
{
   //Determine the max dist you can travel 
   //based on the current fuelLevel.
   //Compare the requested distance to maxDistance
   //to see if that is possible and act accordingly.
   double maxDistance = fuelLevel*mpg; 
   if(distance <= maxDistance) {
      odometer += distance;
      fuelLevel -= distance/mpg;
   } else {
      cerr << "  Err: Out of gas after " << maxDistance << " miles." << endl;
      odometer += maxDistance;
      fuelLevel = 0;
   }
}

void autoType::addFuel(double fl_in)
{
	if ((fuelLevel + fl_in) <= fuelCap && fl_in > 0)
		fuelLevel += fl_in;
	else
	{
		if (fl_in <= 0)
			cerr << "  Err: Add a positive double amount of fuel." << endl;
		if ((fuelLevel + fl_in) > fuelCap)
		{
			cerr << "  Err: "<< (fuelLevel + fl_in) - fuelCap << " gallons of fuel exceed the tanks capacity.\n       The tank is now full." << endl;
			fuelLevel = fuelCap;
		}
	}
}
