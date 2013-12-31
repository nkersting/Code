// use quicksort to get the kth-order element quickly (O(n) on average)


#include<iostream>

using namespace std;


int QSortMedian(int list[], int lower, int upper, int target)
{
   int M = lower;
   int pivot = list[M];
   for (int j = lower + 1; j <= upper; ++j)
   {
      if (list[j] < pivot)
      {
         M++;
         swap(list[M], list[j]);
      }
   }
   swap(list[M], list[lower]);
   if (M == target) { return list[M]; }
   if (M < target)
   {
      return QSortMedian(list, M + 1, upper, target);
   }
   else
   {
      return QSortMedian(list, lower, M - 1, target);
   }
}


int main()
{
   int vals[9] = {10,50,20,40,30,60,90,70,80};
   cout << QSortMedian(vals, 0, 8, 2);
   return 0;
}
