// determines the minimum number of multiplications needed to 
// multiply N matrices together



#include <iostream>
#include<limits>

using namespace std;

int Count(int dims[], int N)
{
   int C[N][N];               // 0th column and row not used
   // C[i][j] = min number of multiplications needed to compute the matrix product
   // A[i]A[i+1]...A[j] where the dimension of A[i] is dims[i-1] x dims[i]


   for (int i = 1; i < N; ++i)
   {
      C[i][i] = 0;   // takes no multiplications to multiply 1 matrix
   }

   for (int L = 2; L < N; ++L)    // consider products of 2 to N-1 matrices
   {
      for (int i = 1; i <= N - L; ++i)
      {
         int j = i + L - 1;
//         C[i][j] = numeric_limits<int>::max();
         C[i][j] = 1000000;

         for (int k = i; k <= j-1 ; ++k)
         {
            int q = C[i][k] + C[k+1][j] + dims[i-1]*dims[k]*dims[j];
            if (C[i][j] > q)
            {
               C[i][j] = q;
            }
         }

      }
   }

   return C[1][N-1];

}




int main()
{
   int dims[5] = {40, 20, 30, 10, 30};

   cout << Count(dims, 5);


   return 0;
}
