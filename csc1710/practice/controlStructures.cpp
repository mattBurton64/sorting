/*
Matt Buron
csc1710 03
10/9/20
home/students/mburton/csc1710/test
Add a number of n consecutive integers beginning with x
*/
#include <iostream>
using namespace std;

int main ()
{
  int x = 0, n = 0, total = 0, method = 0;

  cout << "Enter the starting integer:";
  cin >> x;
  cout << "Enter the number of added consecutive digits:";
  cin >> n;
  cout << "Choose method. 1 For 2 While 3 Do While :";
  cin >> method;
  
  while (method < 1 || method > 3)
  {
    cout << "Chose a valid method. 1 For 2 While 3 Do While :";
    cin >> method;
  }

  switch (method)
  {
    case 1:	  
	  for (x; x <= n; x++)
	  {
	    total += x;
	  }
    break;
    case 2:
	  while (x <= n)
	  {
	    total += x;
	    x++;
	  }
    break;
    case 3:
	  do
	  {
	    total += x;
	    x++;
	  }
	  while (x <= n);
    break;
  }
 
  cout << "Total:" << total << endl;

  return 0;
}
