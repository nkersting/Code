// 0-1 Knapsack problem


#include <iostream>
#include <cmath>

using namespace std;

// given total Weight W allowed, number of items N and their weights and values,
// maximize value
int Knap(int wt[], int val[], int N, int W)
{
   int K[N+1][W+1];  // solution table
   for (int i = 0; i <= N; ++i)  // number of items in the sack
   {
      for (int w = 0; w <= W; ++w) // weight of items in the sack
      {
         if (i == 0 || w == 0) 
         {
            K[i][w] = 0;
         }
         else if (wt[i-1] <= w)
         {
            K[i][w] = max(K[i-1][w - wt[i-1]] + val[i-1], K[i-1][w]); 
         }
         else
         {
            K[i][w] = K[i-1][w];   // this item too heavy to place in sack
         }
      }
   }


   return K[N][W];
}



int main()
{
   int N = 3;
   int val[] = {70, 100, 120};
   int wt[] = {10, 20, 35};
   int W = 50;

   cout << Knap(wt, val, N, W);

   return 0;

}
