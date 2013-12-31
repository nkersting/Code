// Describe a ‚.n lg n/-time algorithm that, given a set S of n integers and another
// integer x, determines whether or not there exist two elements in S whose sum is
// exactly x.


// First sort the sequence (say mergesort)
// Now loop over the items and for each, binary search for the requisitve partner

#include<iostream>
#include<vector>

using namespace std;


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

int BinarySearch(int list[], int low, int high, int target)
{
   if (low > high) { return -1;}
   if (low == high) {return list[low] == target ? low : -1;}

   int middle = low + (high - low) / 2;
   if (list[middle] == target) {return middle;}
   if (list[middle] > target)
   {
      BinarySearch(list, low, middle - 1, target);
   }
   else
   {
      BinarySearch(list, middle + 1, high, target);
   }
}


int main()
{
   int input[10] = {4,6,3,6,1,3,2,6,8,9};
   //  int input[10] = {1,4,6,7,9,8,5,6,3,2};
   int x = 3;

   // sort with mergesort
   MergeSort(input, 0, 9);

   for (int i = 0; i < 10; ++i)
   {
      cout << input[i] << " ";
   }
   cout << endl;

   //  loop over sorted array and binary search for partner
   for (int i = 0; i < 10; ++i)
   {
      int j = BinarySearch(input, 0, 9, x-input[i]);
      if (j != -1) { cout << i << " and " << j << endl;}
   }

   return 1;
}
