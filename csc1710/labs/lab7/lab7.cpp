/*
Matt Burton
csc1710 03
9/30/20
students/mburton/csc1710/lab7
Create a conversion chart for farenheit to celcius and kelvin with a input range and increment
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
  double low = 0.0, high = 0.0, count = 0.0, far = 0.0, cel = 0.0, kel = 0.0, increment = 0.0, min= 0.0, max = 100.0, width = 0.0;

  //into and user prompt
  cout << "Farenheit Conversion Table" << endl;
  cout << "Enter the range as: min max (" << min <<  " - " << max << "). Ensure the first number is smaller than the latter." << endl;
  cin >> low >> high;
  
  //input validation
  while (high <= low)
  { 
    cout << "Enter a valid max." << endl;
    cin >> high;
  }

  while (low < min)
  { 
    cout << "Enter a valid min." << endl;
    cin >> low;
  }

  while (high > max)
  { 
    cout << "Enter a valid max." << endl;
    cin >> high;
  }

  //asks the user to define the increment rate
  while (increment == 0.0)
  {
    cout << "Enter the increment amount for the table." << endl;
    cin >> increment;
  }
  
  //prints header
  cout << setw(12) << "FARENHEIT" << setw(10) << "CELCIUS" << setw(9) << "KELVIN" << endl;
  cout << setw(33) << "================================" << endl;
  cout << showpoint << fixed << setprecision(2);
  
  //converts and outputs table
  count = low;
  while (count <=high)
  {
    far = count;
    cel = (far - 32) * 5.0 / 9.0;
    kel = (far - 32) * 5.0 / 9.0 + 273.15;
    
    cout << setw(10) << far << setw(11) << cel << setw(10) << kel << endl;
    count += increment;
  }
  
  return 0;
}
