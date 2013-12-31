// QuickSort with random pivot choice




#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void QuickSort(int range[], int lower, int upper)
{
   if (lower < upper)
   {      
      int middle =  lower + rand() % (upper - lower);
      swap(range[lower], range[middle]);
      
      int pivot = range[lower];
      int M = lower;
      for (int j = lower + 1; j <= upper; ++j)
      {
         if (range[j] < pivot)
         {
            M += 1;
            swap(range[M],range[j]);
         }
      }
      swap(range[M], range[lower]);
      QuickSort(range, lower, M-1);
      QuickSort(range, M+1, upper);
   }
}




int main()
{
   int my_array[10] = {0,3,6,4,8,9,1,22,40,7};

   srand (time(NULL));

   
   QuickSort(my_array,0,9);
   
   for (int i = 0; i < 10; ++i)
   {
      cout << my_array[i] << endl;
   }

}
