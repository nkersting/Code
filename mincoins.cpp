// Given a sum and a list of denominations, determine the minimum number of coins needed
// to make up the sum


#include <iostream>
#include <vector>

using namespace std;


// dynamic programming approach

const int MAXVAL =  10000;

int VecVal(vector<int> mins, int index, int offset)
{
   if (index - offset < 0) { return MAXVAL; }
   return mins.at(index - offset);
}


int MinCoins(vector<int> denoms, int sum)
{
   vector<int> mins;
   mins.push_back(0);  // 0 coins needed to make 0 change

   for (int i = 1; i <= sum; ++i)
   {
      int minv = 1000;
      for (vector<int>::iterator it = denoms.begin(); it != denoms.end(); ++it)
      {
         if (1 + VecVal(mins, i, *it) < minv)
         {
            minv = 1 + VecVal(mins, i, *it);
         }
      }
      mins.push_back(minv);
   }

   return mins.back();
}



int main(int argv, char** argc)
{
   vector<int> denoms;
   denoms.push_back(1);
   denoms.push_back(5);
   denoms.push_back(10);
   denoms.push_back(25);

   for (int i = 0; i <= 100; ++i)
   {
      cout << MinCoins(denoms, i) << endl;
   }

   return 0;
}
