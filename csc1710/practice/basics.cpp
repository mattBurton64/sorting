/******************************
Matt Burton
csc1710 03
9/3/20
/home/students/mburton/csc1710/
Purpose:First program
*******************************/

#include <iostream>
using namespace std;

int main ()
{
  int variable;
  cin >> variable;
  int x = 0;
  x = x % variable;
  cout << x << endl;  
  int y = 1;
  y = y %  variable;
  cout << y << endl;
  int z = 2;
  z = z % variable;
  cout << z << endl;
  int a = 3;
  a = a % variable;
  cout << a << endl;  
  return 0;
}
