#include "empType.h"

void empType::setName(string empName)
{
	name = empName;
}

void empType::getName(string& empName)
{
   empName = name;
}

void empType::setAge(int empAge)
{
	age = empAge;
}

void empType::getAge(int& empAge)
{
   empAge = age;
}

void empType::setSalary(double empSalary)
{
	salary = empSalary;
}

void empType::getName(double& empName)
{
   empSalary = salary;
}

void empType::empType(string empName, int empAge, double empSalary)
{
	name = empName;
	age = empAge;
	salary = empSalary;
}

void empType::empType()
{
	name = "";
	age = 0;
	salary = 0.0;
}
