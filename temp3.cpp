#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

void SiftUp(int list[], int N)   // for a max-heap
{
   int position = N; 
   while (position > 1)
   {
      int parent = position / 2;
      if (list[parent] >= list[position]) { break; }
      swap(list[parent], list[position]);
      position = parent;
   }
}

void SiftDown(int list[], int N)  // for a max-heap
{
   int position = 1, child = 2;      // ordinal position in heap
   while (child <= N)
   {     
      if (child > N) { break;}
      if (child + 1 <= N)
      {
         if (list[child + 1] >= list[child])
         {
            child += 1;
         }
      }
if (list[position] >= list[child]) {break;}            swap(list[position], list[child]);   
      position = child;
child = 2*position;
   }
}



void HeapSort(int list[], int N)
{
   for (int i = 1; i <= N; ++i){SiftUp(list, i);}
   for (int i = N; i > 1; --i)
   {
      swap(list[1], list[i]);
      SiftDown(list, i - 1);
   }
}


void QuickSortArray(int range[], int lower, int upper)
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
      QuickSortArray(range, lower, M-1);
      QuickSortArray(range, M+1, upper);
   }
}



void Merge(int s[], int low, int middle, int high)
{
   int i; /* counter */
   vector<int> buffer1, buffer2; 
   for (i=middle; i>=low; i--) {buffer1.push_back(s[i]);}
   for (i=high; i>=middle+1; i--) {buffer2.push_back(s[i]);}
   i = low;
   while (!(buffer1.empty() || buffer2.empty())) {
      if (buffer1.back() <= buffer2.back())
      {
         s[i++] = buffer1.back();
         buffer1.pop_back();
      }
      else
      {
         s[i++] = buffer2.back();
         buffer2.pop_back();
      }
   }
   while (!buffer1.empty())
   {
      s[i++] = buffer1.back();
      buffer1.pop_back();
   }
   while (!buffer2.empty())
   {
      s[i++] = buffer2.back();
      buffer2.pop_back();
   }
}



void MergeSort(int list[], int low, int high)
{
   if (low >= high) { return;}
   int middle;
   middle = (low + high) / 2;
   MergeSort(list, low, middle);
   MergeSort(list, middle + 1, high);
   Merge(list, low, middle, high);
   return;
}

void Radix(int a[], int N)
{
   // first get the maximum number
   int max = 0;
   for (int i = 0; i < N; ++i)
   {
      if (a[i] > max)
      {
         max = a[i];
      }
   }

   int exp = 1;
   while (max / exp >= 1)
   {
      int buckets[10] = {0,0,0,0,0,0,0,0,0,0};
      int b[N];
      for (int i = 0; i < N; ++i)
      {
         buckets[(a[i] / exp) % 10]++; 
      }
      for (int i = 1; i < 10; ++i)
      {
         buckets[i] += buckets[i-1]; 
      }
      for (int i = N - 1; i >= 0; --i)  
      {
         b[--buckets[(a[i] / exp) % 10]] = a[i];
      }
      for (int i = 0; i < N; ++i)
      {
         a[i] = b[i];
      }
      exp *= 10;      
   }
}

void StringRadix(vector<string>& input)
{
   int N = input.size();
   int max = 0;
   for (int j = 0; j < N; ++j)   // find max
      { if (input[j].length() > max){max = input[j].length();}}
   for (int i = 0; i < max; ++i)
   {
      int buckets[27]; // need to include a "zero" at position 0
      for (int k = 0; k <= 26; ++k){buckets[k] = 0;}
      string temp[N]; for (int k = 0; k < N; ++k){temp[k] = "";}
      
      for (int j = 0; j < N; ++j)
      {
         string x = input.at(j);
         if (x.length() <= i)
         {
            buckets[0]++;
         }
         else
         {
            buckets[(int)(x[x.length() - i - 1]) - (int)('A') + 1]++;
         }
      }
      for (int k = 1; k <= 26; ++k){ buckets[k] += buckets[k-1];}
      for (int j = N-1; j >= 0; --j)
      {
         string x = input.at(j);
         if (x.length() <= i){ temp[--buckets[0]] = x;}
         else
         {
temp[--buckets[(int)(x[x.length()-i-1]) - (int)('A') + 1]] = x;
         }
      }
      for (int j = 0; j < N; ++j){ input.at(j) = temp[j]; }
   }

}



int BinarySearch(int vals[], int low, int high, int x)
{
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




int main()
{
//   int vals[11] = {-111, 3,5,2,1,0,6,0,-1,2,33};

   int vals[11] = {111, 3,5,2,1,0,6,0,1,2,33};

   //   HeapSort(vals, 10);

    QuickSortArray(vals, 0,10);
   
   // MergeSort(vals, 1, 10);

   //  Radix(vals, 11);

   for (int i = 1; i <= 10; ++i)
   {
      cout << vals[i] << endl;
   }

   // vector<string> vv;
   // vv.push_back("AAA");
   // vv.push_back("AA");
   // vv.push_back("B");
   // vv.push_back("DA");
   // vv.push_back("DAY");

   // StringRadix(vv);

   // for (int i = 0; i < 5; ++i)
   // {
   //    cout << vv.at(i) << endl;
   // }

   int x;
   cout << "enter x:";
   cin >> x;
   cout << BinarySearch(vals, 0, 10, x);

   return 0;
}
