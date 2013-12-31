//If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
//{20,48,52}, {24,45,51}, {30,40,50}
//For which value of p ≤ 1000, is the number of solutions maximised?
// This code shows the answer is p=840, with 8 solutions

#include <string>
#include <string.h>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;
////////////////////////

///////////////////////

int main()
{
   map<int, vector<vector<int> > > solution_map;
   int max_p = 0;
   int max_sols = 0;

   for (int p = 1000; p >= 3; --p) {
      for (int c = p - 2; c >= 2; --c) {
         for (int a = p - c - 1; a >= 1; --a) {
            int b = p - c - a;
            if (a >= b &&            // avoids double-counting
                a*a + b*b == c*c) {
               vector<int> triple = vector<int>{a,b,c};
               solution_map[p].push_back(triple);
            }
         }
      }
      if (solution_map[p].size() > max_sols) {
         max_sols = solution_map[p].size();
         max_p = p;
      }
   }

   cout << "Maximum number for perimeter of " << max_p << ", in which case " << max_sols << " solutions." << endl << endl;

   for (map<int, vector<vector<int> > >::iterator iter = solution_map.begin();
        iter != solution_map.end(); ++iter){
      std::cout << iter->first << " ";
      for (vector<vector<int> >::iterator iter2 = (iter->second).begin(); iter2 != (iter->second).end(); ++iter2){
         for (vector<int>::iterator iter3 = (*iter2).begin(); iter3 != (*iter2).end(); ++iter3){
            std::cout << *iter3 << " ";
         }
         std::cout << ", ";
      }
      std::cout << std::endl;
   }


   return 1;
}
