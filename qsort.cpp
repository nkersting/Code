// Quicksort for the input array


#include <iostream>
#include <vector>

using namespace std;


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
//////////////////


////////////////////////
void quicksort(vector<int>& input, int l, int h){
   int p;    // pivot
   if ((h - l) > 0){
      p = partition(input, l, h);
      quicksort(input, l, p - 1);
      quicksort(input, p + 1, h);
   }

}
///////////////////////


int main()
{
   vector<int> input; // = {3,2,6,5,4,22,10,66,90,7};
   input.push_back(3);
   input.push_back(2);
   input.push_back(6);
   input.push_back(5);
   input.push_back(4);
   input.push_back(22);
   input.push_back(10);
   input.push_back(66);
   input.push_back(0);

   quicksort(input, 0, input.size() - 1);

   cout << "Sorted:" << endl;
   for (vector<int>::const_iterator iter = input.begin(); iter != input.end(); ++iter){
      cout << *iter << " ";
   }

   return 1;
}
