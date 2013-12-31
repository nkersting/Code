
// Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array. You may assume that the array was originally sorted in increasing order.
// EXAMPLE:
// Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)
// Output: 8 (the index of 5 in the array)

#include<iostream>

using namespace std;


int FindBreak(int list[], int low, int high)
{
   if (high - low == 1) { return low;}

   int middle = (low + high) / 2;
   if (list[middle] <= list[low])
   {
      return FindBreak(list, low, middle);
   }
   else if (list[high] <= list[middle])
   {
      return FindBreak(list, middle, high);
   }
   else return -1; // this list has no such break
}


int Search(int list[], int low, int high, int target)
{
   if (low > high) { return -1;}
   if (low == high) { return list[low] == target ? low : -1;} 

   int middle = (low + high) / 2;
   if (list[middle] == target) { return middle;}

   if (list[middle] > target) 
   {
      return Search(list, low, middle, target);
   }
   else
   {
      return Search(list, middle + 1, high, target);
   }
}


int FindElement(int list[], int N, int element)
{
   int divider = FindBreak(list, 0, N - 1);
   if (divider != -1)
   {
      int firstresult = Search(list, 0, divider, element);
      int secondresult = Search(list, divider+1, N - 1, element);
      return firstresult == -1 ? secondresult : firstresult;
   }
   else  // array was already in order
   {
      return Search(list, 0, N - 1, element);
   }
}



// here's the cute way
int ModBSearch(int input[], int N, int num)
{
   int low = 0;
   int high = N-1;

   while (low <= high)
   {
      int middle = (low + high) / 2;
      if (input[middle] == num) { return middle;}
      if (input[low] < input[middle])  // low end is ordinary interval
      {
         if (num > input[middle])
         {
            low = middle + 1;
         }
         else if (num >= input[low])
         {
            high = middle - 1;
         }
         else
         {
            low = middle + 1;
         }
      }
      else if (input[low] == input[middle])
      {
         low += 1;              // this covers the inefficent case of duplicates
      }
      else    // inverted interval
      {
         if (num < input[middle])      // so the high end is the normal interval
         {
            high = middle - 1;
         }
         else if (num <= input[high])
         {
            low = middle + 1;
         }
         else
         {
            high = middle - 1;
         }
      }
   }

   return -1;
}


int main()
{
 int input[10] = {5,6,7,8,9,0,1,2,3,4};
//   int input[10] = {0,1,2,3,4,5,6,7,8,9};
   //  int input[10] = {1,1,2,1,1,1,1,1,1,1};

   int num;
   cout << "Enter number to search for:";
   cin >> num;

   cout << FindElement(input, 10, num) << endl;

   cout << ModBSearch(input, 10, num) << endl;

   return 1;
}
