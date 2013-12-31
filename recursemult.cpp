// There is an array A[N] of N numbers. You have to compose an array Output[N] such that Output[i] will be equal to multiplication of all the elements of A[N] except A[i]. For example Output[0] will be multiplication of A[1] to A[N-1] and Output[1] will be multiplication of A[0] and from A[2] to A[N-1]. Solve it without division operator and in O(n).


#include<iostream>

using namespace std;


int Mult(int vals[], int low, int high)
{
   int prod = 1;
   for (int i = low; i <= high; ++i)
   {
      prod *= vals[i];
   }
   return prod;
}

void RecurseMultiply(int sol[], int vals[], int low, int high, int prod)    // this is O(n ln n)
{
   if (low == high)
   {
      sol[low] = prod;
      return;
   }

   int middle = (low + high) / 2;
   int prod1 = prod*Mult(vals, middle + 1, high);
   int prod2 = prod*Mult(vals, low, middle);
   RecurseMultiply(sol, vals, low, middle, prod1);
   RecurseMultiply(sol, vals, middle + 1, high, prod2);
}


int main()
{
   int vals[10] = {1,2,4,2,1,2,4,2,2,2};
   int sol[10] = {0,0,0,0,0,0,0,0,0,0};
   RecurseMultiply(sol, vals, 0, 9, 1);

   for (int i = 0; i < 10; ++i)
   {
      cout << sol[i] << endl;
   }
	
   return 0;
}


// one way to do this O(N), if prime factorization of a number is a legal representation, is to
// store the first 100 numbers' prime factorizations in a lookup table, compute the total prime
// factorization of the array, then just walk down the array subtracting the appropriate prime factors
