/*
Matt Burton
Testing variables and functions
*/

#include <iostream>
using namespace std;

int main ()
{
  int x = 2, y = 6, z = 9, w;
  double u = 2.345, v, t = 3.14159;
  char letter = 'g';

  cout << x + y * z << endl;
  cout << y * z / x / z << endl;
  cout << y + z % x << endl;
  cout << -x * y -z << endl;
//error  cout << y % u << endl;
  cout << u / t << endl;
//error  cout << z**2 << endl;
  cout << letter - 2 << endl;
  cout << static_cast<double>(y / z) << endl;

  w = t;
  cout << w << endl;

  v = z / x;
  cout << v << endl;

  w = u;
  v = w;
  cout << w  << " " << v << endl;

  letter++;
  cout << letter << endl;

  u *= z / 4.0;
  cout << u << endl;

  v = static_cast<int>(u) / x;
  cout << v << endl;

  z %= y;
  cout << z << endl;

  return 0;

}
