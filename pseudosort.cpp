// Given an array which has n integers. It has both positive and negative integers.Now you need to sort this array in such a way that,the negative integers should be in the front,and the positive integers should at the back.Also the relative position should not be changed.
// eg. -1 1 3 -2 2 ans: -1 -2 1 3 2.

// Required running time complexity is O(N) and the space complexity is O(1)


#include <iostream>

using namespace std;



void InsertionOrder(int nums[], int N)
{
   for (int i = 0; i < N; ++i)
   {
      if (nums[i] < 0)
      {
         int j = i;
         while (j > 0 && nums[j-1] >= 0)
         {
            swap(nums[j], nums[j-1]);
            --j;
         }
      }
   }
}


void Reverse(int list[], int low, int high)
{
   for (int i = 0; i < (high - low + 1)/2; ++i)
   {
      swap(list[low + i], list[high - i]);
   }
}


void Rotate(int list[], int low, int high)
{
   Reverse(list, low, high - 1);
   Reverse(list, low, high);
}

void QSortAndReverse(int nums[], int N)
{
   int pivot = 0;
   int M = 0;

   for (int i = 0; i < N; ++i)
   {
      if (nums[i] < pivot)
      {
         swap(nums[i], nums[M]);
         ++M;
         Rotate(nums, M, i);
      }
   }
}


int main()
{
   int list[10] = {4,3,-1,0,-11,6,90,100,-3,-99};



//   InsertionOrder(list, 10);
   QSortAndReverse(list, 10);

   for (int i = 0; i < 10; ++i)
   {
      cout << list[i] << endl;
   }


   return 0;
}
