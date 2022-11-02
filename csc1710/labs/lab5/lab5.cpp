/*
Matt Burton
9/17/20
csc1710 03
home/students/mburton/csc1710/lab5
Purpose: take input file and reformat into a new output file
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main ()
{ 
  ifstream inFile;
  ofstream outFile;
  
  inFile.open ("inData.txt");
  outFile.open ("outData.txt");
  
  //initialize variables 
  string first, last, department;   
  double mgs, bonus, taxes, check, miles, time, aspeed, cost, sales;
  int cupsSold; 

  //read and store variables
  inFile >> first >> last >> department >> mgs >> bonus >> taxes >> miles >> time >> cupsSold >> cost >> sales;
  check = mgs;
  check -= (check * (taxes * 0.01));
  check += (check * (bonus * 0.01));
  aspeed = miles / time;
  sales = cupsSold * cost;

  //format output
  outFile << fixed << showpoint << setprecision(2);
  outFile << "Name: " << first << " " << last << ", Department: " << department << endl;
  outFile << "Monthly Gross Salary: $" << mgs << ", Monthly Bonus: " << bonus << "%, Taxes: " << taxes << "%" << endl;
  outFile << "Paycheck: $" << check << "\n" << endl;
  outFile << "Distance Traveled: " << miles << " miles, Traveling Time: " << time << " hours" << endl;
  outFile << "Average Speed: " << aspeed << " miles per hour\n" << endl;
  outFile << "Number of Coffe Cups Sold: " << cupsSold << ", Cost: $" << cost << " per cup" << endl;
  outFile << "Sales Amount: $" << sales << endl;

  inFile.close();
  outFile.close();
}
