// Solve the partition problem: given a positive integer N, find all the ways to write this as a sum of smaller positive integers.



// This uses a dynamic programming technique to store previous results.
// MUCH faster than recursive technique I tried in the past.

#include <iostream>
#include <vector>

using namespace std;
//////////////////
vector<vector<int> > Partition(int endN)
{
   vector<vector<vector<int> > > partitions;

   // initialize base case N = 1
   vector<int> first;
   vector<vector<int> > firstrows;
   first.push_back(1);
   firstrows.push_back(first);
   partitions.push_back(firstrows);

   for (int i = 1; i < endN; ++i)
   {
      vector<int> head;
      vector<vector<int> > these_sols;
      head.push_back(i + 1);
      these_sols.push_back(head);  // the first way to partition N is just N

      for (int j = i - 1; j >= 0; --j)
      {
         for (vector<vector<int> >::iterator it = (partitions.at(j)).begin();
              it != (partitions.at(j)).end(); ++it)
         {
            if (it->back() >= i - j) 
            {
               vector<int> this_sol = *it;
               this_sol.push_back(i - j);     
               these_sols.push_back(this_sol);
            }
         }
      }
      partitions.push_back(these_sols);
   }


   return partitions.back();
}




///////////////////
int main()
{
   int N;
   cout << "Enter an integer: ";
   cin >> N;

   vector<vector<int> > solutions = Partition(N);

   for (vector<vector<int> >::iterator it = solutions.begin();
        it != solutions.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      } 
      cout << endl;
   }

   cout << "Found " << solutions.size() << " solutions." << endl;

   return 1;
}
