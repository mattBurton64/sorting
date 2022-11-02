/*
Matt Burton
9/24/20
csc1710 03
home/students/mburton/csc1710/lab6
Purpose: determine if a given year is a leap year or not
*/
#include <iostream>
#include <string>
using namespace std;

int main ()
{
  int year = 0;
  const int CURRENT = 2020;
  string time = "", time2 = "", isLeap = "";

  cout << "Enter a year as an integer to determine if it is a leap year." << endl;
  cin >> year;
  
  if (year % 4 == 0)
  {
    if (year % 100 == 0)
    {  
      if (year % 400 != 0)
      { 
        //not a leap year
        isLeap = " not";
      }
      //leap year
    }
  } else
    {
      //not a leap year 
      isLeap = " not";
    }  

  if (year > CURRENT)
  {
    //future
    time = " will";
    time2 = " be";
  } else
  {
    //past
    time = " was";
  }

  cout << year << time << isLeap << time2 << " a leap year.";

  return 0;
}

