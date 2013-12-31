// How many ways to merge N objects into 1 ? 

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



int Fact(int n)
{
   if (n <= 1) { return 1;}
   return n*Fact(n-1);
}

int Comb(int i, int j)
{
   return Fact(i)/Fact(j)/Fact(i-j);
}


int NumWays(int N)
{
   if (N == 1 || N == 2) { return 1;}
   vector<vector<int> > partition = Partition(N);
   
   int grandTotal = 0;
   for (vector<vector<int> >::iterator it = partition.begin() + 1; it != partition.end(); ++it) // skip the trivial partition
   {
      int num = 1;
      int remain = N;
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         if (*it2 == 1) { continue;}   // number of ways to choose 1 object is taken to be 1
         num *= Comb(remain, *it2)*NumWays(*it2);
         remain -= *it2;
      }
      grandTotal += num;
   }
   return grandTotal;
}


///////////////////
int main()
{
   int N;
   cout << "How many objects? ";
   cin >> N;

   cout << "Found " << NumWays(N) << " mergings" << endl;
   

   return 1;
}
