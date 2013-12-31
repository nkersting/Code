//Write a method that returns all subsets of a set.


#include<iostream>
#include<vector>

using namespace std;


vector<vector<int> > AllSubsets(vector<int> master_set)
{
   int N = 1<<(master_set.size());
   vector<vector<int> > subsets;

   for (int i = 0; i < N; ++i)
   {
      vector<int> this_subset;
      for (int j = 0; j < master_set.size(); ++j)
      {
         if ((i>>j) % 2 == 1)
         {
	    this_subset.push_back(master_set.at(j));
         }
      }


      subsets.push_back(this_subset);
   }

   return subsets;
}


void AllSubsetsRecursive(vector<int> remaining, vector<vector<int> >& results, vector<int> temp)
{
   if (remaining.size() == 0) {results.push_back(temp); return;}

   int curr = remaining.back();
   remaining.pop_back();
   AllSubsetsRecursive(remaining, results, temp);
   temp.push_back(curr);
   AllSubsetsRecursive(remaining, results, temp);
}

int main()
{
   vector<int> master;
   for (int i = 1; i < 4; i++)
   {
      master.push_back(i);
   }
   

   vector<vector<int> > result = AllSubsets(master);
   for (vector<vector<int> >::iterator it = result.begin(); it != result.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin();
           it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   cout << endl;

   vector<vector<int> > result2;
   vector<int> temp;
   AllSubsetsRecursive(master, result2, temp);
   for (vector<vector<int> >::iterator it = result2.begin(); it != result2.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin();
           it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }

   

}
