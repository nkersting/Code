// see xorListTriples.cpp ... does this generalize to n-tuples ? 
// For n even, it's 'trivial' xor method
// For n odd, we have more work to do

#include <iostream>

using namespace std;


int Quins()
{
  int N = 11;
  int nums[11] = {3,3,3,3,3,1,1,1,1,1,423};
   int ones = 0;
   int twos= 0;        // xor of all numbers appearing only 2 times
   int threes = 0;     //  same for 3 times
   int fours = 0;      // same for 4 times
   int not_fives, x;

   for (int i = 0; i < N; ++i)
   {
       x = nums[i];  
       fours |= threes & x;
       threes |= twos & x;
       twos |= ones & x;

       ones ^= x;

       not_fives = ~ (ones & twos & threes & fours);
       ones &= not_fives;
       twos &= not_fives;
       threes &= not_fives;
       fours &= not_fives;
   }

   return ones;

}


int main()
{

   int N = 17;
   int nums[17] = {3,3,3,3,1,1,1,1,42,999,999,999,999,0,0,0,0};
   int ones = 0;
   int x;

   for (int i = 0; i < N; ++i)
   {
       x = nums[i];  
       ones ^= x;   // standard trick to remove even number of x from ones
   }

   cout << "The unique element is " << ones << endl;;

   cout << "In the quintuplet array, the unique guy is " << Quins();

   return 0;
}

