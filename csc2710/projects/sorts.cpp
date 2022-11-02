/*
Class: csc2710 Algorithms
Professor: Lloyd Williams
Students: Matt Burton, Jeremy Maas, Kolt Byers, Cam Bortle, Chris Thiry
Date: 2/7/22
Purpose: Create a program which can:
  - generate 4 types of arrays(random, many duplicates, reverse sorted, and almost sorted)
  - execute every sort algorithm we know(selection, exchange, insertion, bubble, merge,and  quicksort)
  - count the number of swaps done by selection and exchange sort
  - track the time of each sort
  - count basics opertaion performed by each sort
  - terminate sorting loop once the array is sorted for faster performance
  - return the sorted array, the number of basic operations, the time taken to compute, and for selection/exchange sorts the number of swaps 
*/
#include <iostream>
//#include <sys/time.h>
using namespace std;

void fillArray(int n, int arr[], int arrType); // prompts the user to select an array type, then populates the array as specified
void printArray(int n, int arr[]); // prints the array to the terminal
void selectionSort(int n, int arr[], int &counter, int &swaps); // finds the smallest number in the array[i through n], then swaps array[smallest] with array[i]
void exchangeSort(int n, int arr[], int &counter, int &swaps);
void insertionSort(int n, int arr[], int &counter, int &swaps);
void bubbleSort(int n, int arr[], int &countner, int &swaps);
void mergeSort(int arr[], int left, int right, int &counter);
void merge(int arr[], int left, int mid, int right, int &counter);
void quicksort (int low, int high, int arr[], int &counter, int &swaps);
void partition (int low, int high, int& pivotpoint, int arr[], int &counter, int &swaps);
void swap(int i, int j, int arr[], int &swaps); // exchages the items in "arr" at positios i and j 
int arrayType(); // prompts the user to select an array generation algorithm





int main()
{

  int n = 100; // array length
  int arr[n]; // initializes the array
  fillArray(n, arr, arrayType()); // fills the array with values according the the generation algorithm
  printArray(n, arr); // outputs the array to the terminal

  //timer
  /*
  struct timeval startTime, stopTime;
  double start, stop, diff;
  start = startTime.tv_sec+(startTime.tv_usec/100000.0);
  stop = stopTime.tv_sec+(stopTime.tv_usec/100000.0);
  diff = (stop - start/100000);
  */

  int response = 0; //initialize the response to 0

  while(response != 8) //exit the main loop when the user inputs 9 for their response
  {
    
    int counter = 0, swaps = 0, timeElapsed = 0; // resets the countss

    cout << endl;

    cout << "Choose a sort from the list below to apply to the array above." << endl; // print instructions to select an algorithm

    // Algorithm options below
    cout << "1 | Selection Sort" << endl;
    cout << "2 | Exchange Sort" << endl;
    cout << "3 | Insertion Sort" << endl;
    cout << "4 | Bubble Sort" << endl;
    cout << "5 | Merge Sort" << endl;
    cout << "6 | Quick Sort" << endl;
    cout << "7 | New Array" << endl;
    cout << "8 | Terminate Program" << endl;

    cin >> response; // store user algorithm choice
    cout << endl;

	  switch (response)
	  {
		 	
      case 1: // selection sort
      {
        
        selectionSort(n, arr, counter, swaps);
		  	printArray(n, arr);
        cout << endl << "Number of basic operations: " << counter << endl;
        cout << endl << "Number of swaps: " << swaps << endl;
        cout << endl << "Time elapsed:" << timeElapsed << endl;
        
        break;
      }
      
      case 2: // exchange sort
      {
        
        exchangeSort(n, arr, counter, swaps);
		  	printArray(n, arr);
        cout << endl << "Number of basic operations: " << counter << endl;
        cout << endl << "Number of swaps: " << swaps << endl;
        cout << endl << "Time elapsed:" << timeElapsed << endl;
        
        break;
      }
      
      case 3: // insertion sort
      {
        
        insertionSort(n, arr, counter, swaps);
		  	printArray(n, arr);
        cout << endl << "Number of basic operations: " << counter << endl;
        cout << endl << "Number of swaps: " << swaps << endl;
        cout << endl << "Time elapsed:" << timeElapsed << endl;
 
        
        break;
      }
			
      case 4: // bubble sort
			{
		  	
        bubbleSort(n, arr, counter, swaps);
		  	printArray(n, arr);
        cout << endl << "Number of basic operations: " << counter << endl;
        cout << endl << "Number of swaps: " << swaps << endl;
        cout << endl << "Time elapsed:" << timeElapsed << endl;
 
        break;
			}
      
      case 5: // merge sort
      {
        
        mergeSort(arr, 0, n, counter);
		  	printArray(n, arr);
	      cout << endl << "Number of basic operations: " << counter << endl;
	      cout << endl << "Time elapsed: " << timeElapsed << endl;

        break;
      }
      
      case 6: // quick sort
      {
        quicksort(0, n-1, arr, counter, swaps);
		  	printArray(n, arr);
        cout << endl << "Number of basic operations: " << counter << endl;
        cout << endl << "Number of swaps: " << swaps << endl;
        cout << endl << "Time elapsed:" << timeElapsed << endl;
        
        break;
      }
      
      case 7: // new array
      {
        fillArray(n, arr, arrayType()); // populates the array with random numbers 0-99
        printArray(n, arr); // outputs the array to the terminal
        
        break;
      }
			
      case 8: // terminate program
      {
			  cout << "Thanks for using this program." << endl;
				break;
			}
      
      default:
	      cout << "ERROR: Select a sort from the list below by inputting it's corresponding number." << endl; // print an error message if the response is not among the options provided
			  break;
	  }
  }
}

