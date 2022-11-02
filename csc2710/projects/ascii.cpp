#include <iostream>
using namespace std;

int main()
{
  cout << "ASCII TABLE" << endl << "33 - 127" << endl;
  for (int i = 33; i < 128; i++)
  {
    if (i % 16 == 0)
      cout << endl;
    cout << char(i) << " ";
  }
  cout << endl;
}
