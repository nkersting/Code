


#include<iostream>

using namespace std;


int SumNLargest(int* vals, int size, int N)
{
   int counts[10] = {0,0,0,0,0,0,0,0,0,0};

   for (int i = 0; i < size; ++i)
   {
      if (vals[i] <= 9 && vals[i] >= 0) {counts[vals[i]]++;}
   }

   int sum = 0;
   for (int i = N; i > 0; --i)
   {
      for (int j = 9; j > 0; --j)
      {
         if (counts[j] > 0)
         {
            sum += j;
            counts[j]--;
            break;
         }
      }
   }

   return sum;
}


int main()
{
//   int input[10] = {1,2,3,4,5,6,7,8,9,8};   // edge case: duplicates

   int input[10] = {1,2,3,4,5,6,7,8,19,-8};   // edge case: unexpected numbers

   cout << SumNLargest(input, 10, 3);
//   cout << SumNLargest(input, 10, 30);   // edge case: N too large
   return 0;
}
