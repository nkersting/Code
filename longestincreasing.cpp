//Given an array, i) find the longest continuous increasing subsequence. ii) find the longest increasing subsequence.


#include<iostream>
#include<vector>

using namespace std;

pair<int,int> LongestIncreasing(int vals[], int N)
{
   int start = 0;
   int maxidx1 = 0;
   int maxidx2 = 0;

   for (int i = 1; i < N; ++i)
   {
      if (vals[i] <= vals[i-1])
      {
         if (i-1 - start > maxidx2 - maxidx1)
         {
            maxidx1 = start;
            maxidx2 = i-1;
         }
         start = i;
      }
      else if (i == N - 1 && i - start > maxidx2 - maxidx1)
      {
         maxidx1 = start;
         maxidx2 = i;
      }
   }
   
   return pair<int,int>(maxidx1, maxidx2);
}

struct Entry
{
   int val;
   int pos;
   Entry()
      {
         val = 0;
         pos = 0;
      }
   Entry(int value, int position)
      {
         val = value;
         pos = position;
      }
};



void QSort(Entry list[], int low, int high)
{
   if (low >= high) return;

   int pivot = list[low].val;
   int M = low;

   for (int j = low + 1; j <= high; ++j)
   {
      if (list[j].val < pivot)
      {
         M++;
         swap(list[j], list[M]);
      }
   }
   swap(list[low], list[M]);

   QSort(list, low, M-1);
   QSort(list, M+1, high);
}



vector<int> LongestInterrupted(int list[], int N)
{
   Entry vals[N];
   for (int i = 0; i < N; ++i)
   {
      vals[i].val = list[i];
      vals[i].pos = i;
   }

   QSort(vals, 0, N-1);
   int positions[N];
   for (int i = 0; i < N; ++i)
   {
      positions[i] = vals[i].pos;
   }

   vector<int> solution;
   pair<int,int> ends = LongestIncreasing(positions, N);
   for (int i = ends.first; i <= ends.second; ++i)
   {
      solution.push_back(positions[i]);
   }
   return solution;
}

int main()
{
   int input[10] = {1,2,3,4,0,-15,-5,-1,9,10};

   pair<int,int> solution = LongestIncreasing(input, 10);
   cout << solution.first << endl;
   cout << solution.second << endl << endl;

   vector<int> solution2 = LongestInterrupted(input, 10);
   for (vector<int>::iterator it = solution2.begin(); it != solution2.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;

   return 0;
}
