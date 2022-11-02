#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int roll(int sides);

int main ()
{
  srand(time(0));
  int sides = 0, rolls = 0, output = 0;
 
  cout << "How many sides on the die:";
  cin >> sides;
  
  while (sides < 2)
  {
    cout << "Enter at least 2 or more sides";
    cin >> sides;
  }
  
  cout << "How many times should it roll:";
  cin >> rolls;
  
  while (rolls < 1)
  {
    cout << "Enter at least 1 or more rolls:";
    cin >> rolls;
  }
  
  for(int i = 1; i <= rolls; i++)
    roll(sides);

  return 0;
}

int roll(int sides)
{

  int output = rand() % sides + 1;
  cout << output;
  return output;
}
