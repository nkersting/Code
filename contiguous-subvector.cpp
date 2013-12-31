// Problem: given a cyclic vector of integers, find the continguous subvector with maximal sum
// Start anywhere and sum the entries as we go and mark the lowest and highest points of the sum. If this occured
// at indices i and j, then the subvector we want is from (i+1) to j (inclusive).


#include <iostream>

using namespace std;


int main()
{
   int input[10] = {931,-41,59,26,-53,58,97,-93,-23,84};
   
   int sum[10];
   sum[0] = input[0];
   pair<int, int> min;
   min.first = 0;
   min.second = 1000000;
   pair<int, int> maxx;
   maxx.first = 0;
   maxx.second = -1000000;

   for (int i = 1; i < 10; ++i)
   {
      sum[i] = sum[i-1] +  input[i];
      if (sum[i] < min.second)
      {
         min.first = i;
         min.second = sum[i];
      }
      if (sum[i] > maxx.second)
      {
         maxx.first = i;
         maxx.second = sum[i];
      }
   }
   sum[0] = sum[9] + input[0];      // wrap around to get the first element
   if (sum[0] < min.second)
   {
      min.first = 0;
      min.second = sum[0];
   }
   if (sum[0] > maxx.second)
   {
      maxx.first = 0;
      maxx.second = sum[0];
   }

   cout << "Values: ";
   for (int i = 0; i < 10; ++i)
   {
      cout << input[i] << " ";
   }
   cout << endl << endl;

   cout << "Sums: ";
   for (int i = 0; i < 10; ++i)
   {
      cout << sum[i] << " ";
   }
   cout << endl << endl;

   cout << "Interval is (" << min.first + 1 << ", " << maxx.first << ")" << endl;
   cout << "High value is " << maxx.second - min.second << endl;

   return 1;

}
