/*
Matt Burton
csc1720
1/12/20
students/mburton/csc1720/labs/lab1/lab1.cpp

Run using file rediraction to input the name, position, games played, goals 
scored, shots taken, and minutes played on a unique line for each player.
This will be organized into a table and can be redirected to other output.

*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//maximum number of players that can be stored
const int ROSTER_SIZE = 30;

struct playerType
{
   string name;
   string position;
   int gamesPlayed;
   int goals;
   int shots;
   int minutesPlayed;
};


//Pre: Input a file with player data
//Post: Players array is filled with the appropriate data for "count" number of players
void loadData(playerType players[], int& count);

//Pre: Input the players array
//Post: Output the players array data in organized format
void printData(playerType players[], int count);

int main()
{
  //player inormation storing array
  playerType players[ROSTER_SIZE];
  
  //number of players
  int count = 0;

  loadData(players, count);  
  printData(players, count); 
}

void loadData(playerType players[], int& count)
{ 
   //read input while the data file has more data
   while(cin)
   {
      //store data in players array
      cin >> players[count].name;
      cin >> players[count].position;
      cin >> players[count].gamesPlayed;
      cin >> players[count].goals;
      cin >> players[count].shots; 
      cin >> players[count].minutesPlayed;  
   
      count++;
   }
}

void printData(playerType players[], int count)
{
   double shotPerc;

   //table headers
   cout << "Soccer Stats" << endl;
   cout << left << setw(11) << "Name" << setw(12) << "Position" << right << setw(4) << "GP" << setw(5) << "G" << setw(6) << "SH" << setw(8) << "Mins" << setw(8) << "Shot%" << endl; 

   for(int i = 0; i < count - 1; i++)
   {
      //calculate shot percantage and prevent 0/0
      if(players[i].goals > 0)
         shotPerc = (static_cast<double>(players[i].goals) / static_cast<double>(players[i].shots)) * 100;
      else
         shotPerc = 0.0;

      //output one line of player info
      cout << left << setw(11) << players[i].name << setw(12) << players[i].position << right << setw(4) << players[i].gamesPlayed  << setw(5) << players[i].goals << setw(6) << players[i].shots << setw(8) << players[i].minutesPlayed << setw(7) << fixed << showpoint << setprecision(1) << shotPerc << "%" << endl;       
   }
}
