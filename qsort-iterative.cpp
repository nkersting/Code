

#include <iostream>

using namespace std;



int AuxPartition(int list[], int low, int high)
{
   int M = low;
   int pivot = list[low];

   for (int i = low + 1; i <= high; ++i)
   {
      if (list[low] > list[i])
      {
         ++M;
         swap(list[M], list[i]);
      }
   }
   swap(list[M], list[low]);
   return M;
}


void QSortIterative(int list[], int low, int high)
{
   int stack[high - low + 1];  // this holds the current interval to partition

   int top = -1;

   stack[++top] = low;
   stack[++top] = high;

   while (top >= 0)
   {
      high = stack[ top--];
      low = stack[ top--];

      int p = AuxPartition(list, low, high);

      if (p-1 > low)
      {
         stack[ ++top] = low;
         stack[ ++top] = p - 1;
      }

      if (p+1 < high)
      {
         stack[ ++top ] = p + 1;
         stack[ ++top ] = high;
      }
   }
}


int main()
{
   int nums[10] = {88, 2,3,5,1,0,9,22,3,-1};


   QSortIterative(nums, 0, 9);


   for (int i = 0; i < 10; ++i)
   {
      cout << nums[i] << " ";
   }

}
