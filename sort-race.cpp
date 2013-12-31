// Comparison of performance for various sorting methods:
// Input: list of about 0.5 million unsorted integers
// Output: sorted list

// Sorts:
// 1. Insertion
// 2. Merge
// 3. Quicksort (my version)
// 4. Quicksort (book version)
// 5. Radix
// 6. Heapsort

#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

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
/////////////////////////

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


/////////////////////////
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


/////////////////////////////

int partition(vector<int>& input, int l, int h){
   int i;
   int p;        // pivot

   p = h;         // one choice for the pivot; or could choose randomly
   int pivot = input.at(p);
   int firsthigh;

   vector<int> lowvals;
   vector<int> hivals;

   for (i = l; i < h; ++i){
      if (input.at(i) >= pivot){
         hivals.push_back(input.at(i));
      }
      else
      {
         lowvals.push_back(input.at(i));
      }
   }
   

   int j = l;
   for (vector<int>::iterator it = lowvals.begin(); it != lowvals.end(); ++it){
      input.at(j++) = *it;
   }
   input.at(j++) = pivot;
   firsthigh = j;
   for (vector<int>::iterator it = hivals.begin(); it != hivals.end(); ++it){
      input.at(j++) = *it;
   }

   return firsthigh - 1;
}

////////////////////////
void QuickSortVector(vector<int>& input, int l, int h){
   int p;    // pivot
   if ((h - l) > 0){
      p = partition(input, l, h);
      QuickSortVector(input, l, p - 1);
      QuickSortVector(input, p + 1, h);
   }

}
///////////////////////
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
      for (int i = N - 1; i >= 0; --i)  // note this is reverse order because items in the same bucket are LIFO
      {
         b[--buckets[(a[i] / exp) % 10]] = a[i];
      }
      for (int i = 0; i < N; ++i)
      {
         a[i] = b[i];
      }

   
      exp *= 10;      
   }

     

     return;

}
////////////////////////

void Merge(int s[], int low, int middle, int high)
{
   int i; /* counter */
   vector<int> buffer1, buffer2; /* buffers to hold elements for merging */

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

////////////////
void InsertionSort(int list[], int N)
{
   for (int i = 0; i < N; ++i)
   {
      int j = i;
      while (j > 1 && list[j-1] > list[j])
      {
         swap(list[j-1], list[j]);
         j--;
      }

   }
}

/////////////
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
   // assumes the top of the heap is out-of-order, sifts down until is in-order
   int position = 1;      // ordinal position in heap
   int child = 2;         // ordinal position in heap
   while (true)
   {
      child = 2*position;
      if (child > N) { break;}
      if (child + 1 <= N)
      {
         if (list[child + 1] >= list[child])
         {
            child += 1;
         }
      }
      if (list[position] >= list[child]) {break;}  // heap is now correctly ordered
      swap(list[position], list[child]);    // sift down
      position = child;
   }
}

void HeapSort(int list[], int N)
{

   // first construct the heap (max-heap)
   for (int i = 1; i <= N; ++i)
   {
      SiftUp(list, i);
   }

   // next sort by extracting max, swapping, and sifting down
   for (int i = N; i > 1; --i)
   {
      swap(list[1], list[i]);
      SiftDown(list, i - 1);
   }
}


//////////////

int main()
{

   ifstream infile;
   infile.open("unsorted_integer_list.txt");
   string numstring;
   vector<int> inputvals;
   int MAXNUM = 100000;      // number of integers to sort
   multimap<int, string> results;

   int count = 1;
   while(infile.good() && count++ <= MAXNUM)
   {
      infile >> numstring;
      inputvals.push_back((atoi)(numstring.c_str()));
   }
   infile.close();

   // make some copies:
   vector<int> inputvals2 = inputvals;
   vector<int> inputvals3 = inputvals;
   vector<int> inputvals4 = inputvals;
   vector<int> inputvals5 = inputvals;
   vector<int> inputvals6 = inputvals;
   vector<int> inputvals7 = inputvals;
   vector<int> inputvals8 = inputvals;


   // clock_t time_qsort1s = clock();
   // QuickSortVector(inputvals, 0, MAXNUM - 1);
   // clock_t time_qsort1f = clock();
   // int time_qsort1 =  time_qsort1f - time_qsort1s;
   // results.insert(pair<int,string>(time_qsort1,"My Quicksort"));


/*
   for (vector<int>::iterator it = inputvals.begin(); it != inputvals.end(); ++it)
   {
      cout << *it << endl;
   }
*/


   clock_t time_qsort2s = clock();
   QuickSortArray(&inputvals2[0], 0, MAXNUM - 1);
   clock_t time_qsort2f = clock();
   int time_qsort2 =  time_qsort2f - time_qsort2s;
   results.insert(pair<int,string>(time_qsort2,"Book Quicksort"));

 
   clock_t time_radixs = clock();
   Radix(&inputvals3[0], MAXNUM);
   clock_t time_radixf = clock();
   int time_radix = time_radixf - time_radixs;
   results.insert(pair<int,string>(time_radix,"Radix"));

 
   // clock_t time_merges = clock();
   // MergeSort(&inputvals4[0], 0, MAXNUM - 1);
   // clock_t time_mergef = clock();
   // int time_merge = time_mergef - time_merges;
   // results.insert(pair<int,string>(time_merge,"Merge"));

  
  

// The insertion sort is so slow that it makes it impractical to compare the other sorts to eachother
// Uncomment for small MAXNUM to see just how slow this is.
/*
   clock_t time_inserts = clock();
   InsertionSort(&inputvals5[0], MAXNUM);
   clock_t time_insertf = clock();
   int time_insert = time_insertf - time_inserts;
   results.insert(pair<int,string>(time_insert,"Insertion"));
*/

   clock_t time_STLs = clock();
   sort(inputvals6.begin(), inputvals6.end());
   clock_t time_STLf = clock();
   int time_STL = time_STLf - time_STLs;
   results.insert(pair<int,string>(time_STL,"STL sort"));

   // for Heapsort it is convenient to shift array so it starts at index 1
   inputvals7.insert(inputvals7.begin(), -10);
   clock_t time_heaps = clock();
   HeapSort(&inputvals7[0], MAXNUM);
   clock_t time_heapf = clock();
   int time_heap = time_heapf - time_heaps;
   results.insert(pair<int,string>(time_heap,"Heap sort"));


   clock_t time_inserts = clock();
   QSortIterative(&inputvals8[0], 0, MAXNUM-1);
   clock_t time_insertf = clock();
   int time_insert = time_insertf - time_inserts;
   results.insert(pair<int,string>(time_insert,"QSort Iterative"));


   cout << "And the winners are ..." << endl;
   for (multimap<int,string>::iterator it = results.begin(); it != results.end(); ++it)
   {
      std::cout << (*it).first << " => " << (*it).second << '\n';
   }


   return 1;
}
