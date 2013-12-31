

#include <iostream>

using namespace std;


void QuickSort(int list[], int lower, int higher)
{

   if (lower < higher)
   {
      int middle = (lower + higher) / 2;
      swap (list[lower], list[middle]);

      int M = lower;
      int pivot = list[lower];
      for (int i = lower; i <= higher; ++i)
      {
         if (list[i] > pivot)
         {
            ++M;
            swap(list[i], list[M]);
         }
      }
      swap(list[M], list[lower]);

      QuickSort(list, lower, M-1);
      QuickSort(list, M+1, higher);

   }

}


void SiftUp(int input[], int n)  // min heap
{
   int position = n;
   while (position > 1)
   {
      int parent = position/2;
      if (input[parent] <= input[position]) { break;}
      swap(input[parent], input[position]);
      position = parent;
   }
}


void SiftDown(int input[], int N)
{
   int position = 1;
   int child = 2;
   while (child <= N)
   {
      if (child + 1 <= N)
      {
         if (input[child + 1] <= input[child])
         {
            child += 1;
         }
      }

      if (input[position] <= input[child]) { break;}
      swap(input[position], input[child]);
      position = child;
      child = 2*position;
   }
}

void HeapSort(int input[], int N)   // from 1 to N inclusive
{
   for (int i = 1; i <= N; ++i)
   {
      SiftUp(input, i);
   }

   for (int i = N; i > 1; --i)
   {
      swap(input[1],input[i]);
      SiftDown(input, i-1);
   }
}


int main()
{
   int input[10] = {4,2,9,0,3,2,2,7,7,5};

   QuickSort(input, 0, 9);

   for (int i = 0; i < 10; ++i)
   {
      cout << input[i] << endl;
   }
   cout << endl << endl;

   int input2[11] = {-1,4,2,9,0,3,2,2,7,7,5};
   HeapSort(input2, 10);
   for (int i = 0; i <= 10; ++i)
   {
      cout << input2[i] << endl;
   }

   return 0;
}
