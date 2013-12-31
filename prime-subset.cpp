// Given a set of numbers [1-N] . Find the number of subsets such that the sum of numbers in the subset is a prime number.


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool IsPrime(int N)
{
   for (int i = 2; i <= sqrt(N); ++i)
   {
      if (N % i == 0) { return false;}
   }
   return true;
}


bool PrimeSet(int subset, int nums[], int N)
{
   int sum = 0;
   for (int i = 0; i < N; ++i)
   {
      if ((subset >> i) & 1 == 1)
      {
         sum += nums[i];
      }
   }
   return IsPrime(sum);
}


vector<int> PrimeSubsets(int nums[], int N)
{
   vector<int> solutions;

   for (int subset = 1; subset <= (1<<N) - 1; ++subset)
   {
      if (PrimeSet(subset, nums, N))
      {
         solutions.push_back(subset);
      }
   }
   return solutions;
}


int main()
{
   int nums[4] = {3,2,1,0};

   vector<int> sols = PrimeSubsets(nums, 4);

   for (vector<int>::iterator it = sols.begin(); it != sols.end(); ++it)
   {
      cout << *it << endl;
   }

   return 0;
}
