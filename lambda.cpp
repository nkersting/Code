

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


int main()
{
   vector<int> vals{3,3,3,23,2,1};

   for (auto x:  vals)
   {
      cout << x << " ";
   }
   cout << endl;


   for_each(vals.begin(), vals.end(), [](int& v){v = v*v;});
   cout << endl;
   

  for (auto x:  vals)
   {
      cout << x << " ";
   }
   cout << endl;


   return 0;
}
