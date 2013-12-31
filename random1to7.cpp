
// Given a function which produces a random integer in the range 1 to 5, write a function which produces a random integer in the range 1 to 7.


#include<iostream>
#include<stdlib.h>

using namespace std;




int Random1To7()
{
   int final = 8;
   while (final == 8)
   {
      int root = 5;
      while (root == 5)    // root is 1,2,3, or 4
      {
         root = rand()%5 + 1;
      }
      int root2 = 3;
      while (root2 > 2)
      {
         root2 = rand()%5 + 1;    // root2 is 1 or 2
      }
      final = 2*root - root2 + 1;
   }
   return final;
}

int main()
{
   int total = 0;
   int N = 1000;
   for (int i = 0; i < N; ++i)
   {
      int temp = Random1To7();
      total += temp;
   }
   cout << 1.0*total / N << endl;
   return 0;
}

