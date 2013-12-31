//Print the elements of a matrix in spiral order (outside to inside). Make your code as efficient as possible. 


#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;



const int M = 5;
const int N = 4;


void SpiralTraverse(int A[][N], int vals[])
{
   int x = 0;
   int y = 0;
   int count = 0;

   while (x <= N/2 && y <= M/2)
   {
      for (int i = x; i <= N - 1 - x; ++i)  //R
      {
         vals[count++] = A[y][i];
      }

      for (int j = y + 1; j <= M - 1 -y; ++j)  //D
      {
         vals[count++] = A[j][N-1-x];
      }

      for (int i = N-1-x-1; i >= x; --i) //L
      {
         vals[count++] = A[M-1-y][i];
      }

      for (int j = M-1-y-1; j >= y + 1; --j) //U
      {
         vals[count++] = A[j][x];
      }

      ++x;
      ++y;
   }
}


int main()
{
   srand(time(NULL));

   int input[M][N];
   for (int j = 0; j < M; ++j)
   {
      for (int i = 0; i < N; ++i)
      {
         input[j][i] = rand() % 9;
         cout << input[j][i] << " ";
      }
      cout << endl;
   } 
   cout << endl;
   


   int vals[M*N];
   memset(vals, 0, M*N);

   SpiralTraverse(input, vals);

   for (int i = 0; i < M*N; ++i)
   {
      cout << vals[i] << " ";
   }

   return 0;
}
