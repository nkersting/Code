// find the i-th order element in a given list


#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>
#include <vector>

using namespace std;


int RandomPartition(int vals[], int low, int high)
{

   int rand_idx = low + rand() % (high - low);
   swap(vals[rand_idx], vals[low]);
   int pivot = vals[low];
   int M = low;
   for (int j = low + 1; j <= high; ++j)
   {
      if (vals[j] < pivot)
      {
         M++;
         swap(vals[M], vals[j]);
      }
   } 
   swap(vals[M], vals[low]);

   return M;
}


int RandomSelect(int vals[], int low, int high, int ith)
{
   if (low == high) {  return vals[low];}

   int middle = RandomPartition(vals, low, high);
   int k = middle - low + 1;
   if (k == ith) {return vals[middle];}
   if (ith < k) { return RandomSelect(vals, low, middle - 1, ith);}
   if (ith > k) { return RandomSelect(vals, middle + 1, high, ith - k);}
}



int main()
{
   int vals[10] = {3,4,2,-10,3,66,3,21,7,1};
   vector<int> vecvals(vals, vals + 10);
   int N;

   cout << "Which order element? ";
   cin >> N;

  // sort(vals, vals + 10);
  //  for (int i = 0; i < 10; ++i)
  //  {
  //     cout << vals[i] << " ";
  //  }
  //  cout << endl;

   cout << "That is " << RandomSelect(vals, 0, 9, N) << endl;;


   cout << "Verify:" << endl;
   sort(vecvals.begin(), vecvals.end());
   for (int i = 0; i < 10; ++i)
   {
      cout << vecvals[i] << " ";
   }
   cout << endl;

   return 1;
}
