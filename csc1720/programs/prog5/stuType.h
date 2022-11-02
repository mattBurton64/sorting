#ifndef STUTYPE
#define STUTYPE
#include <iostream>
#include <iomanip>

class stuType
{
   private:
      string fName;
      string lName;
      double gpa;
   public:
      stuType();
      stuType(string inFirst, string inLast, double ingpa);
      friend ostream& operator<<(ostream& osObject, const stuType&);
      bool operator<(const stuType&);
      bool operator>(const stuType&);
      bool operator==(const stuType&);
      bool operator!=(const stuType&);
      bool operator<=(const stuType&);
      bool operator>=(const stuType&);
		double getGPA();
};

stuType::stuType()
{
   fName = "";
   lName = "";
   gpa = 0;
}

stuType::stuType(string inFirst, string inLast, double ingpa)
{
   fName = inFirst;
   lName = inLast;
	gpa = ingpa;
}

ostream& operator<<(ostream& osObject, const stuType& stu)
{
   osObject << setw(12) << right << stu.fName << " " << setw(12) << left << stu.lName << " " << showpoint << setprecision(2) << stu.gpa << endl;
   return osObject;
}

bool stuType::operator<(const stuType& stu)
{
   return (gpa < stu.gpa);
}

bool stuType::operator>(const stuType& stu)
{
   return(gpa > stu.gpa);
}

bool stuType::operator==(const stuType& stu)
{
   return (gpa = stu.gpa);
}

bool stuType::operator!=(const stuType& stu)
{
   return (gpa = stu.gpa);
}

bool stuType::operator>=(const stuType& stu)
{
   return(gpa >= stu.gpa);
}

bool stuType::operator<=(const stuType& stu)
{
   return (gpa <= stu.gpa);
}

double stuType::getGPA()
{
	return gpa;
}
#endif
