 // 	Suppose you had an n by n chess board and a super piece called a kingknight. Using only one move the kingknight denoted 'K' below can reach any of the spaces denoted 'X' or 'L' below:
//    .......
//    ..L.L..
//    .LXXXL.
//    ..XKX..
//    .LXXXL.
//    ..L.L..
//    .......
// In other words, the kingknight can move either one space in any direction (vertical, horizontal or diagonally) or can make an 'L' shaped move. An 'L' shaped move involves moving 2 spaces horizontally then 1 space vertically or 2 spaces vertically then 1 space horizontally. In the drawing above, the 'L' shaped moves are marked with 'L's whereas the one space moves are marked with 'X's. In addition, a kingknight may never jump off the board.



// Given the size of the board, the start position of the kingknight and the end position of the kingknight, your method will return how many possible ways there are of getting from start to end in exactly numMoves moves. start and finish are int[]s each containing 2 elements. The first element will be the (0-based) row position and the second will be the (0-based) column position. Rows and columns will increment down and to the right respectively. The board itself will have rows and columns ranging from 0 to size-1 inclusive. 


#include <iostream>
#include <vector>
#include <cmath>


using namespace std;


vector<pair<int, int> > Locus(int board_size, pair<int, int> origin)
{
   int x = origin.first;
   int y = origin.second;
   int xx, yy;
   vector<pair<int, int> > results;
   for (int i = -2; i <= 2; ++i)
   {
      for (int j = -2; j <= 2; ++j)
      {
         xx = x + i;
         yy = y + j;
         if (i == 0 && j == 0 ||
             abs(i*j) == 4 ||             // trick to get knights moves
             (i == 0 && abs(j) == 2) ||
             (j == 0 && abs(i) == 2))
         { 
            continue;
         }
         if (xx < board_size &&
             yy < board_size &&
                  xx >= 0 &&
                  yy >= 0)
         {
//            cout << xx << " " << yy << endl;
            results.push_back(pair<int,int>(xx,yy));
         }
      }   
   }         
   return results;
}


int InLocus(vector<pair<int, int> > points, pair<int, int> start)
{
   for (vector<pair<int, int> >::iterator it = points.begin(); it != points.end(); ++it)
   {
      if (it->first == start.first && it->second == start.second) { return 1;}
   }
   return 0;
}

int NumWays(int board_size, pair<int, int> start, pair<int, int> finish, int moves)
{
   if (moves == 0) { return 1;}

   vector<pair<int, int> > points = Locus(board_size, finish);
   if (moves == 1)
   {
      return InLocus(points, start);
   }

   int total = 0;
   for (vector<pair<int, int> >::iterator it = points.begin(); it != points.end(); ++it)
   {
      total += NumWays(board_size, start, *it, moves - 1);
   }
   return total;
}



int main()
{
   // int board_size = 3;
   // int moves = 1;
   // pair<int,int> start(0,0);
   // pair<int,int> finish(1,0);
   // cout << NumWays(3, start, finish, moves);

   // int board_size = 3;
   // int moves = 1;
   // pair<int,int> start(0,0);
   // pair<int,int> finish(1,2);
   // cout << NumWays(3, start, finish, moves);


   // int board_size = 3;
   // int moves = 1;
   // pair<int,int> start(0,0);
   // pair<int,int> finish(2,2);
   // cout << NumWays(3, start, finish, moves);

   // int board_size = 3;
   // int moves = 2;
   // pair<int,int> start(0,0);
   // pair<int,int> finish(0,0);
   // cout << NumWays(3, start, finish, moves);

   int board_size = 8;
   int moves = 5;
   pair<int,int> start(0,0);
   pair<int,int> finish(4,4);
   cout << NumWays(8, start, finish, moves);

   return 0;
}
