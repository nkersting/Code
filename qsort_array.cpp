// Quicksort for the input array


#include <iostream>
#include <vector>

using namespace std;


int partition(int (&inputarray)[10], int l, int h){
   int i;
   int p;        // pivot

   p = h;         // one choice for the pivot; or could choose randomly
   int firsthigh;

   vector<int> lowvals;
   vector<int> hivals;

   for (i = l; i < h; ++i){
      if (inputarray[i] >= inputarray[p]){
         hivals.push_back(inputarray[i]);
      }
      else
      {
         lowvals.push_back(inputarray[i]);
      }
   }
   

   int j = l;
   for (vector<int>::iterator it = lowvals.begin(); it != lowvals.end(); ++it){
      inputarray[j++] = *it;
   }
   inputarray[j++] = inputarray[p];
   firsthigh = j;
   for (vector<int>::iterator it = hivals.begin(); it != hivals.end(); ++it){
      inputarray[j++] = *it;
   }

   return firsthigh - 1;
}
//////////////////


////////////////////////
void quicksort(int (&inputarray)[10], int l, int h){
   int p;    // pivot
   if ((h - l) > 0){
      p = partition(inputarray, l, h);
      quicksort(inputarray, l, p - 1);
      quicksort(inputarray, p + 1, h);
   }

}
///////////////////////


int main()
{
   int input[10] = {3,2,6,5,4,22,10,66,90,7};

   quicksort(input, 0, 10);


   cout << "Sorted:" << endl;
   for (int i = 0; i < 10; ++i){
      cout << input[i] << " ";
   }

   return 1;
}
