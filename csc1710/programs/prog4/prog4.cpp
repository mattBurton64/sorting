/*
Matt Burton
csc1710 03
11/16/20
home/students/mburton/csc1710/programs/prog4
Reads input golf data from a file and outputs the appropriate scorecard and stats
completed the A(92%) level assignment with (6%) 9 hole split and (6%) multiple winners
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int NUM_HOLES = 18;
const int NUM_GOLFERS = 4;

struct golfer
{
  string name;
  int score[NUM_HOLES];
  char symbols[NUM_HOLES];
  int total = 0;
  int firstNine = 0;
  int backNine = 0;
  bool winner = false;
};

void readFile(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES); //reads in par, name, and scores from a data file
void evaluateScores(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES);
void nineHoleSplit(golfer golfers[], const int NUM_HOLES, int i, int j);
int winner(golfer golfers[], const int NUM_GOLFERS);
void printScorecard(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES, int winnerCount);

int main()
{
  golfer golfers[NUM_GOLFERS]; //names, scores, and totals for the four golfers
  int par[NUM_HOLES]; //par for 18 holes
  int winnerCount = -1; //stores the number of winners
  
  readFile(golfers, NUM_GOLFERS, par, NUM_HOLES);
  evaluateScores(golfers, NUM_GOLFERS, par, NUM_HOLES);
  winnerCount = winner(golfers, NUM_GOLFERS);
  printScorecard(golfers, NUM_GOLFERS, par, NUM_HOLES, winnerCount);

  return 0;
}

void readFile(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES)
{
  string dataFile; //file input
  ifstream inData;
  cout << "Data file:";
  cin >> dataFile;
  dataFile.c_str();
  inData.open(dataFile);
  
  for(int i = 0; i < NUM_HOLES; i++) //stores the par for each of the 18 holes 
    inData >> par[i];
  
  for(int i = 0; i < NUM_GOLFERS; i++) //stores the names for each of the 4 golfers
    inData >> golfers[i].name;

  for(int i = 0; i < NUM_HOLES; i++) //stores the scores for each hole
    for(int j = 0; j < NUM_GOLFERS; j++) //stores the scores to the right person
      inData >> golfers[j].score[i];

  inData.close();
}

void evaluateScores(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES)
{
  for(int i = 0; i < NUM_HOLES; i++) //checks each hole
  {
    for(int j = 0; j < NUM_GOLFERS; j++) //checks each golfer
    {
      golfers[j].total += golfers[j].score[i]; //adds score to total
      nineHoleSplit(golfers, NUM_HOLES, i, j); //tracks the front and back nine hoesl separately

      if(par[i] - golfers[j].score[i] >= 2) //adds marks for eagles
        golfers[j].symbols[i] = '!';
      else if(par[i] - golfers[j].score[i] == 1) //adds stars for birdies
        golfers[j].symbols[i] = '*';
      else if(par[i] - golfers[j].score[i] < 1)
        golfers[j].symbols[i] = ' ';
    }  
  }
}

void nineHoleSplit(golfer golfers[], const int NUM_HOLES, int i, int j)
{
  if(i < 9)
    golfers[j].firstNine += golfers[j].score[i]; //adds score to first nine 
  else
    golfers[j].backNine += golfers[j].score[i]; //adds score to back nine
}

int winner(golfer golfers[], const int NUM_GOLFERS)
{
  int lowest = 10000, winnerCount = 0;

  for(int i = 0; i < NUM_GOLFERS; i++) //determines the lowest score
  {  
    if(golfers[i].total <= lowest)
      {
        lowest = golfers[i].total;
     }
  }

  for(int i = 0; i < NUM_GOLFERS; i++) //determines who has the lowest score and how many have it
  {
    if(golfers[i].total == lowest)
    {
      golfers[i].winner = true;
      winnerCount++;
    }
  }
  return winnerCount;
}

void printScorecard(golfer golfers[], const int NUM_GOLFERS, int par[], const int NUM_HOLES, int winnerCount)
{
  int parTotal = 0, scoreDifference = 0;

  //prints names, totals, first nine, and back nine scores
  for(int i = 0; i < NUM_GOLFERS; i++)
  {
    cout << setw(7) << right << golfers[i].name << setw(4) << golfers[i].total << setw(3) << "(" << golfers[i].firstNine << " - " << golfers[i].backNine << ")" << endl;
  }
  
  for(int i = 0; i < NUM_HOLES; i++)
    parTotal += par[i];
  
  //prints winner
  int count = 0;
  cout << endl;
  for(int i = 0; i < NUM_GOLFERS; i++)
  {
    if(golfers[i].winner && count == 0) //print case for 1 winner
    {
      cout << golfers[i].name;
      scoreDifference = golfers[i].total - parTotal;
      count++;
    } else if(golfers[i].winner && count > 0 && count < winnerCount - 1) //print case for 2-(n-1) winners
    {
      cout << ", " << golfers[i].name;
      count++;
    } else if(golfers[i].winner && count == winnerCount - 1) //print case (n-1) winner
    {
      cout << " and " << golfers[i].name;
      count++;
    }
  }
  cout << " was the winner with a score of " << scoreDifference << "." << endl<< endl;
  
  //prints labels
  cout << setw(7) << "";
  for(int i = 0; i < NUM_HOLES; i++)
    cout << setw(2) << right << i + 1 << " ";
  cout << setw(6) << "Score" << endl;

  //score table
  for(int i = 0; i < NUM_GOLFERS; i++) //each line per person
  {  
    cout << setw(7) << right << golfers[i].name;
    for(int j = 0; j < NUM_HOLES; j++) //score for each hole
    {
      cout << setw(2) << right << golfers[i].score[j] << setw(1) << golfers[i].symbols[j];
    }
    cout << setw(5) << golfers[i].total << endl;
  }
}
