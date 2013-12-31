// You are given a game of Tic Tac Toe. You have to write a function in which you pass the whole game and name of a player. The function will return whether the player has won the 
// game or not. First you to decide which data structure you will use for the game. You need to tell the algorithm first and then need to write the code. Note: Some position may be blank in 
// the game। So your data structure should consider this condition also.

#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;


struct Game
{
   int b[3][3];
   string player;
};


bool IsWon(Game g, int qual)
{
  
   for (int i = 0; i <= 2; ++i)
   {
      if (g.b[i][0]*g.b[i][1]*g.b[i][2] == qual)
      {
         return true;
      }
   }
   for (int i = 0; i <= 2; ++i)
   {
      if (g.b[0][i]*g.b[1][i]*g.b[2][i] == qual)
      {
         return true;
      }
   }
   if (g.b[0][0]*g.b[1][1]*g.b[2][2] == qual) { return true;}
   if (g.b[0][2]*g.b[1][1]*g.b[2][0] == qual) { return true;}

   return false;
}

int main()
{
   srand(time(NULL));


   Game mygame;
   mygame.player = "Nick";

   for (int i = 0; i < 3; ++i)
   {
      for (int j = 0; j < 3; ++j)
      {
         mygame.b[i][j] = rand()%3;
      }
   }

   for (int i = 0; i < 3; ++i)
   {
      for (int j = 0; j < 3; ++j)
      {
         cout << mygame.b[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;



   cout << mygame.player << " wins? " <<  (IsWon(mygame, 1) && !IsWon(mygame,8)) << endl;
   cout << "Player 2 wins? " <<  (IsWon(mygame, 8) && !IsWon(mygame,1)) << endl;


   return 0;

}
