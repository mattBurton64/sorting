/*
Matt Burton
csc1710 03
10/27/20
home/students/mburton/csc1710/prog3
Hangman
I completed the A(92%) category with the Bonus2(5%) and the Bonus3(3%) as well
*/
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

string generateAnswer();
string prepGuess(string answer);
bool guessAgain(char letter, string guessedLetters);
void play(string answer, string& guess);
void drawHangman(int errors);

int main ()
{
  string answer = generateAnswer(); //gets a random word from amn input data file
  string guess = prepGuess(answer); //creates a guess string with blanks the length of the randomly generated word 
  play(answer, guess); //starts the game

  return 0;
}

void play(string answer, string& guess)
{
  string guessedLetters = "";
  char letter;
  bool correct, terminate = false;
  int errors = 0, guessCount = 0;

  while(guess != answer && !terminate)
  {
    cout << "Errors: " << errors << "/10"<< endl; //error count display

    if (guessCount > 0) //skips the first turn since non letters have been guessed
    {    
      cout << "Guessed letters: "; //previously guessed letters display    
      for(int i = 0; i < guessedLetters.length(); i++)
      {
        cout << guessedLetters[i] << " ";
      } 
    }
    cout << endl;
    drawHangman(errors); //stick-figure display

    cout << guess << endl; //shows current state of the guess
    
    cout << "Guess a new letter:"; //USER INPUTS LETTER GUESS
    cin >> letter;
 
    bool redundant = guessAgain(letter,guessedLetters); //prevents guessing the same letter twice
    while(redundant)
    {
      cout << "That letter has already been guessed, guess a new letter:";
      cin >> letter;
      redundant = guessAgain(letter, guessedLetters);
   }
    
    guessedLetters += letter; //tracks previoiusly guessed letters
    guessCount++; //tracks total guesses   

    correct = false; 

    for(int i = 0; i < answer.length(); i++) //fills in the blanks on guess with correct letters
    {
      if(letter == answer[i])
      {
        correct = true;
        guess.erase(i, 1); 
        guess.insert(i, 1, letter);
      }
    }  
    
    if(correct == false) //feedback on incorrect guesses 
    { 
      cout << "Incorrect." << endl; 
      errors++;
    }

    if (errors == 10) //ends the game
    {
      terminate = true;
    }
  }

  cout << "Game over." << endl; //feedback on the game ending 

  if (guess == answer)
  {
    cout << guess << endl;
    cout << "Congratulations! It only took you " << guessCount << " guesses." << endl;
  } else
    cout << "You lost. The word was \" " << answer << " \"" << endl; 
}

string generateAnswer()
{
  srand(time(0));
  string answer, fileName;
  cout << "Enter the name of the data file containing possible word choices" << endl;
  cin >> fileName;  
  ifstream inData;
  inData.open(fileName);

  int random = rand() % 30;

  for(int i = 0; i < random; i++)
     inData >> answer;

  inData.close();
  return answer;
}

string prepGuess(string answer)
{ 
  string guess;
  for(int i = 0; i < answer.length(); i++)
  {
    guess += "_";
  }
  return guess;
}

bool guessAgain(char letter, string guessedLetters)
{ 
  bool redundant = false;
  for(int i = 0; i < guessedLetters.length(); i++)
  {
    if (letter == guessedLetters[i])
      redundant = true;
  }
  if (redundant)
    return true;
  else
    return false;
}

void drawHangman(int errors)
{
  switch (errors)
  {
    case 0:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||        " << endl;
      cout << "||        " << endl;
      cout << "||        " << endl;
      cout << "--        " << endl;
      break;
    case 1:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||        " << endl;
      cout << "||        " << endl;
      cout << "--        " << endl;
      cout << "   Head   " << endl;
      break;
    case 2:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||     |  " << endl;
      cout << "||        " << endl;
      cout << "--        " << endl;
      cout << "   Torso  " << endl;
     break;
    case 3:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|  " << endl;
      cout << "||        " << endl;
      cout << "--        " << endl;
      cout << " Left Arm " << endl;
      break;
    case 4:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||        " << endl;
      cout << "--        " << endl;
      cout << " Right Arm" << endl;
      break;
    case 5:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    /   " << endl;
      cout << "--        " << endl;
      cout << " Left Leg " << endl;
      break;
    case 6:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    / \\" << endl;
      cout << "--        " << endl;
      cout << " Right Leg" << endl;
      break;
    case 7:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    / \\" << endl;
      cout << "--        " << endl;
      cout << " Left Eye " << endl;
      break;
    case 8:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    / \\" << endl;
      cout << "--        " << endl;
      cout << " Right Eye" << endl;
      break;
    case 9:
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    / \\" << endl;
      cout << "--        " << endl;
      cout << "   Nose   " << endl;
      break;
    case 10:      
      cout << "++-----+  " << endl;
      cout << "||/    :  " << endl;
      cout << "||     O  " << endl;
      cout << "||    /|\\" << endl;
      cout << "||    / \\" << endl;
      cout << "--        " << endl;
      cout << "   Frown  " << endl;
      break;
  }
}
