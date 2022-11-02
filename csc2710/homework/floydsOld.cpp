#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#define INF 9999;

//void path(int q, int r);

int main()
{
  ifstream inFile; // reference to the file being loaded 
  string fileName; // name of the file to load

  cout << "Enter the name of the file to load the W matrix from:" << endl; //gets user input for the file name 
  cin >> fileName; // stores the file name

  inFile.open(fileName); // opens the input stream through the specified file 

  while (inFile.fail()) // ensures a valid file is entered before opening
  {
    cout << "ERROR: Please enter a valid file name to load the W matrix from:" << endl; // re-prompts the user to enter a valid file name
    cin >> fileName; // stores the file name
    inFile.open(fileName); // opens the file
  }
  
  int vertices, edges; // stores the number of edges
  inFile >> vertices >> edges; // the first two numbers are stored in vertices and edges repectively

  cout << "number of vertices: " << vertices << endl; // debug message
  cout << "number of edges: " << edges << endl; // debug message

  int W[vertices][vertices]; // declares the @ matrix
  
  for(int i = 1; i < vertices + 1; i++)
  {  
    for(int j = 1; j < vertices + 1; j++)
      {
        if(i == j)
          W[i][j] = 0; // sets all edges to a nodes self to 0
        else
          W[i][j] = INF; // defaults everything else to Infinity
      }
  }
  
  int lineCount = 0; // tracks the current line number out of the number of edges declared above
  while (!inFile.eof() && lineCount < edges)  // reads inputs untili the file ends or the end of the edges section is reached
  {
    string v1, v2; // stores the first two strings as v1 and v2
    int vOne = v1[1] - 48, vTwo = v2[1] - 48, distance; // stores the vertex numbers and the edge distance
    //cout << vOverticese << " " << vTwo << " " << distance << endl;
    W[vTwo][vOne] = distance; // sets the distance in the W matrix
    inFile >> v1 >> v2 >> distance;  // reads in a new line
    lineCount++; // increments line count
  }
  
 for(int j = 0; j < vertices + 1; j++)
  {  
     for(int i = 0; i < vertices + 1; i++)
     {
       if (i == 0 && j == 0)
         cout << "    W ";
       else if (i == 0)
         cout << setw(5) << right << j << " ";
       else if(j == 0)
         cout << setw(5) << right << i << " ";
       else
         cout << setw(5) << right <<  W[i][j] << " ";
     }
     cout << endl;
   }
  
  cout << endl;
  
  int P[vertices][vertices] = {0};
  int D[vertices][vertices] = {0};
  
  /*for (int j = 0; j < vertices; j++)
    for (int i = 0; i < vertices; i++)
      P[i][j] = 0;
  */

  for (int j = 0; j < vertices; j++)
  {
    for (int i = 0; i < vertices; i++)
    { 
      D[i][j] = W[i][j];
    }
  }

  for (int k = 0; k < vertices; k++)
  {
    for (int j = 0; j < vertices; j++)
    {
      for (int i = 0; i < vertices; i++)
      {
        if(D[i][k] + D[k][j] < D[i][j])
        {
          P[i][j] = k;
          D[i][j] = D[i][k] + D[k][j];
        }
      }
    }
  }

  for(int j = 0; j < vertices + 1; j++)
  {  
     for(int i = 0; i < vertices + 1; i++)
     {
       if (i == 0 && j == 0)
         cout << "    P ";
       else if (i == 0)
         cout << setw(5) << right << j << " ";
       else if(j == 0)
         cout << setw(5) << right << i << " ";
       else
         cout << setw(5) << right <<  P[i][j] << " ";
     }
     cout << endl;
   }

   /*int numPaths; // the number of paths to determine the shortest route between
   inFile >> numPaths; // stores the number of paths
 
   lineCount = 0;
   while(!inFile.eof() && lineCount < numPaths)
   {
     string v1, v2; // stores the first two strings as v1 and v2
     int vOne = v1[1] - 48, vTwo = v2[1] - 48; // stores the vertex numbers and the edge distance
     if (vOne > 0 && vTwo > 0 && vOne < vertices && vTwo < vertices)
       path(vOne, vTwo, P[][6]);
     inFile >> v1 >> v2;  
   }
   */
   inFile.close();
}

/*void path(int q, int r)
{
  if (P[q][r] != 0)
  {
    path(q, P[q][r]);
    cout << "v" << P[q][r] << " ";
    path(P[q][r], r);
  }
}*/
