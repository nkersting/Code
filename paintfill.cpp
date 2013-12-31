// Implement the “paint fill” function that one might see on many image editing programs. That is, given a screen (represented by a 2-dimensional array of Colors), a point, and a new color, fill in the surrounding area until you hit a border of that color.


#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

void PaintFill(vector<vector<int> >& M, int x, int y, int color)
{
   M.at(x).at(y) = color;
   for (int k = -1; k < 2; k += 2)
   {
      if (y + k >= 0 && y + k < M.size() && M.at(x).at(y+k) != color)
      {
         PaintFill(M, x, y+k, color);
      }
   }

   for (int k = -1; k < 2; k += 2)
   {
      if (x + k >= 0 && x + k < M.size() && M.at(x+k).at(y) != color)

      {
         PaintFill(M, x+k, y, color);
      }
   }
}

void PrintMatrix(vector<vector<int> > M)
{
   int N = M.size();
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         cout << M.at(i).at(j) << " ";
      }
      cout << endl;
   }
   cout << endl;

}

int main()
{
   vector<vector<int> > M;
   int N = 20;
   for (int i = 0; i < N; ++i)
   {
      vector<int> this_row;
      for (int j = 0; j < N; ++j)
      {
         this_row.push_back(rand() % 10);
      }
      M.push_back(this_row);
   }


   // make four stripes defining a central region
   for (int i = 0; i < N; ++i)
   {
      M.at(i).at(N/6) = 0;
      M.at(N/6).at(i) = 0;
      M.at(i).at(3*N/4) = 0;
      M.at(3*N/4).at(i) = 0;
   }


   PrintMatrix(M);
   PaintFill(M, N/2, N/2, 0);

   PrintMatrix(M);



}
