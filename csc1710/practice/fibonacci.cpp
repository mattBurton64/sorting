#include <iostream>
using namespace std;

int main ()
{
  int last1 = 0, last2 = 0, n = 0, current = 0, count = 3;

  cout << "Enter the first two digits of your sequence." << endl;
  cin >> last1 >> last2;
  cout << "What nth number in the sequence would you like to know?" << endl;
  cin >> n;

  cout << last1 << " " << last2 << " ";

  if (n == 1) //if n is 1 it outputs the first
    current = last1;
  else if (n == 2) //if n is 2 it outputs the second
    current = last2;
  else
  {
    while (count <= n) //for all other n it updates current until current is the nth digit
    {  
      current = last2 + last1;
      last1 = last2;
      last2 = current;
      count++;
      cout << current << " ";
    }
  }

  cout << endl << n << " number in the sequence is " << current << endl;

  return 0;
}
