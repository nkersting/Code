
#include <vector>
#include<iostream>

using namespace std;


void QuickSort(int list[], int low, int high)
{
   if (low >= high) { return; }
  
   int pivot = list[low]; // or choose random
   int M = low;

   for (int i = low + 1; i <= high; ++i)
   {
      if (list[i] < pivot)
      {
         M++;
         swap(list[i], list[M]);
      }
   }
   swap(list[low], list[M]);
   
   QuickSort(list, low, M - 1);
   QuickSort(list, M + 1, high);
}
  


void Merge(int list[], int low, int middle, int high)
{

   vector<int> first, second;
   for (int i = middle; i >= low; --i)
   {
      first.push_back(list[i]);
   }
   for (int i = high; i > middle; --i)
   {
      second.push_back(list[i]);
   }

   int count = low;
   while (!first.empty() && !second.empty())
   {
      if (first.back() < second.back())
      {
         list[count++] = first.back();
         first.pop_back();
      }
      else
      {
         list[count++] = second.back();
         second.pop_back();
      }
   }

   while (!first.empty())
   {
      list[count++] = first.back();
      first.pop_back();
   }
   while (!second.empty())
   {
      list[count++] = second.back();
      second.pop_back();
   }
}



void MergeSort(int list[], int low, int high)
{
   if (low >= high) { return;}

   int middle = (low + high) / 2;
   MergeSort(list, low, middle);
   MergeSort(list, middle + 1, high);
   Merge(list, low, middle, high);
}


void SiftUp(int vals[], int x)
{
   int parent = x/2;
   while (parent > 0)
   {
      if (vals[parent] <= vals[x])
      {
         break;    // already in-order
      }
      swap(vals[parent], vals[x]);
      x = parent;
      parent = x/2;
   }
}

void SiftDown(int vals[], int N)
{
   int curr = 1;
   int child = 2;
   while (child <= N)
   {
      if (child < N)
      {
         if (vals[child + 1] < vals[child])
         {
            ++child;
         }
      }
      if (vals[curr] <= vals[child]) { break;}   // already in order
      swap(vals[curr], vals[child]);
      curr = child;
      child = curr*2;
   }
}

void HeapSort(int vals[], int N)  // min-heap
{
   for (int i = 1; i <= N; ++i)
   {
      SiftUp(vals, i);
   }

   for (int j = N; j > 1; --j)
   {
      swap(vals[j], vals[1]);
      SiftDown(vals, j-1);
   }

}


int main()
{
   int vals[10] = {5,3,-1,7,6,92,44,2,11,100};
//   QuickSort(vals, 0, 9);
//   MergeSort(vals, 0, 9);
   


   vector<int> vvals;
   vvals.push_back(-271828);  //dummy origin
   for (int i = 0; i < 10; ++i)
   {
      vvals.push_back(vals[i]);
   }
   HeapSort(&vvals[0], 10);


   for (int i = 0; i <= 10; ++i)
   {
      cout << vvals[i] << " ";
   }
   cout << endl;

}
