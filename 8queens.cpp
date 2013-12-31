// Write an algorithm to print all ways of arranging eight queens on a chess board so that none of them share the same row, column or diagonal.

// Note, try this for N queens on a NxN board, ... the number of solution boards minimizes briefly at N = 6 !

#include<vector>
#include<iostream>
#include<cstdlib>

using namespace std;

vector<vector<int> > ModifiedBoard(vector<vector<int> > board, int y, int x)
{
   int N = board.size();
   for (int i = 0; i < N; ++i)
   {
      if (i != y)
      {
         board.at(i).at(x) = 0;
      }
      if (i != x)
      {
         board.at(y).at(i) = 0;
      }
   }
   // now for the diagonals
   for (int i = -N + 1; i < N; ++i)
   {
      if (y + i < N && y + i >= 0 && x + i < N && x + i >= 0
          && i != 0)
      {
         board.at(y + i).at(x + i) = 0;
      }

      if (y - i < N && y - i >= 0 && x + i < N && x + i >= 0
          && i != 0)
      {
         board.at(y - i).at(x + i) = 0;
      }
   }

   return board;
}



void PlaceQueens(vector<vector<vector<int> > >& good_boards, vector<vector<int> > board, int nQueens)
{
   int N = board.size();
   if (nQueens == 0)
   {
      good_boards.push_back(board);
      return;
   }

   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (board.at(i).at(j) == 1)  // safe to place here
         {
            board.at(i).at(j) = 2;   // mark of a Queen
            PlaceQueens(good_boards, ModifiedBoard(board, i, j), nQueens - 1);
         }
      }
   }
   return;
}


bool ColCheck(vector<int> queen_columns, int curr)
{
   for (int i = 0; i < queen_columns.size(); ++i)
   {
      if (queen_columns.at(i) == curr ||
          abs(queen_columns.at(i) - curr) == abs(i - (int)(queen_columns.size())))
      {
         return false;
      }
   }
   return true;
}


// a cuter, faster solution
void RecurseQueen(vector<int> queen_columns)   
{
   if (queen_columns.size() == 8)
   {
      for (vector<int>::iterator it = queen_columns.begin(); it != queen_columns.end(); ++it)
      {
         cout << *it << " ";
      }
      cout << endl;
      return;
   }

   for (int i = 0; i < 8; ++i)
   {
      if (ColCheck(queen_columns, i) == true)
      {
         queen_columns.push_back(i);
         RecurseQueen(queen_columns);
         queen_columns.pop_back();
      }

   }
}



int main()
{
   int N = 8;
   vector<vector<int> > board;
   for (int i = 0; i < N; ++i)
   {
      vector<int> this_row(N,1);
      board.push_back(this_row);	 
   }


   vector<vector<vector<int> > > solutions;

   PlaceQueens(solutions, board, N);


   for (int i = 0; i < solutions.size(); ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         for (int k = 0; k < N; ++k)
         {
            cout << solutions.at(i).at(j).at(k) << " ";
         }
         cout << endl;

      }
      cout << endl;
      cout << endl;
   }

   cout << "There were " << solutions.size() << " solution boards." << endl;


   vector<int> temp;
   temp.clear();
   RecurseQueen(temp);

   return 1;
}
