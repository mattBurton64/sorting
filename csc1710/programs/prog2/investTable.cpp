/*
Matt Burton
10/6/20
csc1710 03
home/students/mburton/csc1710/prog2
Creates a table showing the investment growth based on user inputs
aiming for 100%, tried to follow the directions as presented
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main ()
{
  double init = 0, deposit = 0, years = 0, rate = 0, rateChange = 0, totalInvest = 0, currentValue = 0, count = 0, gain = 0;

  cout << "Enter initial investment:"; //initial investment
  cin >> init;
  
  while (init <= 0)//input validation 5%
  {
    cout << "Enter a valid double greater than zero:";
    cin >> init;
  }

  cout << "Enter montly deposit:"; //monthly deposit
  cin >> deposit;
  
  while (deposit <= 0)
  {
    cout << "Enter a valid double greater than zero:";
    cin >> deposit;
  }

  cout << "Enter number of years:"; //number of years
  cin >> years;
  
  while (years <= 0)
  {
    cout << "Enter a valid double greater than zero:";
    cin >> years;
  }

  cout << "Enter interest rate as a decimal:"; //interest rate
  cin >> rate;
  
  while (rate <= 0)
  {
    cout << "Enter a valid double greater than zero:"; 
    cin >> rate;
  }

  cout << "Enter change in interest rate per year as a decimal:"; //rate of rate change
  cin >> rateChange;
  
  while (rateChange <= 0)
  {
    cout << "Enter a valid double greater than zero:";
    cin >> rateChange;
  }

  //table

  cout << "\n\n" << setw(29) << "Investment Table" << endl;
  cout << "\n" << setw(7) << "Month" << setw(16) << "Total Invested" << setw(15) << "Current Value" << endl;
  cout << setw(18) << "($)" << setw(13) << "($)" << endl;

  while (count < 40)
  { 
    cout << "_";
    count++;
  }
  
  count = 0;
  totalInvest = init - deposit;
  currentValue = init - deposit;
  cout << endl;
  while (count <= (years * 12))
  {
    //apr rate change 5%
    if (static_cast<int>(count) % 12 == 0)
      rate += rateChange;
    totalInvest += deposit;
    currentValue = totalInvest * pow(1.0 + rate, count / 12.0); 
    cout << setw(5) << setprecision(0) <<  count << fixed;
    cout << setw(14) << setprecision(2) << totalInvest;
    cout << setw(14) << setprecision(2) << currentValue << endl;
    count++;
  }
  
  //capital gain 5%
  gain = currentValue - totalInvest;
  cout << "Capital Gain: " << gain << endl;

  return 0;
}
