/* Name: Matt Burton
   Date: 2/9/21
   Class: csc1720
   Location: students/mburton/csc1720/labs/lab05/autoType.h

   Used to define the autoType class
*/
#include<iostream>
using namespace std;

#ifndef AUTO_TYPE
#define AUTO_TYPE

class autoType
{
   private:
      double odometer = 0;
      double fuelLevel = 0;
      double mpg = 0;
		double fuelCap = 0;
   public:
      /* Constructor for the class with parameters
       * Sets the odometer, fuelLevel and mpg.  If no paramters
       * are given it uses the default values.
       * Postcondition - odometer=od_in, fuelLevel=fl_in
       *                 mpg=mpg_in
       * NOTE: with this constructor, a default constructor is
       * NOT needed.
       */
      autoType(double od_in=0, double fl_in=0, double mpg_in=0, double fc_in=20);
      
      /* Function to set the auto specs - odometer, fuelLevel, and mpg.
       * Postcondition - odometer=od_in, fuelLevel=fl_in
       *                 mpg=mpg_in
       */
      void setAutoSpecs(double od_in, double fl_in, double mpg_in);

      /* Function to build a string containing the odometer, fuelLevel,
       * and mpg.  The values will be rounded off to two decimal places.
       * Postcondition - the string is returned.
       */
      string getAutoSpecs(void)const;

      /* Function to drive the car the distance given in a parameter.
       * The function will update the odometer and fuel amounts and
       * monitor if you are trying to drive more than you have fuel.
       * If you do not have enough fuel to drive the distance, the 
       * odometer and fuel will be updated based on how far you actually
       * can drive.
       */ 
      void drive(double distance);

		/* Function to add fuel to the cars existing fuel. The function
	    * will fill he tank unntil the tank is full, and the remaining
		 * is output through a cerr message. If you add negative fuel an
		 * error is returned.
		 * postCondition: FuelLevel += fl_in and is less than or equal to fuelCap
	    */
		void addFuel(double fl_in);
};
#endif
