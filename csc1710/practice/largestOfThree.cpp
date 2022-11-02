#include <iostream>
using namespace std;

int solutionOne(int x, int y, int z);
int solutionTwo(int x, int y, int z);
int solutionThree(int x, int y, int z);
int solutionFour(int x, int y, int z);
int solutionFive(int x, int y, int z);

int main()
{
  int x = 0, y = 0, z = 0, method, largest = 0; //used to store the largest number

  cout << "Enter three numbers." << endl;
  cin >> x >> y >> z;
  
  cout << "Chose solution method[1-5]" << endl;
  cin >> method;
  switch (method)
  {
    case 1:
      largest = solutionOne(x, y, z);
      break;
     case 2:
      largest = solutionTwo(x, y, z);
      break;
     case 3:
      largest = solutionThree(x, y, z);
      break;
     case 4:
      largest = solutionFour(x, y, z);
      break;
     case 5:
      largest = solutionFive(x, y, z);
      break;
  }
  cout << "The largest number is: " << largest << endl;
  return 0;
}

int solutionOne(int x, int y, int z)
{
  int largest;

  if (x >= y && x >= z)
    largest = x;
  if (y >= x && y >= z)
    largest = y;
  if (z >= x && z >= y)
    largest = z;

  return largest;
}  

int solutionTwo(int x, int y, int z)
{
  int largest = (x >= y) ? (x >= z) ? x : z : (y >= z) ? y : z;
  return largest;
}  

int solutionThree(int x, int y, int z)
{
  int largest;

  if (x > y && x > z)
    largest = x;
  else if (y > z)
    largest = y;
  else 
    largest = z;

  return largest;
}  

int solutionFour(int x, int y, int z)
{
  int largest = 0;

  while (largest < x || largest < y || largest < z)
    largest++;

  return largest;
}

int solutionFive(int x, int y, int z)
{
  int largest = 0;

  for (int i = 0; i < x || i < y || i < z; i++)
    largest++;

  return largest;
} 
