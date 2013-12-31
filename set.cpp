#include <iostream>
#include <set>

using namespace std;

int main()
{
   set<int> test;

   test.insert(5);
   test.insert(10);
   test.insert(-22);

   for (set<int>::reverse_iterator it = test.rbegin(); it != test.rend(); ++it)
   {
      std::cout << *it << " ";
   }


   for (set<int>::iterator it = test.begin(); it != test.end(); ++it)
   {
      std::cout << *it << " ";
   }
   

}
