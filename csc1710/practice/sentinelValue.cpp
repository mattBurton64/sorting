/*
Matt Buron
csc1710 03
10/9/20
home/students/mburton/csc1710/test
Multiply input values until a multiple of 5 is input
*/
#include <iostream>
using namespace std;

int main ()
{
  int input = 1, total = 1;
 
  while (input % 5 != 0)
  {
    cout << "Enter an integer:";
    cin >> input;
    total *= input;
    cout << total << endl;
  }

  input = 1;
  total = 1;

  do 
  {
    cout << "Enter an integer:";
    cin >> input;
    total *= input;
    cout << total << endl;
  }
  while (input % 5 != 0);
 
  return 0;
}  
