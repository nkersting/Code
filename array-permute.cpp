// given an array[N] and a desired permutation perm[N], permute the array in-place.



#include<iostream>

using namespace std;


const int N = 10;

void Permute(string vals[], int perm[])
{
   for (int i = 0; i < N; ++i)
   {
      if (perm[i] == i) { continue;} 
    
      swap(vals[i], vals[perm[i]]);

      for (int j = 0; j < N; ++j)  // alternatively, if extra memory allocation is available,
      {                            // we could store the locations of the elements in another array
         if (perm[j] == i)         // such that A[i] = j where perm[j] = i 
         {
            swap(perm[j], perm[i]);
            break;
         } 
      }
   }

}


int main()
{

   int perm[N] = {4,9,3,1,7,8,0,2,6,5};
   string vals[N] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

   cout << "Permutation ordered: ";
   for (int i = 0; i < N; ++i)
   {
      cout << perm[i] << " ";
   }
   cout << endl;

   Permute(vals, perm);

   for (int i = 0; i < N; ++i)
   {
      cout << vals[i] << endl;
   }


}
