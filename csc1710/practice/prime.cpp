#include <iostream>
using namespace std;

int main ()
{
  int num = 0, count = 2;
  bool prime = true;

  cout << "Enter a number:";
  cin >> num;
  
  //cout << endl;
  while (count <= num)
  { 
    if (num != count)
    {
      if (num % count == 0)
      { 
        cout << count << " ";
        prime = false;
      }
    }  
    count++;
  }

  if (prime)
    cout << endl << num << " is prime." << endl;
  else
    cout << endl << num << " is not prime." << endl;
}
