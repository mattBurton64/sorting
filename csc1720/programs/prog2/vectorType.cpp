/*
Matt Burton
csc1720
2/2/21
csc1720/labs/lab04/vectorType.h

I implimented all of the methods possible.

a class for storing and manipulating vectors
*/
#include "vectorType.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

#define EPSILON 0.0001

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
	Pre condition: two vectorType objects exist with data and one is acted upon and the other is passed in
	Post condition: A third vectorType object is returned with each variable summated
*/
vectorType vectorType::addVector(vectorType vec)
{
	vectorType retVec(x + vec.getX(), y + vec.getY(), z + vec.getZ());
	return retVec;
}

/*
	Pre condition: two vectorType objects exist with data and one is acted upon and the other is passed in
	Post condition: A third vectorTyp object is returned with each variable subtracted from eachother
*/
vectorType vectorType::subVector(vectorType vec)
{
	vectorType retVec(x - vec.getX(), y - vec.getY(), z - vec.getZ());
	return retVec;
}

/*
	Pre condition: A vectorType object exists with data in each variable
	Post condition: The veector has a length of 1 and x and y are scaled by the same value
*/
vectorType vectorType::unitVector()
{
	double scalar = 1.0 / z;
	vectorType retVec(x * scalar, y * scalar, z * scalar);
	return retVec;
}

/*
	Pre condition: two vectorType objects exist with data, one is acted upon and one it passed in
	Post condition: the x, y, and z variables of each vector is multiplied by the x, y, and z of the other, added together and returned as a duble
*/
double vectorType::dotProduct(vectorType vec)
{
	double a = x * vec.getX();
	double b = y * vec.getY();
	double c = z * vec.getZ();
	return (a + b + c);
}

/*
	Pre condition: two vectorType objects exist with data
	Post condition: the cross product formula is executed on the two vectors and returns a third vector
*/
vectorType vectorType::crossProduct(vectorType vec)
{
	vectorType retVec((y * vec.getZ()) - (z * vec.getY()), (z * vec.getX()) - (x * vec.getZ()), (x * vec.getY()) - (y * vec.getX()));
	return retVec;
}

/*
	Pre condition: two vectorType objects exist with data
	Post condition: if the difference of each respective variable is less than 0.0001 than the two vectors are equal and returns true
*/
bool vectorType::equalVector(vectorType vec)
{
	if (abs(x - vec.getX()) < EPSILON && abs(y - vec.getY()) < EPSILON && abs(z - vec.getZ()) < EPSILON)
		return true;
	else
		return false;
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
