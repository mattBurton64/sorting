/*
Matt Burton
csc1710 03
11/12/20
home/students/mburton/csc1710/labs/lab12
Format and sort information from an input file
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int NUM_OF_STUDENTS = 20;

struct studentType
{
  string studentFName;
  string studentLName;
  int testScore;
  char grade;
};

void getData(ifstream& inFile, studentType sList[], const int NUM_OF_STUDENTS);
void calculateGrade(studentType sList[], const int NUM_OF_STUDENTS);
int highestScore(studentType sList[], const int NUM_OF_STUDENTS);
void printResult(ofstream& outFile, studentType sList[], const int NUM_OF_STUDENTS, int highestScore);

int main()
{
  studentType sList[NUM_OF_STUDENTS];
  int theHighestScore;

//input setup
  string inputFileName;
  cout << "Input File:";
  cin >> inputFileName;
  inputFileName.c_str();
  ifstream inData;
  inData.open(inputFileName);
 
//output 
  ofstream outFile;
  outFile.open("students.out");
  
  getData(inData, sList, NUM_OF_STUDENTS);
  calculateGrade(sList, NUM_OF_STUDENTS);
  theHighestScore = highestScore(sList, NUM_OF_STUDENTS);
  printResult(outFile, sList, NUM_OF_STUDENTS, theHighestScore);

  outFile.close();
  inData.close();
  return 0;
}

void getData(ifstream& inFile, studentType sList[], const int NUM_OF_STUDENTS)
{
  //stores file data in the array as student type
  for(int i = 0; i < NUM_OF_STUDENTS; i++)
  {
    inFile >> sList[i].studentFName >> sList[i].studentLName >> sList[i].testScore; 
  }
}

void calculateGrade(studentType sList[], const int NUM_OF_STUDENTS)
{
  //checks test scores and assigns students the appropriate letter
  for(int i = 0; i < NUM_OF_STUDENTS; i++)
  {
    if (sList[i].testScore >= 90)
      sList[i].grade = 'A';
    else if(sList[i].testScore >= 80)
      sList[i].grade = 'B';
    else if(sList[i].testScore >= 70)
      sList[i].grade = 'C';
    else if(sList[i].testScore >= 60)
      sList[i].grade = 'D';
    else
      sList[i].grade = 'F';
  }
}

int highestScore(studentType sList[], const int NUM_OF_STUDENTS)
{
  //return the highest test score value
  int highestScore = 0;

  for(int i = 0; i < NUM_OF_STUDENTS; i++)
  {
    if(sList[i].testScore >= highestScore)
      highestScore = sList[i].testScore;
  }

  return highestScore;
}

void printResult(ofstream& outFile, studentType sList[], const int NUM_OF_STUDENTS, int highestScore)
{
  //outputsall information provided with labels and correct spacing
  outFile << setw(23) << left << "Student Name" << setw(12) << "Test Score" << "Grade" << endl;

  for(int i = 0; i < NUM_OF_STUDENTS; i++)
  {
    string name = sList[i].studentLName + ", " + sList[i].studentFName;
    outFile << setw(26) << left << name << setw(5) << right << sList[i].testScore << setw(7) << sList[i].grade << endl;
  }
  
  outFile << "\nHighest Test Score: " << highestScore << endl;
  outFile << "Students having the highest test score:" << endl;
  
  for(int i = 0; i < NUM_OF_STUDENTS; i++)
  {
    if(sList[i].testScore == highestScore)
      outFile << sList[i].studentLName << ", " << sList[i].studentFName << endl;
  }
}
