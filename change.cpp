// Given an infinite number of quarters (25 cents), dimes (10 cents), nickels (5 cents) and pennies (1 cent), write code to calculate the number of ways of representing n cents.

#include<vector>
#include<iostream>

using namespace std;


void ChangeCompute(vector<vector<int> >& combos, vector<int> counts, vector<int> denoms, int index, int residual)
{
   if (residual == 0)
   {
      combos.push_back(counts);
      return;
   }

   if (index == denoms.size()) { return;}

   for (int i = 0; i <= residual / denoms.at(index); ++i)
   {

      ChangeCompute(combos, counts, denoms, index + 1, residual - i*denoms.at(index));
      counts.at(index)++;
	
   } 
}


int main()
{
   vector<int> denoms;
   denoms.push_back(25);
   denoms.push_back(10);
   denoms.push_back(5);
   denoms.push_back(1);

   vector<int> counts;
   counts.push_back(0);
   counts.push_back(0);
   counts.push_back(0);
   counts.push_back(0);

   vector<vector<int> > combos;

   int N;
   cout << "Enter integer:";
   cin >> N;

   ChangeCompute(combos, counts, denoms, 0, N);

   cout << "There are " << combos.size() << " ways:" << endl;
   for (vector<vector<int> >::iterator it = combos.begin(); it != combos.end(); ++it)
   {
      for (vector<int>::iterator itr = it->begin(); itr != it->end(); ++itr)
      {
         cout << (*itr) << " ";
      }
      cout << endl;
   }

  return 1;
}
