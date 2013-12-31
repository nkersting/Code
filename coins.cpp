// Given a set of coin denominators, find the minimum number of coins to make a
// certain amount of change.


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

/////////////////////
int NumWays(vector<int> denoms, int index, int N)
{
   if (N == 0)
   {
      return 1;
   }
   else if (index > denoms.size() - 1 ||
            N < denoms.at(index))
   {
      return 0;         // cannot make change
   }


   int num_ways = 0;
   for (int count = 0; count <= N/denoms.at(index); ++count)
   {
      num_ways += NumWays(denoms, index + 1, N - count*denoms.at(index));
   }
   return num_ways;

}
//////////////////////
void NumWays2(vector<int> denoms, map<int, vector<int> >& counts, vector<int> trial, int index, int N)
{
   if (N == 0)
   {
      int total = 0;
      for (vector<int>::iterator it = trial.begin(); it != trial.end(); ++it)
      {
         total += *it;
      }
      counts[total] = trial;       // add this as a solution
      return;
   }
   else if (index > denoms.size() - 1 ||
            N < denoms.at(index))
   {
      return;         // cannot make change
   }



   for (int count = 0; count <= N/denoms.at(index); ++count)
   {
      trial.at(index) = count;
      NumWays2(denoms, counts, trial, index + 1, N - count*denoms.at(index));
   }
   return;

}
//////////////////
struct node{
   int coin_level;
   int total;
   node(int level,int sum)
      {
         coin_level = level;
         total = sum;
      }
};

///////////////////////////
int NumCombos(vector<int> denoms, vector<double> weights, vector<int> counts)
{
   set<int> combos;

 
   node start_node = node(-1,0);
   queue<node> q;
   q.push(start_node);
   while (!q.empty())
   {
      node top = q.front();
      q.pop();
      if (top.coin_level == denoms.size()-1)
      {
         if (top.total < 100) {combos.insert(top.total);}
      }
      else
      {
         for (int j = 0; j <= counts.at(top.coin_level + 1); ++j)
         {
            q.push(node(top.coin_level + 1, top.total + j*denoms.at(top.coin_level + 1)));            
         }
      }
   }


   return combos.size();
}

/////////////////////
int main()
{
   vector<int> denoms; // coin denominations, in increasing order
   map<int, vector<int> > counts;  // number of each denomination in the best case
   vector<int> trial;
   int N;   // change to make

/*
   denoms.push_back(1);
   denoms.push_back(6);
   denoms.push_back(10);
*/


/*
   denoms.push_back(5);  // AU coinage
   denoms.push_back(10);
   denoms.push_back(20);
   denoms.push_back(50);
*/


   denoms.push_back(1);     // US coinage
   denoms.push_back(5);
   denoms.push_back(10);
   denoms.push_back(25);



   for (int i = 0 ; i < denoms.size(); ++i)
   {
      trial.push_back(0);
   }



   cout << "Change to make: ";
   cin >> N;

   // try all ways
   cout << "There are " << NumWays(denoms, 0, N) << " ways" << endl;

   NumWays2(denoms, counts, trial, 0, N);

   cout << "They are: " << endl;
   for (map<int, vector<int> >::iterator iter = counts.begin(); iter != counts.end(); ++iter)
   {
      for (vector<int>::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
      {
         cout << *it << " ";
      }
      cout << endl;
   }
   cout << endl << endl;

   cout << "The best way is ";

   for (vector<int>::iterator it = ((counts.begin())->second).begin(); 
        it !=  ((counts.begin())->second).end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;


// the following snippet calculates the hardest amount to make change for in an interval
/*
   int lowerbound = 1;
   int upperbound = 100;
   int maxcount = 0; 
   int maxchange = 0;
   vector<int> maxcounts;
   for (int ch = lowerbound; ch <= upperbound; ++ch)
   {
      counts.clear();
      NumWays2(denoms, counts, trial, 0, ch);
      if ((counts.begin())->first > maxcount)
      {
         maxchange = ch;
         maxcount = (counts.begin())->first;
         maxcounts = (counts.begin())->second;
      }

//      cout << ch << " " << counts.begin()->first << endl;



   }
   cout << "The hardest change to make is for " << maxchange << " cents." << endl;

   for (vector<int>::iterator it = maxcounts.begin(); 
        it !=  maxcounts.end(); ++it)
   {
      cout << *it << " ";
   }

*/


// Next we ask the question: what combination of coins maximizes ratio of number of combos to weight?

   vector<double> weights;


   weights.push_back(2.5);   // US coin weights in grams
   weights.push_back(5.0);
   weights.push_back(2.27);
   weights.push_back(5.67);


/*
   weights.push_back(2.83);   // AU coin weights in grams
   weights.push_back(5.65);
   weights.push_back(11.3);
   weights.push_back(15.55);
*/
   /*
   vector<int> coin_counts;
   vector<int> counts_best;
   int best_num = 0;
   double max_ratio = 0;
   int maxcoins = 5;
   for (int n1 = 0; n1 <= maxcoins; ++n1)     
   {
      for (int n2 = 0; n2 <= maxcoins; ++n2)
      {
         for (int n3 = 0; n3 <= maxcoins; ++n3)
         {
            for (int n4 = 0; n4 <= maxcoins; ++n4)
            {
               coin_counts.clear();
               coin_counts.push_back(n1);
               coin_counts.push_back(n2);
               coin_counts.push_back(n3);
               coin_counts.push_back(n4);
               size_t possibilities = NumCombos(denoms, weights, coin_counts) - 1;
               double weight = n1*weights.at(0) +  n2*weights.at(1) + n3*weights.at(2) + n4*weights.at(3);
               double wnratio = (1.0 * possibilities) / (weight + 0.01);

               cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << possibilities << " " << weight << " " << wnratio << endl;
               if (wnratio > max_ratio)
               {
                  max_ratio = wnratio;
                  best_num = possibilities;
                  counts_best = coin_counts;
               }
            }
         }
      }
   }

   cout << "The best combination of coins is ";
   for (vector<int>::iterator it = counts_best.begin(); it != counts_best.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl << "ratio, number of combos = " << max_ratio << " " << best_num << endl;
   */
   return 0;

}
