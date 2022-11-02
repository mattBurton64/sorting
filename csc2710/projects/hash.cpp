#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//string getUsername();
string getPassword(); //returns the password entered by the user
string newHash(string password); //returns the hashValue after hashing functions have been executed on the password
int ascii(char character); //returns the ascii value for the char passed in 
int sort(int num); //returns the sorted digits of the int passed in
int shift(int num, int amount); //shifts the digits n amount
bool passMatch(string hash); //

int main()
{
  //string username = getUsername();
  string password = getPassword(); // prompts user for password and stores the string
  cout << "You entered: " << password << endl << endl; // echos the password back to the user

  string hash = newHash(password); // calculates the hash for the provided password

  //cout << hashedPass;
  
  if (passMatch(hash)) // determines if the hash matches one of the passwords in the datafile of passwords
  {
    cout << "password matched" << endl;
  }
  else
  {
    cout << "password was not a match" << endl;
  }
}

/*string getUsername()
{
  string username;

  cout << "Username: ";
  cin >> username;

  return username;
}*/

string getPassword()
{
  string password;

  cout << "Password: ";
  cin >> password;
  
  if (password.length() < 8)
  {
    cout << "Passwords must be at least 8 characters long." << endl;
    password = getPassword();
  }
  
  return password;
}

string newHash(string password)
{
  string hashValue; // stores the hashvalue
  int hash[password.length()]; // stores the final hash
  int offset; // value to be added to all numbers, derived from the first character's ascii value

  for (int i = 0; i < password.length(); i ++)
  {
    //FIRST SECURITY LEVEL - converting character to ascii
    hash[i] = ascii(password[i]); // returns the ascii value
    
    //SECOND SECURITY LEVEL - adding the first ascii value to every hash index
    if (i == 0)
      offset = hash[i]; // stores the first character's ascii value in offset
    hash[i] += offset; // offsets every value by the first password digit's ascii value
    cout << " offset: " << left << setw(3) << hash[i] << " "; // prints the offset value
    
    //THIRD SECURITY LEVEL - shifts the digits right by 1
    hash[i] = shift(hash[i], 1); // shifts the digits right one

    //FOURTH SECURITY LEVEL - sorts the digits in non-decreasing order
    hash[i] = sort(hash[i]); // sorts the digits
    
    //FIFTH SECURITY LEVEL - converts hash indicies back to ascii codes
    hash[i] %= 95; // keeps values within ascii table
    hash[i] += 32; // keeps values within ascii table
    cout << " final ascii: " << left << setw(3) << hash[i] << endl; // prints the final ascii value
  }
  
  for (int i = 0; i < password.length(); i ++)
  {  
    hashValue += hash[i]; //concatenates final hash values into one string
  }
  cout << endl << "Hash: " << hashValue << endl; // prints the final hash value

  return hashValue;
}

/*int asciiSum(string hashable)
{
  int ascii;
  int sum = 0;

  for (int i = 0; i < hashable.length(); i++)
  {
    ascii = hashable[i] - 0;
    cout << ascii << " ";
    sum += ascii;
  }
  cout << endl;
  return sum;
}*/

int ascii(char character)
{
  int ascii = character - 0;  // soncverts from char to ascii value
  cout << character << " ascii: " << left << setw(3) << ascii << " "; // prints the ascii value
  return ascii;
}

int sort(int num)
{
  int sorted = 0; // stores the sorted number
  
  for(int digit = 0; digit < 10; digit++) // iterates each digit 0-9
  {
    for(int i = num; i > 0; i /= 10) //iterates each tens place
    {
      if (i % 10 == digit) //compares i to digit
      {
        sorted *= 10; //shifts digits by factor of ten
        sorted += i % 10; // sppends i digit on the end
      }
    }
  }
  
  cout << " sorted: " << left << setw(3) << sorted << " "; //prints the sorted value
  return sorted;
}

int shift(int num, int amount)
{
  int shifted = (num >> amount); // shifts digits n amount
  cout << " shifted " << amount << ": " << left << setw(3) << shifted << " "; // prints the shifted value
  return shifted;
}

bool passMatch(string hash)
{
  string pass; // stores the getline information form the ifstream
  ifstream inFile; // creates an inFile for the ifstream
  inFile.open ("passwords.txt"); // opens the valid passwords text document
  
  while(!inFile.eof()) // iterates over each line in the passwords document
  {
    getline(inFile, pass, '\n'); // stores the given line in pass
    //cout << pass << endl;
    if (hash == pass) // compares the user inputted hash to pass
      return true; // returns a true match
  }

  inFile.close(); // closes the file
  return false; // returns no match
}
