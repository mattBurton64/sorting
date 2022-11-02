/*
Matt Burton
csc1710 03
10/8/20
home/students/mburton/csc1710/lab8
Calculate factorials
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
  int x = 0, count = 1, terms = 0;
  double seriesA = 0.0, sum = 0.0;
  long factorial = 1, factorial2 = 1;

  //user prompt and input
  cout << "Enter an integer to find its factorial(1-25):";
  cin >> x;

  while (x <= 0 || x > 25)
  {
    cout << "Invalid. Enter an integer greater than 0 and less than 25:";
    cin >> x;
  }

  //facotorial computation and output
  cout << "Factorial" << endl;
  cout << x << "! = "; 
  for (int i = 1; i <= x; i++)
  {
    factorial *= i;
    cout << i;
    if (i <= x - 1)
      cout << " * ";
  }
  cout << " = " << factorial << endl;

  //user prompt and input
  cout << "Enter an ODD integer to find its double factorial(1-25):";
  cin >> x;

  while (x <= 0 || x > 25 || x % 2 == 0)
  {
    cout << "Invalid. Enter an ODD integer between 1-25:";
    cin >> x;
  }

  //double factorial
  cout << "Double Factorial" << endl;
  cout << x << "! = ";
  do
  {
    if (count % 2 != 0)
    {
      factorial2 *= count;
      cout << count;
      if (count <= x -1)
        cout << " * ";
    }
    count++;
  }  
  while (count <= x);
  cout << " = " << factorial2 << endl;

  //user prompt and input
  cout << "Enter the first value of the geometric series:";
  cin >> seriesA;
  cout << "Enter how many terms of the series you want to see:";
  cin >> terms;

  while (terms <= 0)
  {
    cout << "Invalid. Enter a positive integer:";
    cin >> terms;
  }

  //geometric series
  cout << "Sum of " << terms << " terms, a=" << seriesA << ", r=0.5, is ";
  for (int i = 0; i < terms; i++)
  {
     sum += seriesA;
     seriesA *= 0.5;
  }
  cout << showpoint << sum << endl;

  return 0;
}
