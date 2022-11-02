/*
Matt Burton
csc1710 03
10/26/20
students/home/mburton/csc1710/test
Remove vowels from strings
*/

#include <iostream>
#include <string>
using namespace std;

void removeVowels(string& str);
bool isVowel(char letter);

int main ()
{
  //user input and priliminary outputs
  string str;
  cout << "Enter a word to remove the vowels." << endl;
  cin >> str;

  cout << "Before: " << str << endl;
  removeVowels(str); //removes vowels
  cout << "After: " << str << endl; 
  
  return 0;
}

void removeVowels(string& str)
{
  //iterates for every character in str
  for (int i = 0; i < str.length(); i++)
  {
    bool erase = isVowel(str[i]);    
    if (erase) //remove the current character
      str.erase(i, 1); 
  }
}

bool isVowel(char letter)
{ 
  //compares the current character with vowels
  if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
    return true;
  else
    return false;
}
