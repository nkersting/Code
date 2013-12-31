// Given an integer array, sort the integer array such that the concatenated integer of the result array is max. e.g. [4, 94, 9, 14, 1] will be sorted to [9,94,4,14,1] where the result integer is 9944141.



#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;


void RevRadix(string input[], int N)
{
   int max = 0;
   for (int j = 0; j < N; ++j)
   {
      if (input[j].length() > max)
      {
         max = input[j].length();
      }
   }


   // now pad all strings to this length with 'A's
   for (int i = 0; i < N; ++i)
   {
      int L = input[i].length();
      for (int j = 0; j < max - L; ++j)
      {
         input[i] += 'A';
      }
   }


   for (int i = 0; i < max; ++i)
   {
      int buckets[10]; // 0 1 2 ... 9 
      for (int k = 0; k < 10; ++k)
      {
         buckets[k] = 0;
      }

      string temp[N];

      for (int j = 0; j < N; ++j)
      {
         string x = input[j];
         if (x[max - 1 - i] == 'A')    // special case for this digit, which mimics the first non-A
         {
            for (int k = max - 1 - i; k >= 0; --k)
            {
               if (x[k] != 'A')
               {
                  buckets[(int)(x[k] - '0')]++;
                  break;
               }
            }
         } 
         else
         {
            buckets[(int)(x[max - 1- i] - '0')]++;
         }
      }

      for (int k = 1; k < 10; ++k)
      {
         buckets[k] += buckets[k-1];
      }


      for (int k = N-1; k >= 0; --k)
      {
         string x = input[k];
         if (x[max - 1 - i] == 'A')
         {
            for (int q = max - 1 - i; q >= 0; --q)
            {
               if (x[q] != 'A')
               {
                  temp[--buckets[(int)(x[q] - '0')]] = x;
                  break;
               }
            }
         }
         else
         {
            temp[--buckets[(int)(x[max - 1 - i] - '0')]] = x;
         }
      }


      for (int k = 0; k < N; ++k)
      {
         input[k] = temp[k];
      }
   }
}


void StripPadding(string input[], int N)
{
   for (int i = 0; i < N; ++i)
   {
      int count = 0;
      for (int j = 0; j < input[i].length(); ++j)
      {
         if (input[i][j] == 'A') { count++;};
      }
      input[i] = input[i].substr(0, input[i].length() - count);
   }

}


int main()
{
   // int N = 5;
   // string input[5] = {"4", "94", "9", "14", "1"};

   int N = 10;
   string input[10] = {"4", "914", "955", "143", "100", "66", "999", "919", "113", "9099"};


   RevRadix(input, N);

   StripPadding(input, N);

   for (int i = N-1; i >=0 ; --i)
   {
      cout << input[i] << " ";
   }


   return 0;
}
