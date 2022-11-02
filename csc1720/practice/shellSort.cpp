/*
Author:   Matt Burton
Date:     1/24/2021
Class:    csc1720
Location: ~/csc1720/practice/shellSort.cpp
Purpose:  populate an array and sort using the shell sorting algoorithm
*/
#include <iostream>
#include <ctime>
using namespace std;

/*
Pre-Cond:  pass a non initialized array and its size
PostCond:  each index in the array is initialized to an integer 0-99
*/
void populate(int A[], int n);

/*
Pre-Cond:  pass an array and its size
PostCond:  the array is sorted from least to greatest
*/
void shellSort(int A[], int n);

/*
Pre-Cond:  pass in an unsorted array, its size and the gap
PostCond:  runs through the array once to swap indexes of "gap" distance apart
*/
bool shellPass(int A[], int n, int gap);

/*
Pre-Cond:  pass in two indexes in an array
PostCond:  the two indexes contents are swapped
*/
void exchange(int& a, int& b);

/*
Pre-Cond:  pass an array and its size
PostCond:  output all indexs in the array
*/
void output(int A[], int n);

int main()
{
	//declare arary and its size
   int num = 10;
   int array[num];

   populate(array, num);
   output(array, num);  
	shellSort(array, num);
	output(array, num);

	return 0;
}

void populate(int A[], int n)
{
   srand(time(0));

   for(int i = 0; i < n; i++)
   {
   	A[i] = rand() % 100;
   }
}

void shellSort(int A[], int n)
{
	int gap = n / 2;
	while(gap != 0)
	{
		if(shellPass(A, n, gap))
			gap /= 2;
	}
}

bool shellPass(int A[], int n, int gap)
{
	//true means update gap, false means leave it
	bool same = true;
	for (int j = 0; j < n-gap; j++)
		if (A[j] > A[j+gap])
		{
			exchange(A[j],A[j+gap]);
			same = false;
		}
	return same;
}

void exchange(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void output(int A[], int n)
{
  for(int i = 0; i < n; i++)
  {
    cout << A[i] << " ";
  }
  cout << endl;
}
