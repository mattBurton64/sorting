/******************************
Matt Burton
csc1710 03
9/11/20
/home/students/mburton/csc1710/
Purpose:User enters heigh in feet and inches and it gets converted to cm
*******************************/

#include <iostream>
using namespace std;

int main ()
{
  //Creates double variables so the decimals are maintained
  double feet = 0.0, inches = 0.0, cm = 0.0;
  //Prompt the user for their height
  cout << "Enter your height in feet and inches" << endl;
  cin >> feet >> inches;
  
  //Convert feet to inches
  feet *= 12.0;
  //Add those inches to the inputted inches
  inches += feet;
  //Convert inches to centimeters with the conversion amount
  cm = inches * 2.54;

  //Output the converted height
  cout << "Your height in centimeters is: " << cm << endl;
  return 0;
}
