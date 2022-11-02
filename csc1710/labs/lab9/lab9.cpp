/*
Matt Burton
csc1710 03
10/15/20
home/students/mburton/csc1710/lab9
Calculate factorials with user defined functions
*/
#include <iostream>
#include <iomanip>
using namespace std;

long int fact(int x);
long int doubleFact(int x);
double geoSeries(int terms, double seriesA);

int main ()
{
  int x = 0, count = 1, terms = 0;
  double seriesA = 0.0;

  //user prompt and input
  cout << "Enter an integer to find its factorial(1-25):";
  cin >> x;

  while (x <= 0 || x > 25)
  {
    cout << "Invalid. Enter an integer greater than 0 and less than 25:";
    cin >> x;
  }

  //factorial computation and output
  cout << "Factorial: " << x << "! = " << fact(x) << endl;

  //user prompt and input
  cout << "Enter an ODD integer to find its double factorial(1-25):";
  cin >> x;

  while (x <= 0 || x > 25 || x % 2 == 0)
  {
    cout << "Invalid. Enter an ODD integer between 1-25:";
    cin >> x;
  }

  //double factorial
  cout << "Double Factorial: " << x << "! = " << doubleFact(x) << endl;

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
  cout << "Sum of " << terms << " terms, a=" << seriesA << ", r=0.5, is " << showpoint << geoSeries(terms, seriesA) << endl;

  return 0;
}

long int fact(int x)
{
  long int factorial = 1;
  for (int i = 1; i <= x; i++)
  {
    factorial *= i;
  }
  return factorial;
} 

long int doubleFact(int x)
{
  int count = 1;
  long int factorial = 1;
  do
  {
    if (count % 2 != 0)
    {
      factorial *= count;
    }
    count++;
  }  
  while (count <= x);
  return factorial;
}

double geoSeries(int terms, double a)
{
  double sum = 0.0;
  for (int i = 1; i < terms; i++)
  {
     sum += a;
     a *= 0.5;
  } 
  return sum;
}
