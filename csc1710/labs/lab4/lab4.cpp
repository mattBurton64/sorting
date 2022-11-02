/*
Matt Burton
9/10/20
csc1710 03
students/home/mburton/csc1710/lab4/
*/

#include <iomanip>
#include <iostream>
using namespace std;

int main ()
{
  //Declare variables from lab instructions
  int p = 17, q = 4, r = 3;
  double j = 3.00, k = 5.0;
  
  //Set the output format
  cout << fixed << showpoint;
  //Print outputs that show the expression and the final result
  cout << "p - q * r = " << p - q * r << endl;
  cout << "p / r = " << p / r << endl;
  cout << "p % r = " << p % r << endl;
  cout << "p / q / r = " << p / q / r << endl;
  cout << "q + r % p = " << q + r % p << endl;
  cout << "q * j / p = " << q * j /p << endl;
  cout << "p / q / j = " << p / q / j << endl;
  cout << "p / j / q = " << p / j / q << endl;
  //Must evaluate k on another line because you can't do /= in cout
  k /= r / q;  
  cout << "k /= r / q = " << k << endl;
  cout << "j / -q = " << j / -q << endl;
  cout << "0.5 * p * r = " << 0.5 * p * r << endl;

  return 0;
}
