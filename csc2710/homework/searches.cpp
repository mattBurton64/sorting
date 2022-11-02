/*
Class: csc2710 Algorithms
Professor: Lloyd Williams
Student: Matt Burton
Date: 1/26/22
Purpose:
*/
#include <iostream>
using namespace std;

void fillArray(int n, int list[]); // populates an array with random numbers 0-99
void printArray(int n, int list[]); // prints the array to the terminal
//int sumArray(int n, int list[]); // returns the sum of all values in the array
int sequentialSearch(int n, int list[], int target, int &counter); // returns the index where the target is found
void exchangeSort(int n, int list[], int &counter); // sorts the array using the exchange method
int binarySearch(int n, int list[], int target, int &counter); // returns the index where the target is found
//int findMax(int n, int list[]); // returns the largest number in the array
//int findMin(int n, int list[]); // returns the smallest number in the array
int fibonacciI(int n, int &counter); // returns the nth fibonacci number iteratively
int fibonacciR(int n, int &counter); // returns the nth fibonacci number recursively

int main()
{
  int n = 0; // array length
  //cout << "Enter the array length:" << endl;
  //cin >> n;
  n = 100;

  int list[n]; // initializes the array

  fillArray(n, list); // populates the array with random numbers 0-99
  printArray(n, list); // outputs the array to the terminal

  int response = 0; //initialize the response to 0
  while(response != 7) //prompt the user to select an algrithm until response is valid
  {
    cout << endl;
    int counter = 0; //tracks basic operations in algorithms

    if (response < 0 | response > 7) // print an error message if the response is not among the options provided
	    cout << "ERROR: Select an algorithm from the list below by inputting it's corresponding number." << endl;
	
	  else // print instructions to select an algorithm
      cout << "Choose an algorithm from the list below to apply to the array above." << endl;

    // Algorithm options below
    cout << "1 | Sequential Search" << endl;
    cout << "2 | Exchange Sort" << endl;
    cout << "3 | Binary Search" << endl;
    cout << "4 | Fibonacci (iterative)" << endl;
    cout << "5 | Fiboonacci (recursive)" << endl;
		cout << "6 | New Array" << endl;
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

				 int index = sequentialSearch(n, list, target, counter); // store the index returned by the sequential search

				 if (index == 0)
		  		 cout << target << " was not found within the given array." << endl; // print a message relaying that the target number was not found

				 else
			  	 cout << target << " was found in the array at index: " << index << endl; // print a message relaying where the target number was found

         cout << "1 | Sequential Search took " << counter << " basic operations." << endl; // prints the counted number of basic operations
				 break;
			}
			case 2: //exchange sort
			{
		  	exchangeSort(n, list, counter);
		  	printArray(n, list);
        cout << "2 | Exchange Sort took " << counter << " basic operations." << endl; // prints the counted number of basic operations
			  break;
			}
			case 3: //binary search
			{ 
			  // establish a target number to search for
			  int target = 0;
			  cout << "Search the array for what number?" << endl;
			  cin >> target;

			  int index = binarySearch(n, list, target, counter); // store the index returned by the binary search

			  if (index == -1)
		  	  cout << target << " was not found within the given array." << endl; // print a message relaying that the target number was not found

			  else
			    cout << target << " was found in the array at index: " << index << endl; // print a message relaying where the target number was found
        cout << "3 | Binary Search took " << counter << " basic operations." << endl; // prints the counter nnumber of basic operations
				break;
			}
      case 4: // find the nth fibonacci number iteratively
      {
        //prompts the user too enter what nth digit of the fibonacci sequence to return 
        int x = 0;
			  cout << "nth digit: " << endl;
			  cin >> x;

        int result = fibonacciI(x, counter); // stores the results
        cout << "The " << x << " place fibonacci number is: " << result << endl; // prints the result
        cout << "4 | Fibonacci (iterative) took " << counter << " basic operations." << endl; // prints the counted number of basic operations
        break;
      }
      case 5: // find the nth fibonacci number recursively
      {
        //prompts the user too enter what nth digit of the fibonacci sequence to return 
        int x = 0;
			  cout << "nth digit: " << endl;
			  cin >> x;

        int result = fibonacciR(x, counter); // stores the results
        cout << "The " << x << " place fibonacci number is: " << result << endl; // prints the result
        cout << "5 | Fibonacci (recursive) took " << counter << " basic operations." << endl; // prints the counted number of basic operations
        break;
      }
      case 6: // refreshes the array values
      { 
        fillArray(n, list); // populates the array with random numbers 0-99
        printArray(n, list); // outputs the array to the terminal
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

int sequentialSearch(int n, int list[], int target, int &counter)
{
  bool found = false; // checked by while to see if looping must continue
  int i = 0; // used to iterate through indecies
  
  while(!found && i < n) // iterates through array until done or found
  {
    counter++; // tracks how many basic operations occured in this algorithm
    if (list[i] == target) // compares array[i] with target
	    found = true; // once found set found to true
  
    else // if array[i] is not the target then increment to the next index
	    i++;
  }

  if (found) // if the target was found then return its index
    return i + 1;

  else // if the target was not in the array then return -1
    return 0;
}

/*int sumArray(int n, int list[])
{
  long int total = 0; //stores the total sum
	for (int i = 0; i < n; i++) //iterates through the array
	{
    total += list[i]; // adds the array[i] to the total
	}

	return total;
}*/

void exchangeSort(int n, int list[], int &counter)
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
      counter++; // tracks how many basic operations occured in this algorithm
	  }
	}
}

int binarySearch(int n, int list[], int target, int &counter)
{
  int low = 0; // stores the low end of the search range
	int high = n; // stores the high end of the search range
	int mid = (high + low) / 2; // stores the mid point between the high and low ends
  bool found = false; // tracks if the target has been found
  while(low < mid && !found) // while the target has not been found...
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
    counter++; // tracks how many basic operations occured in this algorithm
	}
 
  if (found) // if the target was found then return its index
    return mid;

  else // if the target was not in the array then return -1
    return -1;
}

/*int findMax(int n, int list[])
{
  int largest = list[0]; // initializes the largest value with the first item in the array
  for (int i = 0; i < n; i++) // iterates through the array
	{
    if (list[i] > largest) // check if list[i] is greater than current largest
		  largest = list[i]; //updates largest
	}

	return largest;
}*/

/*int findMin(int n, int list[])
{
  int smallest = list[0]; // initializes the smallest value with the first item in the array
  for (int i = 0; i < n; i++) // iterates through the array
	{
    if (list[i] < smallest) // check if list[i] is less than the current smallest
		  smallest = list[i]; // updates smallest
	}

	return smallest;
}*/

int fibonacciI(int n, int &counter)
{
  if (n <= 1)
  {
    counter++;
    return n;
  }
  else
  {
    n -= 1;
    int first = 0;
    int second = 1;
    int last = 0;
  
    for (int i = 0; i < n; i++)
    {
      last = first + second;
      first = second;
      second = last;
      counter++;
    }
  return last;
  }
}

int fibonacciR(int n, int &counter)
{
  counter++;
  if (n <= 1)
    return n;
  else
    return fibonacciR(n - 1, counter) + fibonacciR(n - 2, counter);
}
