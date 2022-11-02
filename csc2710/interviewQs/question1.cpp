#include <iostream>
using namespace std;

void fillArray(int n, int S[]); // used to populate an array with random values between 0-n
void printArray(int n, int S[]); // prints the contents of the array to the terminal
void merge(int n, int A[], int B[]); // combines array B into A
void shift(int n, int S[], int start);

int main()
{
  //int n;

  //cout << "Enter array B length: " << endl;
  //cin >> n;
  
  int A[10] = {0,1,2,3,4};
  int B[5] = {0,2,4,6,8};

  //fillArray(2 * n, A); // fills A halfway
  //fillArray(n, B); // fills B completely

  cout << "A:" << endl;
  printArray(10, A);

  cout << "B:" << endl;
  printArray(5, B);

  merge(10, A, B);

  printArray(10, A);
}

/*void fillArray(int n, int S[])
{
  
  srand(time(0)); //set up for randomizer

  if (n <= 0) // checks for n too small to make an array
    cout << "The array is too small to be filled." << endl;

  else
  {
    	  
    for(int i = 0; i < n; i++) // iterates through each index in the array
    {
      
      int randNum = rand() % 100; // generates a new random nnumber 0-99
      S[i] = randNum; // stores randNum in the array at i
     
     }
   }
}*/

void printArray(int n, int S[])
{
  
  if (n <= 0) // checks for empty arrays
    cout << "The array is empty." << endl;
  
  else
    for (int i = 0; i < n; i++) // iterates through each index in the array
	  {
      
      cout << S[i] << " "; // prints the array value at ix
	  
    }
	  
    cout << endl; // outputs a blank line when complete
}

void merge(int n, int A[], int B[])
{
  int i = 0, j = 0, k = 0;
  while(k < 2 * n)
  {
    if (A[i] < B[j])
    {
      shift(n, A, i);
      A[i] = B[j];
      k++;
      j++;
    }
    else
    {
      k++;
      i++;
    }
  }
}

void shift(int n, int S[], int start)
{
  for (int i = start; i < n; i++)
  {
    S[i] = S[i - 1];
  }
}
