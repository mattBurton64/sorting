/******************************
Matt Burton
csc1710 03
9/3/20
/home/students/mburton/csc1710/lab3/lab3.cpp
Purpose:Calculate the weighted average of user input values
*******************************/

#include <iostream>
using namespace std;

int main ()
{
  //Variables for score storing and manipulating                     total is for return
  double lab1, lab2, lab3, lab4, quiz1, quiz2, quiz3, program, test, total = 0;

  //Prompt input and assign all the scores to their variables
  cout << "Input the four lab grades, three quiz grades, a program grade, and a test grade all separated by a space." << endl;
  cin >> lab1 >> lab2 >> lab3 >> lab4 >> quiz1 >> quiz2 >> quiz3 >> program >> test;
 
  //Multiply by ten to make these scores out of 100 instead of 0-10
  lab1 *= 10;
  lab2 *= 10;
  lab3 *= 10;
  lab4 *= 10;
  quiz1 *= 10;
  quiz2 *= 10;
  quiz3 *= 10;

  //Calculating weighted average and storing in total
  total += ((lab1 + lab2 + lab3 + lab4) / 4) * 0.1;
  total += ((quiz1 + quiz2 + quiz3) / 3) * 0.1;
  total += program * 0.3;
  total += test * 0.3;

  //Filler data to compensate for not having anything in the final grade portion of the total 100%
  total += 20;

  //Outputting the total weighted average
  cout << "Your weighted average is " << total << "%" << endl;

  return 0;
}
