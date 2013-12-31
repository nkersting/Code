// matrix method of determining Fibonacci numbers
// With recursive multiplication, this gives a O(log n) solution

#include <iostream>
#include <cmath>
 
using namespace std;

void RecurseMult(int F[][2], int N)
{
   if (N == 0) return;
   if (N == 1) 
   {
      int G[2][2];
      G[0][0] = 1;
      G[1][0] = 1;
      G[0][1] = 1;
      G[1][1] = 0;

      int f00 = F[0][0]*G[0][0] + F[0][1]*G[1][0];
      int f01 = F[0][0]*G[0][1] + F[0][1]*G[1][1];
      int f10 = F[1][0]*G[0][0] + F[1][1]*G[1][0];
      int f11 = F[1][0]*G[0][1] + F[1][1]*G[1][1];
      F[0][0] = f00;
      F[1][0] = f10;
      F[0][1] = f01;
      F[1][1] = f11;

      return;
   }


   RecurseMult(F, N/2);
   RecurseMult(F, N/2);

   if (N % 2 == 1)
   {
      RecurseMult(F, 1);
   } 

}


// ordinary sequential multiplication, as a check
void SeqMult(int F[][2], int N)
{
   int G[2][2];
   G[0][0] = F[0][0];
   G[1][0] = F[1][0];
   G[0][1] = F[0][1];
   G[1][1] = F[1][1];

   for (int i = 0; i < N; ++i)
   {
      int f00 = F[0][0]*G[0][0] + F[0][1]*G[1][0];
      int f01 = F[0][0]*G[0][1] + F[0][1]*G[1][1];
      int f10 = F[1][0]*G[0][0] + F[1][1]*G[1][0];
      int f11 = F[1][0]*G[0][1] + F[1][1]*G[1][1];
      F[0][0] = f00;
      F[1][0] = f10;
      F[0][1] = f01;
      F[1][1] = f11;
   }
}

int Fibonacci(int N)
{
   int F[2][2];
   F[0][0] = 1;
   F[0][1] = 1;
   F[1][0] = 1;
   F[1][1] = 0;

// SeqMult(F, N);
   RecurseMult(F, N);

   return F[0][0];

}


double Power(double a, int N)
{
   if (N == 0) return 1;
   if (N == 1) return a;

   double x = Power(a, N/2);
   if (N % 2 == 0)
   {
      return x*x;
   }
   else
   {
      return a*x*x;
   }
}

int Explicit(int N)   // derive by finding eigenvalues of G and taking Nth power
{
   double phip = (1 + sqrt(5))/2.0;
   double phin = (1 - sqrt(5))/2.0;

   return (Power(phip, N-1)*(1+phip) - Power(phin, N-1)*(1 + phin))/sqrt(5);
}



int main()
{
   for (int i = 1; i < 45; ++i)
   {
      cout << Fibonacci(i)  << " " << Explicit(i+1) << endl;
   }

   return 0;
}
