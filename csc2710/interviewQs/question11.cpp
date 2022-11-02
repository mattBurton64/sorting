#include <iostream>
using namespace std;

void fillArray(int n, int S[]); // used to populate an array with random values between 0-n
void printArray(int n, int S[]); // prints the contents of the array to the terminal
void peaksValleys(int n, int S[], int peaks[], int valleys[]);

int main()
{
  
  int n = 10;
  int S[n];
  int peaks[n];
  int valleys[n];

  fillArray(n, S);

  cout << "S:" << endl;
  printArray(n, S);

  peaksValleys(n, S, peaks, valleys);

  cout << "Peaks:" << endl;
  printArray(n, peaks);
  
  cout << "Valleys:" << endl;
  printArray(n, valleys);

}

void fillArray(int n, int S[])
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
}

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

void peaksValleys(int n, int S[], int peaks[],  int valleys[])
{
  
  int p = 0, v = 0;
  int prev, next;
  
  for (int i = 1; i < n - 1; i++)
  {
    
    prev = S[i - 1];
    next = S[i + 1];

    if (prev < S[i] && S[i] > next)
      peaks[p] = S[i];
    
    if (prev > S[i] && S[i] < next)
      valleys[v] = S[i];
  
  }
}
