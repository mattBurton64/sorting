/* Name: Matt Burton
   Date: 2/16/21
   Class: csc1720 02
   Location: students/mburton/csc1720/labs/lab06

   this is the header file for the derived autoType class: hybridType
   hybridType is a type of autoType, in which it has two more 
   private instance variable,
                 the amount of charge in its batteries --> chargeLevel
                 and the battery/charge efficiency --> chargeEff
*/
#include<iostream>
#include "autoType.h"
using namespace std;

#ifndef HYBRID_TYPE
#define HYBRID_TYPE

class hybridType: public autoType
{
   private:
      double chargeLevel;
      double chargeEff;
   public:
     /*
      setChargeLevel - use to update the private instance variable
                       chargeLevel of a hybridType.  
                       Max change level is 100%.
      pre-conditions: parameter must be a double in percent form
      post-conditions: chargeLevel = chargeLevel_in
      */
      void setChargeLevel(double chargeLevel_in);

     /*
      getChargeLevel - use to "get" the value of chargeLevel 
                       when it is not directly available
                       ((when outside the class))
      post-conditions: returns chargeLevel in percent form
      */
      double getChargeLevel(void)const;

     /*
      setChargeEfficiency - use to update the private instance variable
                            chargeEff of a hybridType
      pre-conditions: parameter must be a double
      post-conditions: chargeEff = chargeEff_in
      */
      void setChargeEfficiency(double chargeEff_in);

     /*
      getChargeEfficiency - use to "get" the value of chargeEff
                            when it is not directly available 
                            ((outside the class))
      post-conditions: returns chargeEff
      */
      double getChargeEfficiency()const;
		/*
			getAutoSpecs() - use to "get" the value of odometer
								  fuelLevel, fuelCap, mpg, chargeLevel
								  and chargeEff when it is not directly
								  available
			post-conditions: returns a string of car specs 
		*/

      /* Function to drive the car the distance given in a parameter.
         The function will update the odometer and charge amounts and
         monitor if you are trying to drive more than you have charge.
         If you do not have enough charge to drive the distance, the 
         odometer and charge will be updated based on how far you actually
         can drive.
       */
      void drive(double distance);
 
      string getAutoSpecs() const;
		//	parameterized constructor
		hybridType(double od_in, double fc_in, double fl_in, double mpg_in, double ch_in, double ef_in);
		//	constructor
		hybridType();
};

#endif
