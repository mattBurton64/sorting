/*
Matt Burton
csc1070
Count bills and total their values
*/

#include <iostream>
using namespace std;

int main ()
{
  //Establish bill count variables for each bill value and an empty total value to display at the end
  int bill1, bill5, bill10, bill20, total;
  
  //Prompt the user for the appropriate values for each bill denomination
  cout << "How many $1 bills were there?" << endl;
  cin >> bill1;
  cout << "How many $5 bills were there?" << endl;
  cin >> bill5;
  cout << "How many $10 bills were there?" << endl;
  cin >> bill10;
  cout << "How many $20 bills were there?" << endl;
  cin >> bill20;

  //Total up the bill values and return the final total
  total = bill1 * 1 + bill5 * 5 + bill10 * 10 + bill20 * 20;
  cout << "The total value is $" << total << " dollars" << endl;   
}
