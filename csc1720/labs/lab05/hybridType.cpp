/* Name: Matt Burton
   Date: 2/9/21
   Class: csc1720
   Location: students/mburton/csc1720/labs/lab05/hybridType.cpp

	impliments the hypbridType class
*/
#include "hybridType.h"

void hybridType::setChargeLevel(double ch_in)
{
	if (ch_in > 0)
		chargeLevel = ch_in;
	else
		cerr << "  Err: Charge level must be a positive double." << endl;
}

double hybridType::getChargeLevel() const
{
	return chargeLevel;
}

void hybridType::setChargeEfficiency(double ef_in)
{
	if (ef_in > 0)
		chargeEff = ef_in;
	else
		cerr << "  Err: Charge efficiency must be a positive double." << endl;
}

double hybridType::getChargeEfficiency() const
{
	return chargeEff;
}
/*
hybridType::hybridType(double od_in, double fl_in, double mpg_in, double fc_in)
{
   autoType(od_in, fl_in, mpg_in, fc_in);
}*/
