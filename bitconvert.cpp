// Write a function to determine the number of bits required to convert integer A to integer B.
// Input: 31, 14
// Output: 2


#include <iostream>
 
using namespace std;

int BitConvert(int A, int B)
{
   int count = 0;
   while (A > 0 || B > 0)
   {
      count += (A & 1)^(B & 1);
      A = A >> 1;
      B = B >> 1;
      
   }
   return count;
}


int FasterBitConvert(int A, int B)
{
   int count = 0;
   for (int i = A^B; i > 0; i = i >> 1)
   {
      count += (i & 1);
   }
   return count;
}

int main()
{
   cout << BitConvert(31, 14) << endl;;
   cout << FasterBitConvert(31, 14) << endl;
  

   return 0;
}
