// There are n coins in a line. Two players take turns to take a coin from one of the ends of the line until there are no more coins left. The player with the larger amount of money wins. Assuming you go first, how to play?
// http://leetcode.com/2011/02/coins-in-line.html

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


void printMoves(vector<vector<int>> P, vector<int> A, int N) {
  int sum1 = 0, sum2 = 0;
  int m = 0, n = N-1;
  bool myTurn = true;
  while (m < n) {
    int P1 = P[m+1][n]; // If take A[m], opponent can get...
    int P2 = P[m][n-1]; // If take A[n]
    cout << (myTurn ? "I" : "You") << " take coin no. ";
    if (P1 <= P2) {
      cout << m+1 << " (" << A[m] << ")";
      m++;
    } else {
      cout << n+1 << " (" << A[n] << ")";
      n--;
    }
    cout << (myTurn ? ", " : ".\n") << endl;;
    myTurn = !myTurn;
  }
  cout << "\nThe total amount of money (maximum) I get is " << P[0][N-1] << ".\n";
}


void FindChoiceMatrix(vector<vector<int>>& P, vector<int> M)  
{
   int N = P.size();

   // first fill in the diagonal of P = the only coin available
   for (int i = 0; i < N; ++i)
   {
      P[i][i] = M[i];
   }

   // next fill in the adjacent diagonal with the obvious choice
   for (int i = 0; i < N-1; ++i)
   {
      P[i][i+1] = max(M[i],M[i+1]);
   }

   // now fill in the rest of P by the recurrance relation
   // go one diagonal at a time
   for (int i = 2; i < N; ++i)
   {
      for (int j = 0; j < N - i; ++j)
      {
         int x = j;
         int y = i + j;
         P[x][y] = max(M[x] + min(P[x+2][y], P[x+1][y-1]),
                       M[y] + min(P[x+1][y-1], P[x][y-2]));
      }
   }

}





int main()
{

   vector<int> M{10,20,3,14,5,6,1,9};
   int N = M.size();
   vector<vector<int>>P(N, vector<int>(N));

   FindChoiceMatrix(P, M);

   for (auto x: P)
   {
      for (auto y: x)
      {
         cout << y << "      ";
      }
      cout << endl;
   }
   cout << endl;


   for (auto x: M)
   {
      cout << x << " ";
   }
   cout << endl;

   printMoves(P, M, M.size());

   return 0;
}
