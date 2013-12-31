// Given a matrix in which each row and each column is sorted, write a method to find an element in it.


#include<iostream>
#include<vector>

using namespace std;




int BSearch(vector<int> list, int low, int high, int target)
{
   while (low <= high)
   {
      int middle = (low + high) / 2;
      if (list.at(middle) == target) { return middle;} 
      if (list.at(middle) < target)
      {
         low = middle + 1;
      }
      else
      {
         high = middle - 1;
      }
   }
   return -high;
}



pair<int,int> FindElement(vector<vector<int> > M, int target)
{
   int N = M.size();
   int low = 0;
   int high = N-1;
   for (int i = 0; i < N; ++i)
   {
      if (target < M.at(i).at(0)) { break;} // not in M
      if (target > M.at(i).at(N-1)) { continue;} // skip row
      int result = BSearch(M.at(i), low, high, target);
      if ( result < 0) // not found
      {
         high = -result;
      }
      else
      {
         return pair<int,int>(i, result);
      }
   } 
   return pair<int,int>(-1,-1);   // not found
}



// now here's the cute way; note this is slower if target is in upper left corner
pair<int,int> FindIt(const vector<vector<int> > M, int N, int target)
{
   int row = 0;
   int col = N - 1;
   while (row < N && col >= 0)
   {
      if (M[row][col] == target)
      {
         return pair<int,int>(row, col);
      }
      if (M[row][col] > target)
      {
         col--;
      }
      else
      {
         row++;
      }
   }
   return pair<int,int>(-1,-1);
}



int main()
{
   int N = 10;
   vector<vector<int> > input;
   for (int i = 0; i < N; ++i)
   {
      vector<int> this_row;
      for (int j = 0; j < N; ++j)
      {
         this_row.push_back(i*j + i + j);
      }
      input.push_back(this_row);
   }

   for (int i = 0; i < N; ++i)
   {

      for (int j = 0; j < N; ++j)
      {
         cout << input.at(i).at(j) << "    ";
      }
      cout << endl;
   }


   int target;
   cout << "Which number to search for? ";
   cin >> target;

   pair<int,int> answer = FindElement(input, target);
   cout << answer.first << " " << answer.second << endl;


   pair<int,int> answer2 = FindIt(input, N,  target);
   cout << "Cute way: " << answer2.first << " " << answer2.second;


   return 1;
}
