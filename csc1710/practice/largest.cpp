#include <iostream>
using namespace std;

int largest(int max, int input);

int main ()
{
  int count = 0, max = 0, input, size = 1;
  
  cout << "Size of data set:";
  cin >> size;

  while(size <= count)
  {
    cout << "invalid:";
    cin >> size;
  }

  while(count < size)
  {
    cout << "[" << count + 1 << "]:";
    cin >> input;
    max = largest(max, input);
    count++;
  }
  cout << "The largest of the ten input integers is " << max << endl;

  return 0;
}

int largest(int max, int input)
{ 
  if (input > max)
    max = input;
  return max;
}
