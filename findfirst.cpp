
// Given an array whose elements are sorted, return the index of a the first occurrence of a specific integer. Do this in sub-linear time. I.e. do not just go through each element searching for that element.



#include <iostream>

using namespace std;


int Lowest(int list[], int y)
{
   while (y >= 1)
   {
      if (list[y] != list[--y])
      {
         return y+1;
      }
   }
   return 0;
}


int FindFirst(int list[], int low, int high, int x)
{
   while (low <= high)
   {
      int middle = (low + high) / 2;
      if (list[middle] == x) return Lowest(list, middle);
      if (list[middle] < x)
      {
         low = middle + 1;
      }
      else
      {
         high = middle - 1;
      }
   }
   return -1;
}


int main()
{
   int vals[10] = {1,1,1,1,5,6,7,8,99,99};
   int N;

   cout << "Enter number to search for: ";
   cin >> N;



   cout << FindFirst(vals, 0, 9, N);


   return 0;
}
