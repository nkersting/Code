// Given an array of integers, find all triplets s.t. a+b+c = 0

#include <iostream>
#include <algorithm>

using namespace std;




void Triplets(int list[], int N)
{
   for (int i = 0; i < N; ++i)
   {
      int low = i + 1;
      int high = N - 1;
      while (low < high)
      {
//         cout << "test  " << list[i] << " " << list[low] << " " << list[high] << endl;
         if (list[i] + list[low] + list[high] == 0)
         {
            cout << list[i] << " " << list[low] << " " << list[high] << endl;
         }

         if (list[i] + list[low] + list[high] < 0)
         {
            ++low;
         }
         else if (list[i] + list[low] + list[high] > 0)
         {
            --high;
         }
         else if (list[low + 1] == list[low])
         {
            ++low;
         }
         else // if (list[high - 1] == list[high])
         {
            --high;
         }
      }
   }
}



int main()
{
   int N = 10;
   int nums[10] = {-6,-5,-1,0,1,2,3,3,3,-12};

   // first sort nums
   sort(nums, nums + 10);

   for (int i = 0; i < N; ++i)
   {
      cout << nums[i] << " ";
   }
   cout << endl << endl;

   Triplets(nums, 10);



   return 0;
}
