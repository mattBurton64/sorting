#include <iostream>
#include <string>
#include "empType.h"
using namespace std;

void loadEmp(empType& employee);
void printEmp(empType employee);

int main()
{
	empType employee;
   
	loadEmp(employee);
   printEmp(employee);

	return 0;
}

void loadEmp(empType& employee)
{
   string name;

   cout << "Name:";
	cin >> name;
	employee.setName(name);

   int age;
   
	cout << "Age:"
	cin >> age;
	employee.setAge(age);

	double salary;

	cout << "Salary:"
	cin >> salary;
	employee.setSalary(salary);
}

void printEmp()
{
	name = employee.getName();
	age = employee.getAge();
   salary = employee.getSalary();
	cout << name << " | " << age << " years old | $" << salary << "/yr" << endl;
}
