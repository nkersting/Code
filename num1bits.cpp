// Given an integer, print the next smallest and next largest number that have the same number of 1 bits in their binary representation.


#include<iostream>
#include <limits.h>


using namespace std;

int Count1Bits(int N)
{
   int count = 0;
   while (N > 0)
   {
      count += (N & 1);
      N = N >> 1;
   }
   return count;

}


void FindNeighbors(int N)
{

   int n1bits = Count1Bits(N);
   int low = -1;
   for (int i = N - 1; i >= 0; --i)
   {
      if (Count1Bits(i) == n1bits)
      {
         low = i;
         break;
      }
   }

   int high = -1;
   for (int i = N + 1; i <= INT_MAX; ++i)
   {
      if (Count1Bits(i) == n1bits)
      {
         high = i;
         break;
      }
   }


   // cout << INT_MAX << endl;


   // int j = 0;
   // for (int i = 2147483647 - 50; j < 100; ++i)
   // {
   //    ++j;
   //    cout << i << endl;
   // }

   cout << low << endl << high << endl;
}

int main()
{
   FindNeighbors(50);
   return 0;
}
