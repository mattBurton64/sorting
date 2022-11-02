/*
Matt Burton
csc1710 03
11/15/20
home/students/mburton/csc1710/labs/lab11
Functions to load, print, sort, and search an array. Once sorted, the minimum, maximum, and median of the array will be output.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int loadArray(int A[]);
void printArray(int A[], int num);
void sortArray(int A[], int num);
int findMedian(int A[], int num);
int findSmallest(int A[], int num);
int findLargest(int A[], int num);
int searchArray(int A[], int num, int search);

int main ()
{
  int A[100];
  int num, median, smallest, largest, search;
  
  num = loadArray(A); //loads array
  printArray(A, num); //prints array
  cout << "========== SORTED ==========" << endl;
  sortArray(A, num); //sorts array
  printArray(A, num); //prints sorted array 

  cout << "Smallest: " << findSmallest(A, num) << endl; //prints the smallest
  cout << "Median: " << findMedian(A, num) << endl; //prints the median
  cout << "Largest: " << findLargest(A, num) << endl; //prints the largest
  
  cout << "Enter a positive integer to search for in the array:";
  cin >> search;
  cout << "Number of occurances of the integer " << search << ": " << searchArray(A, num, search) << endl; //prints occurances of seach in array
  return 0;
}

int loadArray(int A[])
{ 
  // input file 
  string fileName; 
  cout << "Data file:";
  cin >> fileName;  
  fileName.c_str();
  ifstream inData;
  inData.open(fileName);
 
  int count = 0, input = 0;
  
  //load data into array
  while(cin && input != -1)
  {
    inData >> input;
    if (input > 0) 
    {
      A[count] = input;
      count++;
    }
  }

  inData.close();
  return count;
}

void printArray(int A[], int num)
{
  //output array data
  for(int i = 0; i < num; i++)
    cout << "A[" << i << "] = " << A[i] << endl;
}

void sortArray(int A[], int num)
{
  //bubble sort to organize array
  bool swapped;
  do
  {
    swapped = false;
    for(int i = 0; i < num - 1; i++)
    {
      if (A[i] > A[i+1])
      {
        int x = A[i];
        A[i] = A[i+1];
        A[i+1] = x;
        swapped = true;
      }
    }
  } while(swapped);
}

int findMedian(int A[], int num)
{
  //find median at middle of array
  int median;
  if(num % 2 != 0)
  {
    median = (A[(num / 2) + 1] + A[num / 2]) / 2;
  } else
    median = A[num/2];
  return median;
}

int findSmallest(int A[], int num)
{
  //determines smallest array value
  int smallest = 10000;
  for(int i = 0; i < num; i++)
  {
    if(A[i] < smallest)
      smallest = A[i];
  }
  return smallest;
}

int findLargest(int A[], int num)
{
  //determies largest array value
  int largest = 0;
  for(int i = 0; i < num; i++)
  {
    if(A[i] > largest)
      largest = A[i];
  }
  return largest;
}

int searchArray(int A[], int num, int search)
{
  int occurances = 0;
  for(int i = 0; i < num && i <= search; i++)
  {
    if(A[i] == search)
      occurances++;
  }
  return occurances;
}