void fillArray(int n, int arr[], int arrType)
{
  
  srand(time(0)); //set up for randomizer

  if (n <= 0) // checks for n too small to make an array
    cout << "The array is too small to be filled." << endl;

  else
    switch(arrType)
    {

      case 1: //Almost sorted
      {
        
        for(int i = 0; i < n; i++) // iterates through each index in the array
        {
          
          if((i % 10) == 0 &&  i != 1) // every 10 items are random
            arr[i] = rand() % 100;
          
          else
            arr[i] = i; // every other index is filled with i
        
        }
        break;
      }

      case 2: //Random distribution
      {
    	  
        for(int i = 0; i < n; i++) // iterates through each index in the array
	      {
	        
          int randNum = rand() % 100; // generates a new random nnumber 0-99
	        arr[i] = randNum; // stores randNum in the array at i
        
        }
        break;
      }

      case 3: //Reverse sorted
      {
        for(int i = 0; i < n; i++)
        {
        
          arr[i] = n - i;
        
        }
        break;
      }

      case 4: //Many duplicates
      {
        int i = 0;
        
        while(i < n)
        {
          
          int randNum = rand() % 100;
          int j;

          for(j = 0; j < n / 10; j++)
            arr[i + j] = randNum;
          
          i += j;
        }
        break;
      }

      deafult: 
        cout << "ERROR" << endl;
        break;
    }
}

void printArray(int n, int arr[])
{
  
  if (n <= 0) // checks for empty arrays
    cout << "The array is empty." << endl;
  
  else
    for (int i = 0; i < n; i++) // iterates through each index in the array
	  {
      
      cout << arr[i] << " "; // prints the array value at ix
	  
    }
	  
    cout << endl; // outputs a blank line when complete
}

void selectionSort(int n, int arr[], int &counter, int &swaps)
{
  
  int i = 0, j = 0, smallest;
  bool isSorted = false;
  
  while (!isSorted)
  {
    
    isSorted = true;
    smallest = i;
    
    for(int j = i + 1; j < n; j++)
    {
    
      if(arr[j] < arr[smallest])
         smallest = j;
      

      if(arr[j] < arr[j - 1])  
        isSorted = false;
      
      counter++;
    
    }
    
    if(i != smallest)
      swap(i, smallest, arr, swaps);
    i++;
  
  }
}

void exchangeSort(int n, int arr[], int &counter, int &swaps)
{
  
  int i = 0;
  bool isSorted = false;

  while(!isSorted)
  {
  
    isSorted = true;

    for(int j = i + 1; j < n; j++)
    {
      
      if (arr[j] < arr[i])
      {
         
         swap(j, i, arr, swaps);
         isSorted = false;
      
      }
      
      counter++;
    
    }

    i++;

  } 
}

