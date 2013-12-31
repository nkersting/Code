// Count all the ways of making change with coins of given denoms


#include <iostream>
#include <string.h>


using namespace std;


int Count(int D[], int index, int sum)
{
   int table[sum + 1];  // all the ways of making change, 0 to sum
   for (int i = 0; i < sum+1; ++i)
   {
      table[i] = 0;
   }

   table[0] = 1; // one way to make no change

   for (int i = 0; i < index; i++)  // iterate over denoms
   {
      for (int j = D[i]; j <= sum; ++j)  // start at the sum equal to denom
      {
         table[j] += table[j - D[i]]; // adding one coin to all ways of getting prior sum
      }
   }
   return table[sum];
}


int main()
{
   int D[5] = {1,5,10,25,50};

   for (int i = 0; i <= 100; ++i)
   {
      cout << i << " " << Count(D, 5, i) << endl;
   }

}
