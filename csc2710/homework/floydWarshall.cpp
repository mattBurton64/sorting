/*
Matt Burton
Dr. Lloyd Williams
csc2710
3/28/22
Floyd Warshall Project

Question 1. Be able to fill out the Floyd Warshall worksheet provided in class. 
  [Done]
Question 2. Given a W matrix, how can you find the in and out degree of every vertex? 
  The in degree could be found by counting how many values in the adjacency matrix are neither 0 or INF in a vertex's  given colum
  The out degree could be found by counting how many values in the adjacency matrix are neither 0 or INF in a vertex's given row
Question 3: In the D2 matrix, what value could be stored in the D2[3][5] index?
  The value stored in the D2[3][5] index of that  matrix  would  be the distance betweenn 3-->2-->5 summed
Questionn 4: Verify your answer using Floyd's
  *See program below*
Question 5: Add the recursive oath function to findthe shortest path between a pair of vertices
  *See path functio below*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#define INF 9999;

void path(const int P[][6], int q, int r);

int main()
{
  /*Declaring Matricies*/
  int W[6][6] = {0}; // declares the W matrix
  int D[6][6] = {0}; // declares the D matrix
  int P[6][6] = {0}; // declares the P matrix

  /*Initializing values in W Matrix*/
  for(int j = 0; j < 6; j++)
  {  
    for(int i = 0; i < 6; i++)
      {
        if(i == j)
          W[i][j] = 0; // sets the diagnal to zeros
        else
          W[i][j] = INF; // defaults everything else to INF
      }
  }

  /*Opens the data file*/
  cout << "-|-- Floyd Warshall Program -" << endl;
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

  /*Stores the vertices and edges as read in from the data file*/
  cout << endl << "-|-- Adjacency Matrices -" << endl; 
  int vertices, edges, distance;
  inFile >> vertices >> edges; // the first two numbers are stored in vertices and edges repectively

  //cout << "number of vertices: " << vertices << endl; // debug message
  //cout << "number of edges: " << edges << endl; // debug message

  /*Overwrites W distance between vertex pairs as read in from the data file*/
  int lineCount = 0; // tracks the current line number out of the number of edges declared above
  while (lineCount < edges)  // reads inputs untili the file ends or the end of the edges section is reached
  {
    string v1, v2; // stores the first two strings as v1 and v2
    inFile >> v1 >> v2 >> distance;  // reads in a new line
    int vOne = v1[1] - 49; // stores the first vetex number as an int
    int vTwo = v2[1] - 49; // stores the second vertex number as an int
    W[vTwo][vOne] = distance; // overwrites the distance in the W matrix
    lineCount++; // increments line count
  }

  /*Outputting the W matrix*/
  for(int j = -1; j < vertices; j++)
  {  
     for(int i = -1; i < vertices; i++)
     {
       if (i == -1 && j == -1)
         cout << setw(5) << right << "W" << " ";
       else if (i == -1)
         cout << setw(4) << right << "v" << j + 1 << " "; 
       else if (j == -1)
         cout << setw(4) << right << "v" << i + 1 << " ";
       else
         cout << setw(5) << right <<  W[i][j] << " ";
     }
     cout << endl;
  }
  cout << endl;
  
  /*Copying the W matrix into D*/
  for (int j = 0; j < vertices; j++)
  {
    for (int i = 0; i < vertices; i++)
    { 
      D[i][j] = W[i][j];
    }
  }

  /*The Floyd Warshall Algorithm*/
  for (int k = 0; k < vertices; k++)
  {
    for (int j = 0; j < vertices; j++)
    {
      for (int i = 0; i < vertices; i++)
      {
        if(D[i][k] + D[k][j] < D[i][j])
        {
          P[i][j] = k + 1;
          D[i][j] = D[i][k] + D[k][j];
        }
      }
    }
  }

  /*Outputting the P matrix*/
  for(int j = -1; j < vertices; j++)
  {  
     for(int i = -1; i < vertices; i++)
     {
       if (i == -1 && j == -1)
         cout << setw(5) << right << "P" << " ";
       else if (i == -1)
         cout << setw(4) << right << "v" << j + 1 << " "; 
       else if (j == -1)
         cout << setw(4) << right << "v" << i + 1 << " ";
       else
         cout << setw(5) << right <<  P[i][j] << " ";
     }
     cout << endl;
   }
   
   /*Reading in the number of paths from the data file*/
   int numPaths = 0; // the number of paths to determine the shortest route between
   inFile >> numPaths; // stores the number of paths
   
   /*Determinesthe shortest path between each pair of vertices*/
   if (numPaths > 0)
     cout << endl << "-|-- Shortest Paths -" << endl;
   //cout  << "number of paths: " << numPaths << endl; // debug message  
   lineCount = 0; // trakcs how many pairs/paths have been accounted for
   while(lineCount < numPaths)
   {    
     string vFrom, vTo; // stores the pair of vertices
     inFile >> vFrom >> vTo; // stores the two vertices
      
     cout << "Path from: " << vFrom << " to: " << vTo << " ==> ";
      
     //int vOne = vFrom[1] - 49, vTwo = vTo[1] - 49; // stores the vertex numbers and the edge distance 
      
     if (P[vTo[1] - 49][vFrom[1] - 49] != 0)
       cout << vFrom << " "; // debug message

     //cout << "Path from: " << vOne << " to: " << vTwo << endl; // debug message
     path(P, vTo[1] - 49, vFrom[1] - 49);

     if (P[vTo[1] - 49][vFrom[1] - 49] != 0)
       cout << vTo << endl;
     else
       cout << "no path" << endl;
      
     lineCount++; // increments line count
   }

   inFile.close();
}

void path(const int P[][6], int r, int q)
{
  //cout << "P at " << q << " " << r << " = " << P[q][r] << " " << endl; // debug message
  if (P[r][q] != 0)
  {
    path(P, r, P[r][q] - 1);
    cout << "v" << P[r][q] << " ";
    path(P, P[r][q] - 1, q);
  }
}
