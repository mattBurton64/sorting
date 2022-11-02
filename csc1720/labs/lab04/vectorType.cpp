/*
Matt Burton
csc1720
2/2/21
csc1720/labs/lab04/vectorType.h

a class for storing and manipulating vectors
*/
#include "vectorType.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

/*
	Pre condition: a vectorType object exists with any data
	Post condition: the data for x, y, and z is overwritten to a, b, and c
*/
void vectorType::setComps(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

/*
	Pre condition: a vectorTpe object exists with data in x, y and z
	Post condition: the vector's x, y, and z are output in vector format
*/
void vectorType::printVector() const
{
	cout << fixed << showpoint << setprecision(4);
	cout << "<" << x << ", " << y << ", " << z << ">";
}

/*
	Pre condition: a vector exists with x, y and z
	Post condition: the magnitude is returned
*/
double vectorType::calcMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

/*
	Pre condition: a vectorType object exists with x, y and z data and a scale is passed in
	Post condition: the scale is distributed(multiplied) across x, y, and z and a new vectorType object is returned
*/
vectorType vectorType::scalarMultiply(double scale)
{
	double a = x * scale;
	double b = y * scale;
	double c = z * scale;
	vectorType scaledVector(a, b, c);
	
	return scaledVector;
}

/*
	Pre condition: a vectorType object exists with an x
	Post condition: the x value is returned
*/
double vectorType::getX() const
{
	return x;
}

/*
	Pre condition: a vectorType object exists with an y
	Post condition: the y value is returned
*/
double vectorType::getY() const
{
	return y;
}

/*
	Pre condition: a vectorType object exists with an z
	Post condition: the z value is returned
*/

double vectorType::getZ() const
{
	return z;
}

//constructor
vectorType::vectorType(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

//constructor
vectorType::vectorType()
{
	x = 0;
	y = 0;
	z = 0;
}
