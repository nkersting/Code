// This program counts the number of 1-bits in a given 32-bit integer


#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   int N;

   cout << "Enter a positive number:";
   cin >> N;

   for (int i = log(N)/log(2); i >= 0;  --i)
   {
      cout << ((N >> i)&(1));   // of course we could have just kept track of 1s here
                                // but imagine this is going to be looped over many input N
   }                            // That would be up to 32 computations per input!


   int CountTable[256];             // storing 8-bits at a time is a dynamic programming technique
   for (int j = 0; j < 256; ++j)
   {
      int count = 0;
      for (int i = log(j)/log(2); i >= 0;  --i)
      {
         count += (j >> i)&(1);
      }
      CountTable[j] = count;
   }


   cout << endl << "There are " << CountTable[N & 255] +       // Here we achieve just 4 computations per input
      CountTable[(N >> 8) & 255] + CountTable[(N >> 16) & 255] +
      CountTable[(N >> 24) & 255] << " 1-bits" << endl;


}
