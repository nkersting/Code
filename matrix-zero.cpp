
// Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0.


#include<iostream>
#include<vector>

using namespace std;








vector<pair<int, int> > ZeroPairs(vector<vector<int> > M)
{
   int N = M.size();
   vector<pair<int, int> > zpairs;
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (M.at(i).at(j) == 0)
         {
            zpairs.push_back(pair<int,int>(i,j));
         }
      }
   }
   return zpairs;
}


void ApplyZeroes(vector<vector<int> >& M, vector<pair<int,int> > zpairs)
{
   int N = M.size();
   for (vector<pair<int,int> >::iterator it = zpairs.begin(); it != zpairs.end(); ++it)
   {
      int killrow = it->first;
      int killcol = it->second;
      for (int i = 0; i < N; ++i)
      {
         M.at(killrow).at(i) = 0;
         M.at(i).at(killcol) = 0;
      }
   }
}


int main()
{
   vector<vector<int> > M;

   for (int i = 0; i < 5; ++i)
   {
      vector<int> this_row;
      for (int j = 0; j < 5; ++j)
      {
         this_row.push_back((i+j)%7);
      }
      M.push_back(this_row);
   }

   for (vector<vector<int> >::iterator it = M.begin(); it != M.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   cout << endl << endl;

   ApplyZeroes(M, ZeroPairs(M));

   for (vector<vector<int> >::iterator it = M.begin(); it != M.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }

   return 1;
}
