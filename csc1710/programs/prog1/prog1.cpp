/*
Matt Burton
9/16/20
csc1710 03
home/students/mburton/csc1710/prog1/
Purpose: Take an input dollar amout and return the fewest coins possible
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{ 
  //Constant coin values
  const int QUARTER = 25, DIME = 10, NICKEL = 5, PENNY = 1;
  //Variables that will be manipulated through io
  int quarters = 0, dimes = 0, nickels = 0, pennies = 0, total = 0;
  double dollars = 00.00;
 
  //Prompt and store user dollar input
  cout << "Enter an amount of money in USD:\n$";
  cin >> dollars;
  
  //Convert to cents
  dollars *= 100;
  //Count and remove quarters
  quarters = dollars / QUARTER;
  dollars -= quarters * QUARTER;
  
  //Count and remove dimes
  dimes = dollars / DIME;
  dollars -= dimes * DIME;  

  //Count and remove nickels
  nickels = dollars / NICKEL;
  dollars -= nickels * NICKEL;

  //Count pennies
  pennies = dollars / PENNY;

  //Sum all coins
  total += quarters + dimes + nickels + pennies;

  cout << endl << setw(4) << "COIN" << setw(15) << "AMOUNT" << endl;
  cout << setfill(' ') << "Quarters" << setw(11) << quarters << endl;
  cout << "Dimes" << setw(14) << dimes << endl;
  cout << "Nickels" << setw(12) << nickels << endl;
  cout << "Pennies" << setw(12) << pennies << endl;
  cout << setw(5) << "TOTAL" << setw(14) << total << endl;
 
  return 0;
}
