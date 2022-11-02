#include <iostream>
#include <ctime>
using namespace std;

void populate(int A[], int n);
int sequential(int A[], int n, int search);
bool selection(int A[], int n, int search);
void bubble(int A[], int n);
int binary(int A[], int n, int search);
void outList(int A[], int n);

int main()
{
  const int num = 100;
  int list[num], search, index;
  char algorithm;

  populate(list, num);
  outList(list, num);  

  cout << "Sort algorithm: [S]election [B]ubble" << endl;
  cin >> algorithm;
  switch(algorithm)
  {
    case 'S':
      selection(list, num);
      outList(list, num);
      break;
    case 'B':  
      bubble(list, num);
      outList(list, num);
      break;
  }
  
  cout << "Search algorithm: [S]equential [B]inary" << endl;
  cin >> algorithm; 
  switch (algorithm)
  {
    case 'S':
      cout << "Search value:";
      cin >> search;
      index = sequential(list, num, search);
      cout << search << " at index " << index << endl;
      break;
    case 'B':
      cout << "Search value:";
      cin >> search;
      index = binary(list, num, search);
      cout << search << " at index " << index << endl;
      break;
  }

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

int sequential(int A[], int n, int search)
{
  bool found = false;
  int index = -1;
  for(int i = 0; i < n && !found; i++)
  {
    if (A[i] == search)
    {
      found = true;
      index = i;
    }
  }
  return index;
}

bool selection(int A[], int n, int search)
{
	bool found = false;
	for (int i = 0; i < n; i++)
		if (A[i] == search)
			found = true;
	return found;
}

void bubble(int A[], int n)
{
  bool swapped;
  do
  {
    swapped = false;
    for(int i = 0; i < n - 1; i++)
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
 
int binary(int A[], int n, int search)
{
  int index, left = 0, mid, right = n - 1;
  bool found = false;
  while(left <= right && !found)
  {
    mid = (left + right) / 2;
    if (A[mid] == search)
    {
      found = true;
      index = mid;
    } else if (search > A[mid])
      left = mid + 1;
    else
      right = mid - left;
  }
  return index;
}

void outList(int A[], int n)
{
  for(int i = 0; i < n; i++)
  {
    cout << A[i] << " ";
  }
  cout << endl;
}
