/* Name: Matt Burton
   Date: 2/16/21
   Class: csc1720 02
   Location: students/mburton/csc1720/labs/lab06

   Implementation file for the derived class autoType:  
   Includes set, get, and simple mutator methods.
*/

#include"hybridType.h"
#include<iomanip>

void hybridType::setChargeLevel(double chargeLevel_in)
{
   if (chargeLevel_in > 0.0 && chargeLevel <= 100.0)
      chargeLevel = chargeLevel_in;
   else
      cerr << "Charge level must be > 0% and <= 100%" << endl;
}

double hybridType::getChargeLevel(void)const
{
   return chargeLevel;
}

void hybridType::setChargeEfficiency(double chargeEff_in)
{
   if (chargeEff_in > 1.0)
      chargeEff = chargeEff_in;
   else
      cerr << "Charge efficiency must be > 1.0" << endl;
}

double hybridType::getChargeEfficiency()const
{
   return chargeEff;
}

void hybridType::drive(double distance)
{
   if (distance < 0)
   {
      cerr << "Cannot drive negative miles." << endl;
      return;
   }
 
 	//electric
	double electricDistance = 0.0;

	if (chargeLevel > 20.0)
   	electricDistance = (chargeLevel - 20.0) * chargeEff; 

   if(distance <= electricDistance) 
   {
		odometer += distance;
		chargeLevel -= distance / chargeEff;
		distance -= electricDistance;
	}
	
	//gas
	if (distance > 0)
	{
		double preOdo = odometer;
		autoType::drive(distance);
		if(odometer - preOdo > 0)
			chargeLevel += (odometer - preOdo) / 20.0;
	}
 	else
   {
      cerr << "Out of gas after " << distance << " miles." << endl;
      odometer += distance;
      chargeLevel = 0;
   }
}

string hybridType::getAutoSpecs()const
{
	ostringstream sout;

	sout << autoType::getAutoSpecs();
	sout << ", Charge Level = " << chargeLevel;
	sout << ", Charge Efficiency = " << chargeEff;

	return sout.str();
}

hybridType::hybridType(double od_in, double fc_in, double fl_in, double mpg_in, double ch_in, double ef_in)
	: autoType(od_in, fc_in, fl_in, mpg_in)
{
	if (ch_in > 0.0 && ch_in <= 100.0)
		chargeLevel = ch_in;
	else
		chargeLevel = 0.0;

	if (ef_in > 1.0)
		chargeEff = ef_in;
	else
		chargeEff = 0.0;
}

hybridType::hybridType()
{
		chargeLevel = 0.0;
		chargeEff = 0.0;
}
