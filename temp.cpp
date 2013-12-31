

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<limits>

using namespace std;



void QSort(int list[], int low, int high)
{
   if (low < high)
   {
      int middle = low + rand()%(high - low);
      swap(list[low], list[middle]);
      int pivot = list[low];  
     
      int M = low;
      for (int i = low+1; i <= high; ++i)
      {
         if (list[i] < pivot)
         {
            M++;
            swap(list[M], list[i]);
         }
      }
      swap(list[M], list[low]);
      QSort(list, low, M - 1);
      QSort(list, M + 1, high);
   }
}


void Merge(int list[], int low, int middle, int high)
{
   vector<int> list1;
   vector<int> list2;

   for (int i = middle; i >= low; --i)
   {
      list1.push_back(list[i]);
   }
   for (int i = high; i >= middle + 1; --i)
   {
      list2.push_back(list[i]);
   }

   int count = low;
   while (!list1.empty() && !list2.empty())
   {
      if (list1.back() < list2.back())
      {
         list[count++] = list1.back();
         list1.pop_back();
      }
      else
      {
         list[count++] = list2.back();
         list2.pop_back();
      }
   }

   while(!list1.empty())
   {
      list[count++] = list1.back();
      list1.pop_back();
   }
   while(!list2.empty())
   {
      list[count++] = list2.back();
      list2.pop_back();
   }
}


void MergeSort(int list[], int low, int high)
{
   if (low >= high)
   {
      return;
   }

   int middle = (low + high) / 2;
   MergeSort(list, low, middle);
   MergeSort(list, middle + 1, high);
   Merge(list, low, middle, high);
}


void InsertionSort(int list[], int low, int high)
{
   for (int i = low + 1; i <= high; ++i)
   {
      int j = i;
      while(list[j] < list[j-1] && j > 0)
      {
         swap(list[j], list[j-1]);
         --j;
      }
   }

}


void SiftUp(int list[], int x, int low, int high)   // for max-heap
{
   while (x > low)
   {
      int parent = (x - low + 1) / 2 + low - 1;
      if (list[parent] >= list[x]) { break;}
      swap(list[parent], list[x]);      
      x = parent;
   }
} 


void SiftDown(int list[], int low, int high)
{
   int curr = low;
   int child = (curr - low + 1)*2 + low - 1;
   while (true)
   {
      child = (curr - low + 1)*2 + low - 1;
      if (child > high) {break;}
      if (child < high)
      {
         if (list[child + 1] > list[child])
         {
            ++child;
         }
      }
      if (list[child] <= list[curr]) {break;}
      swap(list[child], list[curr]);
      curr = child;
   }

}


void HeapSort(int list[], int low, int high)
{
   for (int i = low; i <= high; ++i)
   {
      SiftUp(list, i, low, high);
   }
   
   for (int j = high; j > low; --j)
   {
      swap(list[low], list[j]);
      SiftDown(list, low, j - 1);
   }
}


void SaneSiftUp(int list[], int x, int N)
{
   while (x > 1)
   {
      int parent = x/2;
      if (list[parent] >= list[x]) { break;}
      swap(list[parent], list[x]);
      x = parent;
   }
}

void SaneSiftDown(int list[], int N)
{
   int parent = 1;
   int child = 2;
   while (child <= N)
   {
      if (child < N)
      {
         if (list[child + 1] > list[child])
         {
            ++child;
         }
      }
      if (list[child] <= list[parent]) { break;}
      swap(list[child], list[parent]);
      parent = child;
      child = 2*parent;
   }

}


void SaneHeapSort(int list[], int N)   // max-heap indexed 1..N
{
   for (int i = 1; i <= N; ++i)
   {
      SaneSiftUp(list, i, N);
   }

   for (int j = N; j > 1; --j)
   {
      swap(list[1], list[j]);
      SaneSiftDown(list, j-1);
   }
}


void Radix(int list[], int N)
{
   // first find max
   //int max = numeric_limits<int>::min();
     int max = -100;
   for (int i = 0; i < N; ++i)
   {
      if (list[i] > max)
      {
         max = list[i];
      }
   }

   int exp = 1;
   while (max / exp >= 1)
   {
      int buckets[10] = {0,0,0,0,0,0,0,0,0,0};
      int b[N];
      for (int j = 0; j < N; ++j)
      {
         b[j] = 0;
      }

      for (int i = 0; i < N; ++i)
      {
         buckets[(list[i] / exp) % 10]++;
      }
      for (int i = 1; i < 10; ++i)
      {
         buckets[i] += buckets[i-1];
      }
      for (int i = N - 1; i >= 0; --i)
      {
         b[--buckets[(list[i] / exp) % 10]] = list[i];
      }
      for (int i = 0; i < N; ++i)
      {
         list[i] = b[i];
      }
      exp *= 10;
   }
}



int BinarySearchIt(int vals[], int N, int x)
{
   int low = 0;
   int high = N-1;

   while (low <= high)
   {
      int middle = (low + high) / 2;
      if (vals[middle] == x) { return middle;}
      if (vals[middle] < x)
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


int BinaryRecurseSearch(int vals[], int low, int high, int x)
{
   if (low > high) { return -1;}
   int middle = (low + high)/2;
   if (vals[middle] == x) { return middle;}
   if (vals[middle] < x)
   {
      return BinaryRecurseSearch(vals, middle + 1, high, x);
   }
   else
   {
      return BinaryRecurseSearch(vals, low, middle - 1, x);
   }
}


int main()
{
   // int input[20] = {3,5,1,7,8,3,0,3,5,7,0,0,0,0,0,0,0,0,0,0};

   // srand(time(NULL));
   
   // for (int i = 0; i < 20; ++i)
   // {
   //    input[i] = rand()%30;
   //    cout << input[i] << " ";
   // }
   // cout << endl;

//   QSort(input, 0, 9);
//   MergeSort(input, 0, 9);
//   InsertionSort(input, 0, 9);
//   HeapSort(input, 0, 9);

   // int inputnew[11];
   // inputnew[0] = -137;   // dummy value;
   // for (int i = 0; i < 10; ++i)
   // {
   //    inputnew[i+1] = input[i];
   // }
   // SaneHeapSort(inputnew, 10);

   // for (int i = 1; i < 11; ++i)
   // {
   //    cout << inputnew[i] << " ";
   // }
   // cout << endl;


   // Radix(input, 20);
   // cout << "{";
   // for (int i = 0; i < 20; ++i)
   // {
   //    cout << input[i] << ", ";
   // }
   // cout << "}" << endl;


   int N;
   int vals[20] = {2, 4, 4, 7, 8, 11, 13, 16, 17, 17, 18, 19, 20, 25, 25, 27, 28, 29, 29, 29};
   cout << "Search for:";
   cin >> N;

   cout << BinarySearchIt(vals, 20, N) << endl;
   cout << BinaryRecurseSearch(vals, 0, 19, N) << endl;

   return 0;
}

