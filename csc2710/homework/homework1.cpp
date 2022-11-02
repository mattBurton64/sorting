#include <iostream>
using namespace std;

void fillArray(int n, int list[]);
void printArray(int n, int list[]);
void findMin(int n, int list[], int m);
int sumArray(int n, int list[]); // returns the sum of all values in the array
void exchangeSort(int n, int list[]); // sorts the array using the exchange method
int maxDifference(int n, int list[], int A[], int B[]);

int main()
{
  int n = 100;
  int list[n];
  fillArray(n, list);
  printArray(n, list);

  int mins = -1;
  while (mins <= 0)
  { 
    cout << "Enter a positive value to determine how many numbers to return:";
    cin >> mins;
  }

  findMin(n, list, mins);
  int A[n];
  int B[n];
  int result = maxDifference(n, list, A, B);
  cout << endl;
  printArray(n/2, A);
  cout << endl;
  printArray(n/2, B);
  cout << "The max difference is: " << result << endl;
}

void fillArray(int n, int list[])
{
  srand(time(0)); //set up for randomizer

  if (n <= 0) // checks for n too small to make an array
    cout << "The array is too small to be filled." << endl;

  else
    
	 for(int i = 0; i < n; i++) // iterates through each index in the array
	 {
	   int randNum = rand() % 100; // generates a new random nnumber 0-99
	   list[i] = randNum; // stores randNum in the array at i
   }
}

void printArray(int n, int list[])
{
  if (n <= 0) // checks for empty arrays
    cout << "The array is empty." << endl;
  
  else
    for (int i = 0; i < n; i++) // iterates through each index in the array
	 {
      cout << list[i] << " "; // prints the array value at ix
	 }
	 cout << endl; // outputs a blank line when complete
}

void findMin(int n, int list[], int m)
{
  bool exchanged = true; // set to true to initiate the while loop
  int count = 0; // tracks the number of times the loop has run through
  while(exchanged)
  {
    exchanged = false; // tracks if an exchanfe occured this loop
    for(int i = 1; i < n; i++) // iterates through every index
	  {
   	  if (list[i] < list[i - 1]) // compares the current index with i - 1 to see if the current index is less than the previous
      {
		    //exchanges the two indices
		    int temp = list[i];
		    list[i] = list[i - 1];
	    	list[i - 1] = temp;
		    exchanged = true; // tracks that an exchange occurred
	    }
	  }
	  count++;
  }

  cout << "The " << m << " lowest values in the array are ";
  
  for(int i = 0; i < m; i++)
  {
	  cout << list[i] << " ";
  }
  cout << endl;
}

int maxDifference(int n, int list[], int A[], int B[])
{
  exchangeSort(n, list);
  for (int i = 0; i < n; i++)
  {
    if (i <= n/2)
    {
      A[i] = list[i];
    }
    else
    {
      B[i - n/2] = list[i];
    }
  }
  return sumArray(n/2,B) - sumArray(n/2,A);
}

int sumArray(int n, int list[])
{
  long int total = 0; //stores the total sum
	for (int i = 0; i < n; i++) //iterates through the array
	{
    total += list[i]; // adds the array[i] to the total
	}

	return total;
}

void exchangeSort(int n, int list[])
{
  bool exchanged = true; // set to true to intiate the while loop
	while(exchanged)
  {
  	exchanged = false; // tracks if an exchange occured this loop
    for(int i = 1; i < n; i++) // iterates through every index  
	  {
			if (list[i] < list[i - 1]) // compares the curret index with i - 1 to see if the curent index is less than the previous
			{
				 //exchanges the two indicies
				 int temp = list[i];
				 list[i] = list[i - 1];
				 list[i - 1] = temp;
				 exchanged = true; // tracks that an exchange occured
			}
	  }
	}
}
