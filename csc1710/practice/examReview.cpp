/*
Matt Burton
csc1710 03
11/19/20
home/students/mburton/csc1710/practice/
Exam review
*/
#include <iostream>
using namespace std;

struct employeeType
{
  string FName, LName;
  int ID;
  string department;
  double salary; 
  double bonus; 
};

void input(employeeType& employee); 
double calcBonus(employeeType employee);
void output(employeeType employee);

int main()
{
  employeeType employee;

  input(employee);
  employee.bonus = calcBonus(employee);

  cout << "Bonus:" << employee.bonus << endl;

  output(employee);

  return 0;
}

void input(employeeType& employee)
{
  cout << "First name:";
  cin >> employee.FName;

  cout << "Last name:";
  cin >> employee.LName;

  cout << "ID:";
  cin >> employee.ID;

  cout << "Department:";
  cin >> employee.department;
  
  cout << "Salary:";
  cin >> employee.salary;
}

double calcBonus(employeeType employee)
{
  double bonus;
  bonus = employee.salary * 0.014;
  return bonus;
}

void output(employeeType employee)
{
  cout << "==============" << endl;
  cout << employee.LName << ", " << employee.FName << endl;
  cout << employee.ID << endl;
  cout << employee.department << endl;
  cout << "$" << employee.salary << " yearly" << endl;
  cout << "+$" << employee.bonus << endl;
}
