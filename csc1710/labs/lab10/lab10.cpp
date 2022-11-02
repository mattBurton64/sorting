/*
Matt Burton
csc1710 03
10/22/20
home/students/mburton/csc1710/lab10
Use functions to calculate distance and circle measurements from user input
*/

#include <iostream>
#include <math.h>
using namespace std;

double distance(double x1, double y1, double x2, double y2);
double distance(double x1, double y1);
double radius(double x1, double y1, double x2, double y2);
double radius(double x1, double y1);
double circumference(double radius);
double area(double radius);

const double PI = M_PI;

int main()
{
  double x1, y1, x2, y2, rad = 1;

  //user input for the first two points
  cout << "Enter the first X coordinate:";
  cin >> x1;
  cout << "Enter the first Y coordinate:";
  cin >> y1;
  cout << "Enter the second X coordinate:";
  cin >> x2;
  cout << "Enter the second Y coordinate:";
  cin >> y2;

  //finds distance between points
  cout << "The distance between (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ") is " << distance(x1, y1, x2, y2) << endl;
 
  //user input for circle points
  cout << "Enter the circle's center x and y coordinates:";
  cin >> x1 >> y1;
  cout << "Enter the x and y coordinate on a point on the circle's edge:";
  cin >> x2 >> y2;
  
  //testing the functions as specified in the lab directions
  circumference(rad);
  area(rad);
  radius(x1, y1);
  
  //calculate radius
  rad = radius(x1, y1, x2, y2);

  //output
  cout << "The radius of a circle with a center point of (" << x1 << "," << y1 << ") and a point on its circumference at (" << x2 << "," << y2 << ") is " << rad << endl;
  cout << "The circumference of a circle with a radius of " << rad << " is " << circumference(rad) << endl;
  cout << "The area of a circle with a radius of " << rad << " is " << area(rad) << endl;

  return 0;
}

double distance(double x1, double y1, double x2, double y2)
{
  double distance;
  distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
  return distance;
}

double radius(double x1, double y1, double x2, double y2)
{
  double radius;
  radius = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
  return radius;
}

double circumference(double radius)
{
  double circumference;
  circumference = 2 * PI * radius;
  return circumference;
}

double area(double radius)
{
  double area;
  area = PI * pow(radius, 2);
  return area;
}

double distance(double x1, double y1)
{
  double distance;
  distance = sqrt(pow((0 - x1), 2) + pow((0 - y1), 2));
  return distance;
}

double radius(double x1, double y1)
{
  double radius;
  radius = sqrt(pow((0 - x1), 2) + pow((0 - y1), 2));
  return radius;
}
