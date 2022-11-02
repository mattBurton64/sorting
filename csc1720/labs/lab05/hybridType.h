/* Name: Matt Burton
   Date: 2/9/21
   Class: csc1720
   Location: students/mburton/csc1720/labs/lab05/hybridType.h

	defines the hyrbidType class
*/
#include <iostream>
#include "autoType.h"
using namespace std;

#ifndef HYBRID_TYPE
#define HYBRID_TYPE

class hybridType : public autoType
{
   private:
      double chargeLevel;
      double chargeEff;
   public:
		/* Function used to set the charge level to the input charge value.
		 * The charge can not be set to a negative number.
		 * Post Condition: chargeLevel = ch_in
		 */
      void setChargeLevel(double ch_in);
		/* Function used to get the charge level.
		 * postCondition: It returned the value stored in chargeLevel
		 */
		double getChargeLevel() const;
		/* Funtion to set charge efficiency to the input value.
		 * If the input value is <=0 then an error is returned.
		 * post condition: chargeEff = ef_in
		 */ 
		void setChargeEfficiency(double ef_in);
		/* Funtion to get the charge efficiency.
		 * postCondition: returned chargeEff
		 */
		double getChargeEfficiency() const;
		//constructor that passes onto the autoType constructor
		//hybridType(double od_in = 0, double fl_in = 0, double mpg_in = 0, double fc_in = 20);
};
#endif
