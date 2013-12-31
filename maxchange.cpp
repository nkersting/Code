// Given two sequences of items, find the items whose absolute number increases or decreases the most when comparing one sequence with the other by reading the sequence only 
// once.


#include<iostream>

using namespace std;


int MaxChange(int s1[], int s2[], int N)
{
   int max = -10000;
   int index = 0;

   for (int i = 0; i < N; ++i)
   {
      if (s1[i] - s2[i] > max || s1[i] - s2[i] < -max)
      {
         index = i;
         max = s1[i] - s2[i];
      }
   }

   return index + (max > 0 ? 1000*max : -1000*max);   // combine info in one integer
}


int main()
{
   int s1[10] = {3,5,51,-10,4,2,10,5,3,1};
   int s2[10] = {5,2,1,9,5,7,-1,5,-10,1};

   for (int i = 0; i < 10; ++i)
   {
      cout << s1[i] << " ";
   }
   cout << endl;

  for (int i = 0; i < 10; ++i)
   {
      cout << s2[i] << " ";
   }
   cout << endl;



   cout << MaxChange(s1, s2, 10);

   return 0;
}
