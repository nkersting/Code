// check whether a number is a power of 2 or not

#include<iostream>
#include<cmath>

using namespace std;


// first way: keep dividing until zero, count number N
// then raise 2 to that power and check equality
bool IsPower2(int num)
{
   int n = 0;
   int original = num;
   while (num > 1)
   {
      ++n;
      num /= 2;	
   }

   int x = 1;
   while (n > 0)
   {
      x *= 2;
      --n;
   }

   return original == x;
}


// second way: convert to a double and take log base 2. If //mantissa is 0 up to tolerance, we’re good.
bool IsPower2Log(int num)
{
   return (log(1.0*num)/log(2) - floor(log(1.0*num)/log(2))) < 0.001;
}




// third way: check the binary representation of the number //has exactly one ‘1’
bool IsPower2Bit(int num)
{
   int count = 0;
   while (num > 0)
   {
      count += num & 1;
      num = num >> 1;
   }
   return count == 1;
}


int main()
{
   int N;
   cout << "Enter a number:" ;
   cin >> N;

   cout << IsPower2(N) << endl;
   cout << IsPower2Log(N) << endl;
   cout << IsPower2Bit(N) << endl;

   return 0;
}
