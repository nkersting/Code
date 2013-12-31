// Determine in O(Log N) time whether a number is divisible by 5
// The technique is to consider the bit-rep of N:
// n0 + 2*n1 + 4*n2 + 8*n3 + ... = N
// Taking mod5 of above, it's n0 + 2*n1 - n2 -2*n3 + n4 ... repeating set of coefficients
// Note this works for testing divisibility of any number:
// mod7:  (1 2 -3) repeats
// mod3:  (1 -1) repeats
// mod (mth power of 2) : check lower m-1 bits all zero


#include <iostream>

using namespace std;

int ShiftSum(int N, int shift, int offset)
{
   int sum = 0;
   N = N >> offset;
   while (N > 0)
   {
      sum += N & 1;
      N = N >> shift;
   }
   return sum;
}


void SumAlt5(int& N)
{
   int oddSum = ShiftSum(N, 4, 0) - ShiftSum(N, 4, 2);
   int evenSum = 2*(ShiftSum(N, 4, 1) - ShiftSum(N, 4, 3));

   N = oddSum + evenSum;
}

bool IsDiv5(int N)
{
   while (N >= 5)
   {
      SumAlt5(N);
   }
   return (N == 0);
}



int main()
{
   cout << "3: " << IsDiv5(3) << endl;
   cout << "5: " << IsDiv5(5) << endl;
   cout << "10: " << IsDiv5(10) << endl;
   cout << "27: " << IsDiv5(27) << endl;
   cout << "90: " << IsDiv5(90) << endl;

   return 0;

}
