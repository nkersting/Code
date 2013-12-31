// Suppose you have an NxN matrix of positive and negative integers. Write some code that finds the sub-matrix with the maximum sum of its elements.


#include<iostream>
#include<vector>

using namespace std;


int SumMatrix(vector<vector<int> > M, int i, int j, int m, int n)
{
   int sum = 0;
   for (int x = i; x <= m; ++x)
   {
      for (int y = j; y <= n; ++y)
      {
         sum += M.at(x).at(y);
      }
   }
   return sum;
}


vector<int> MaxSubMatrix(vector<vector<int> > M)    //brute force O(N^6)
{
   int maxsum = -10000;
   int N = M.size();
   int tempsum;
   int x1,y1,x2,y2;
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         for (int m = i; m < N; ++m)
         {
            for (int n = j; n < N; ++n)
            {
               tempsum = SumMatrix(M,i,j,m,n);
               if (tempsum > maxsum)
               {
                  maxsum = tempsum;
                  x1 = i;
                  y1 = j;
                  x2 = m;
                  y2 = n;
               }
            }
         }
      }
   } 
   vector<int> vals;
   vals.push_back(maxsum);
   vals.push_back(x1);
   vals.push_back(y1);
   vals.push_back(x2);
   vals.push_back(y2);
   return vals;
}


int SumRow(vector<vector<int> > M, int i, int j, int k)
{
   int sum = 0;
   for (int col = i; col <= j; ++col)
   {
      sum += M.at(k).at(col);
   }
   return sum;
}


vector<int> FastMaxSubMatrix(vector<vector<int> > M)    // O(N^3)
{
   int N = M.size();
   int maxsum = -10000;
   int x1,x2,y1,y2;
   // first choose the combination of rows: O(N^2)
   for (int i = 0; i < N; ++i)
   {
      for (int j = i; j < N; ++j)
      {
         // now march down using the usual 1-d array algorithm
         int index1 = 0;
         int index2 = 0;
         int residual = 0;
         int sum = SumRow(M, i, j, 0);
         for (int k = 1; k < N; ++k)
         {
            int kval = SumRow(M, i, j, k);
            if (kval > kval + sum)
            {
               index1 = k;
               index2 = k;
               sum = kval;
               residual = 0;
            }
            else if (kval + residual > 0)
            {
               index2 = k;
               sum += kval;
               residual = 0;
            }
            else
            {
               residual += kval;
            }
         }
         if (sum > maxsum)
         {
            maxsum = sum;
            y1 = i;
            x1 = index1;
            y2 = j;
            x2 = index2;
         }
      }
   }

   vector<int> sol;
   sol.push_back(maxsum);
   sol.push_back(x1);
   sol.push_back(y1);
   sol.push_back(x2);
   sol.push_back(y2);
   return sol;
}



int main()
{
   int N = 6;
   vector<vector<int> > vals;
  
   for (int i = 0; i < N; ++i)
   {
      vector<int> thisrow;
      for (int j = 0; j < N; ++j)
      {
         if (i < N / 2) 
         {
            thisrow.push_back(i);
         }
         else
         {
            thisrow.push_back(0);
         }
      }
      vals.push_back(thisrow);
   }
   
   vals.at(0).at(0) = -1;
   vals.at(N-1).at(N-2) = 9;
   vals.at(N-1).at(N-1) = -5;


   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         cout << vals.at(i).at(j) << " ";
      }
      cout << endl;
   }
   cout << endl;




   vector<int> sol = MaxSubMatrix(vals);

   for (vector<int>::iterator it = sol.begin(); it != sol.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;


   vector<int> sol2 = FastMaxSubMatrix(vals);

   for (vector<int>::iterator it = sol2.begin(); it != sol2.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;

   return 0;
}


// possible test cases:
// 0. empty matrix - gives error
// 1. matrix of zeroes - gives matrix of corner
// 2. matrix of ones - gives whole matrix
// 3. matrx of -1 - gives matrix of corner
// 4. matrix half -1 half +1 : gives positive half
// 5. only non-negative row is 2nd: gives 2nd row
// 6. only non-zero are kitty corners +1: gives whole matrix
// 7. only non-zero are first and last rows & columns -1: gives (N-2)x(N-2) inner matrix
