/* Author: Matt Burton
   Date: 1/26/21
   Class: CSC-1720
   Code location: ~/csc1720/labs/lab03/main.cpp
   
   About: 
   This program will process a file containing the information about
   the employees. MAX will indicate the maximum number that can be
   processed.  Sample data file named "employeeDB":

   Sam 24 12345.62892
   Mary 19 103234.35345
   Mickey 52 203402
   Alice 43 10203.27003

   The output should be formated as follows with the salary 
   rounded to two decimal places.

   Name        Age       Salary
   Sam          24     12345.63
   Mary         19    103234.35
   Mickey       52    203402.00
   Alice        43     10203.27

   To compile:
      g++ -Wall main.cpp empType.cpp -o processEmployee 

   Create a data file named "employeeDB" containing the sample data 
   from above with some additions.

   NOTE: the load functions opens/closes the file employeeDB for processing.
         the dump function outputs to the screen (stdout).

   To execute:
      ./processEmployee

*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include"empType.h"

using namespace std;

#define MAX 100

//prototypes
void load(empType A[], int &n);
void dump(empType A[], int n);
void shellSort(empType A[], int n);
bool shellPass(empType A[], int n, int gap);
void exchange(empType& a, empType& b);

int main()
{
   empType employeeDB[MAX];
   int n;  

   load(employeeDB, n);
	shellSort(employeeDB, n);
   dump(employeeDB, n);

   return 0;
}

/*
   load - read in data about all employes, name, age, and salary.
   Store the data in an array to be later processed.  The data
   will be loaded into positions 0 through (num employees - 1)
   We are reading from the keyboard so I/O redirection is recommended.
   pre-condition: The empType array references an array that can
                  be loaded with the employee data.  cnt will 
                  initialy be set to 0 but will reflect the total
                  number of employees in the end.
   post-condition: The empType array will be loaded with all 
                   data found in the file or upto MAX 
   Assumption: If the employee's name can be read, we'll assume
               that their age and salary follow.

*/
void load(empType A[], int &cnt)
{
   ifstream inFile;

   inFile.open("employeeDB_withID");
   if(inFile.fail()) {
      cerr << "Error: Could not open the file" << endl;
      exit(1);
   }
   cnt = 0;
   int ID;
	string name;
   int age;
   double salary;
   inFile >> ID >> name >> age >> salary;   
   while(!inFile.eof() && cnt < MAX) {
		A[cnt].setId(ID);
      A[cnt].setName(name);
      A[cnt].setAge(age);
      A[cnt].setSalary(salary);
      cnt++;
      inFile >> ID >> name >> age >> salary;   
   }    
   inFile.close();
}

/*
   dump - output the contents of an empType array containing n elements
          to stdout.  Consider using I/O redirection.
   pre-condition: Array E is loaded with employee data for n employees.
   post-condition: No changes will be made to the array.
*/
void dump(empType A[], int n)
{
   cout << fixed << showpoint;
   cout << left << setw(5) << "ID";
	cout << left << setw(10) << "Name";
   cout << right << setw(5) << "Age";
   cout << right << setw(13) << "Salary" << endl;
   
   for(int i=0;i<n;i++) {
		cout << left << setw(5) << A[i].getId();
      cout << left << setw(10) << A[i].getName();
      cout << right << setw(5) << A[i].getAge();
      cout << right << setw(13) << setprecision(2) << A[i].getSalary();
      cout << endl;
   }
}

/*
	shellSort - rearranges the contents of an empType array in ascending order
	
	pre-condition: Array A is loaded with employee data for n employees
	post-condition: The array is sorted from least to greatest based on ID number
*/

void shellSort(empType A[], int n)
{
	int gap = n / 2;
	while(gap != 0)
	{
		if(shellPass(A, n, gap))
			gap /= 2;
	}
}

bool shellPass(empType A[], int n, int gap)
{
	//true means update gap, false means leave it
	bool same = true;
	for (int j = 0; j < n-gap; j++)
		if (A[j].compareTo(A[j+gap]))
		{
			exchange(A[j], A[j+gap]);
			same = false;
		}
	return same;
}

void exchange(empType& a, empType& b)
{
	empType temp;
	temp = a;
	a = b;
	b = temp;
}


