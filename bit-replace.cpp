// You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method to set all bits between i and j in N equal to M (e.g., M becomes a substring of N located at i and starting at j).
// EXAMPLE:
// Input: N = 10000000000, M = 10101, i = 2, j = 6
// Output: N = 10001010100

#include<iostream>
#include<vector>

using namespace std;


void BitEmbed(int N, int M, int i, int j)
{
   if (N < M) return;

   // assume that j-i+1 is the correct length of M
   vector<int> Nbits;
   while (N > 0)
   {
      Nbits.push_back(N & 1);
      N = N >> 1;
   }

   vector<int> Mbits;
   while (M > 0)
   {
      Mbits.push_back(M & 1);
      M = M >> 1;
   }

   int L = Nbits.size();
   for (int k = i; k <= j; ++k)
   {
      Nbits.at(k) = Mbits.at(k - i);
   }

   for (vector<int>::reverse_iterator it = Nbits.rbegin(); it != Nbits.rend(); ++it)
   {
      cout << *it;
   }
}



// cute way
void BitChange(int N, int M, int i, int j)
{

   // first make all 1's up to index j, then all 0's:
   int max = ~0; /* All 1’s */
   int left = max - (1<<j - 1);

   // now make all 1's in i positions:
   int right = 1<<i - 1;

   // this is our mask
   int mask = left | right;

   cout << ((N & mask) | (M<<i));

}



int main()
{

   int N = 1<<10;
   int M = 21;
   BitEmbed(N,M,2,6);
   cout << endl;
   BitChange(N,M,2,6);
   return 0;
}
