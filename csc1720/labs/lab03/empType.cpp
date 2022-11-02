/* 
   Author: Matt Burton
   Date: 1/26/21
   Class: CSC-1720
   Code location: ~/csc1720/labs/lab03/
   
   About: 
*/

#include"empType.h"

bool empType::compareTo(const empType& otherEmp) const
{
	if (id > otherEmp.id)
	{
		return true;
	} else
		return false;
}

empType::empType(int iId, string iName, int iAge, double iSalary)
{
	if (iAge < 18)
		cerr << "Error: " << iAge << " is not greater than 18." << endl;
	else
		age = iAge;

	if (iName.length() < 1)
		cerr << "Error: " << iName << " is too short." << endl;
	else
		name = iName;

	if (iId < 0)
		cerr << "Error: " << iId << " must be positive." << endl;
	else
		id = iId;

	if (iSalary < 0)
		cerr << "Error: " << iSalary << " must be positive." << endl; 
	else
		salary = iSalary;
}

empType::empType()
{
	id = 0;
	age = 0;
	name = "";
	salary = 0.0;
}

void empType::setName(string iname)
{
   name = iname;
}


void empType::setAge(int iage)
{
   age = iage;
}


void empType::setSalary(double isalary)
{
   salary = isalary;
}

void empType::setId(int iId)
{
	id = iId;
}

string empType::getName(void) const
{
   return name;
}


int empType::getAge(void) const
{
   return age;
}


double empType::getSalary(void) const
{
   return salary;
}


int empType::getId(void) const
{
	return id;
}
