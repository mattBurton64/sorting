/*
Class: csc2710 Algorithms
Professor: Lloyd Williams
Student: Matt Burton
Date: 1/21/22
Purpose: Create an array, fill it with random data, and execute sequential search, sum, exchange sort, binary search, find the largest nnumber, and/or find the smallest number.
*/
#include <iostream>
using namespace std;

void fillArray(int n, int list[]); // populates an array with random numbers 0-99
void printArray(int n, int list[]); // prints the array to the terminal
int sequentialSearch(int n, int list[], int target); // returns the index where the target is found
int sumArray(int n, int list[]); // returns the sum of all values in the array
void exchangeSort(int n, int list[]); // sorts the array using the exchange method
int binarySearch(int n, int list[], int target); // returns the index where the target is found
int findMax(int n, int list[]); // returns the largest number in the array
int findMin(int n, int list[]); // returns the smallest number in the array

int main()
{
  int n = 0; // array length

  cout << "Enter the array length:" << endl;
  cin >> n;

  int list[n]; // initializes the array

  fillArray(n, list); // populates the array with random numbers 0-99
  printArray(n, list); // outputs the array to the terminal

  int response = 0; //initialize the response to 0
  while(response != 7) //prompt the user to select an algrithm until response is valid
  {
    cout << endl;

    if (response < 0 | response > 7) // print an error message if the response is not among the options provided
	    cout << "ERROR: Select an algorithm from the list below by inputting it's corresponding number." << endl;
	
	  else // print instructions to select an algorithm
      cout << "Choose an algorithm from the list below to apply to the array above." << endl;

    // Algorithm options below
    cout << "1 | Sequential Search" << endl;
    cout << "2 | Sum Array Elements" << endl;
    cout << "3 | Exchange Sort" << endl;
    cout << "4 | Binary Search" << endl;
    cout << "5 | Find Maximum" << endl;
    cout << "6 | Find Minimum" << endl;
		cout << "7 | Terminate Program" << endl;

    cin >> response; // store user algorithm choice
    cout << endl;

	  switch (response)
	  {
		 	case 1: //sequential search function
			{	 	
				 // establish a target number to search for
				 int target = 0;
				 cout << "Search the array for what number?" << endl;
				 cin >> target;

				 int index = sequentialSearch(n, list, target); // store the index returned by the sequential search

				 if (index == -1)
		  		 cout << target << " was not found within the given array." << endl; // print a message relaying that the target number was not found

				 else
			  	 cout << target << " was found in the array at index: " << index << endl; // print a message relaying where the target number was found
				 break;
			}
			case 2: //sum the array elements
			{
			  cout << "The sum of every element in the given array is: " << sumArray(n, list) << endl;  
			  break;
			}
			case 3: //exchange sort
			{
		  	exchangeSort(n, list);
		  	printArray(n, list);
			  break;
			}
			case 4: //binary search
			{ 
			  // establish a target number to search for
			  int target = 0;
			  cout << "Search the array for what number?" << endl;
			  cin >> target;

			  int index = binarySearch(n, list, target); // store the index returned by the binary search

			  if (index == -1)
		  	  cout << target << " was not found within the given array." << endl; // print a message relaying that the target number was not found

			  else
			    cout << target << " was found in the array at index: " << index << endl; // print a message relaying where the target number was found
				break;
			}
			case 5: // find the largest number in the array
			{
			  cout << "The largest number in the array is: " << findMax(n, list) << endl;
			  break;
			}
			case 6: // find the smallest number in the array
			{
			  cout << "The smallest number in the array is: " << findMin(n, list) << endl;
        break;
			}
			case 7:
			  cout << "Thanks for using this program." << endl;
				break;
			default:
			  cout << "ERROR" << endl;
			  break;
	  }
  }
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

int sequentialSearch(int n, int list[], int target)
{
  bool found = false; // checked by while to see if looping must continue
  int i = 0; // used to iterate through indecies

  while(!found && i < n) // iterates through array until done or found
  {
    if (list[i] == target) // compares array[i] with target
	    found = true; // once found set found to true
  
    else // if array[i] is not the target then increment to the next index
	    i++;
  }

  if (found) // if the target was found then return its index
    return i;

  else // if the target was not in the array then return -1
    return -1;
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

int binarySearch(int n, int list[], int target)
{
  int low = 0; // stores the low end of the search range
	int high = n; // stores the high end of the search range
	int mid = (high + low) / 2; // stores the mid point between the high and low ends
  bool found = false; // tracks if the target has been found
  while(!found) // while the target has not been found...
	{
    if (target == list[mid]) // check if the mid index value matches the target
      found = true; 
	  else if (target > list[mid]) // check if the mid index value is less than the target
		{
		  low = mid;
			mid = (high + low) / 2;
	  }
    else // the mid index value must be greater than the target
		{
		  high = mid;
			mid = (high + low) / 2;
	  }
	}
 
  if (found) // if the target was found then return its index
    return mid;

  else // if the target was not in the array then return -1
    return -1;
}

int findMax(int n, int list[])
{
  int largest = list[0]; // initializes the largest value with the first item in the array
  for (int i = 0; i < n; i++) // iterates through the array
	{
    if (list[i] > largest) // check if list[i] is greater than current largest
		  largest = list[i]; //updates largest
	}

	return largest;
}

int findMin(int n, int list[])
{
  int smallest = list[0]; // initializes the smallest value with the first item in the array
  for (int i = 0; i < n; i++) // iterates through the array
	{
    if (list[i] < smallest) // check if list[i] is less than the current smallest
		  smallest = list[i]; // updates smallest
	}

	return smallest;
}