void insertionSort(int n, int arr[], int &counter, int &swaps)
{
  bool reverse = true; // assumes the array is sorted in reverse
  
  for(int i = 0; i < n - 1; i++)
  {  
    
    if(arr[i + 1] > arr[i]) // checks if any adjacent values aren't in reverse order
      reverse = false; // updates the reverse bool to reflect the unsorted array
  } 
  
  if(reverse) // if the array is sorted in reverse, then reverse it to sort in ascending order 
  {
    
    int start = 0, end = n - 1; // start tracks the left index, end tracks the right index
    
    while (start < end) // iterates through each index pair from outside in
    {
      
      swap(start, end, arr, swaps);
      start++; // moves right one
      end--; // moves left one
      counter++;

    }
  }
  else // if the array is not reverse sorted then proceed to sort using the insertion sort method
  {
    
    int i, j, x;
    
    for(i = 1; i < n; i++) // iterate through the array
    {
      
      x = arr[i]; // store the second element in the array
      j = i - 1; // j index set to 0 to start
      
      while(j >= 0 && arr[j] > x) // compares every element left of i 
      {
        
        arr[j + 1] = arr[j]; // swaps elements
        j--; // moves j left
        counter++;
      
      }
      
      arr[j + 1] = x; // puts x in place based on j
    
    }
  }
}

void bubbleSort(int n, int arr[], int &counter, int &swaps)
{
  
  bool notSorted = true;
  int i, j, temp;

  while(notSorted)
  {
    
    notSorted = false;
    
    for(i = 0; i < n; i++)
    {
      
      for(j = 0; j < n-i-1; j++)
      {
        
        if(arr[j] > arr[j + 1])
        {
          
          swap(j, j + 1, arr, swaps);
          notSorted = true;
        
        }

        counter++;

      }
    }
  }
}

void mergeSort(int arr[], int left, int right, int &counter)
{
    if (right <= left)
    return;
 
    int mid = (left + (right - left) / 2);
    mergeSort(arr, left, mid, counter);
    mergeSort(arr, mid + 1, right, counter);
    merge(arr, left, mid, right, counter);
}

void merge(int arr[], int left, int mid, int right, int &counter)
{
   int SortedArr[right];
//   int SortedArr[right] = {0};
   int k = 0;
   int i = left;
   int j = mid+1;

   while (i <= mid && j <= right)
   {
      if(arr[i] <= arr[j])
      {
	 counter++;
         SortedArr[k++] = arr[i];
         i++;
      }
      else
      {
         SortedArr[k++] = arr[j];
         j++;
      }
   }
   
   while (i <= mid)
   {
      SortedArr[k++] = arr[i++];
   } 
   while (j <= right)
   {
      SortedArr[k++] = arr[j++];
   }

   int p = left;
   for (int i = 0; i < k; i++)
   {
      arr[p++] = SortedArr[i];
   }

}

void quicksort (int low, int high, int arr[], int &counter, int &swaps)
{

  int pivotpoint;

  if (high > low)
  {
    
    partition(low, high, pivotpoint, arr, counter, swaps);
    quicksort(low, pivotpoint-1, arr, counter, swaps);
    quicksort(pivotpoint+1, high, arr, counter, swaps);
  
  }
}

void partition (int low, int high, int& pivotpoint, int arr[], int &counter, int &swaps)
{
    int i, j, pivotitem, temp;

    pivotitem = arr[low];
    j = low;
    
    for (i = low+1; i <= high; i++){
        counter++;
        if(arr[i] < pivotitem){
            j++;
            swap(i, j, arr, swaps);
        }
    }
    
    pivotpoint = j;
    swap(low, pivotpoint, arr, swaps);
}

void swap(int i, int j, int arr[], int &swaps)
{

  int temp = arr[i]; // temp to store item at i
  arr[i] = arr[j]; // index i = item at j
  arr[j] = temp; // index j = item at i
  
  swaps++; //increment swaps

}

int arrayType()
{
   
   int type;

   while (type <= 0 || type > 5)
   {
      
      if (type <= 0 || type > 5) // error check
	       cout << "ERROR: Select a sort from the list below by inputting it's corresponding number." << endl; // print an error message if the response is not among the options provided
      
      cout << "Select a condition for the new array to exhibit from the list below." << endl;
      cout << "1 | Almost sorted" << endl;
      cout << "2 | Random distribution" << endl;
      cout << "3 | Reverse sorted" << endl;
      cout << "4 | Many duplicates" << endl;

      cin >> type;
      cout << endl;
   
   }
   
   return type;

}
