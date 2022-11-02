#include <iostream>
#include "rectangleType.h"
#include "boxType.h"
using namespace std;

int main()
{
   boxType pkg;
	double a, b, c, l, w, h, size;
	cout << "Enter package dimensions in inches:" << endl;
	cin >> a >> b >> c;

	//Start of solution
	if (a > b && a > c)
		pkg.setDimension(c, b, a);
	else if (b > a && b > c)
		pkg.setDimension(c, a, b);
	else
		pkg.setDimension(a, b, c);

	double girth;
	girth = pkg.perimeter();

	size = girth + pkg.getLength();
	//End of solution

	if (size > 108 && size < 130)
		cout << "Your package meets the requirements for oversized pricing" << endl;
	else
		cout << "Your package does NOT meet the requirements." << endl;
	
	return 0;
}

