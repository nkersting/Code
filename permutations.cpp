// generate all permutations of integers 1,2,3,...,n


#include<iostream>
#include<vector>

using namespace std;


void Generate(vector<vector<int> >& perms, int max, int index, int current[] )
{
   if (index == max)
   {
      vector<int> curr_perm;
      for (int i = 0; i < max; ++i)
      {
         curr_perm.push_back(current[i]);         
      }
      perms.push_back(curr_perm);
      return;
   }
   for (int j = index; j < max; ++j)
   {
      swap(current[index], current[j]);
      Generate(perms, max, index + 1, current);
      swap(current[index], current[j]);
   }

}

int main()
{

   int N;
   vector<vector<int> > perms;
   cout << "Enter a positive integer:";
   cin >> N;

   vector<int> orig;
   for (int i = 1; i <= N; ++i)
   {
      orig.push_back(i);
   }

   Generate(perms, N, 0, &orig[0]);
   

   for (vector<vector<int> >::iterator it_outer = perms.begin(); it_outer != perms.end(); ++it_outer)
   {
      for (vector<int>::iterator it_inner = it_outer->begin(); it_inner != it_outer->end(); ++it_inner)
      {
         cout << *it_inner << " ";
      }
      cout << endl;
   }

   return 1;

}
