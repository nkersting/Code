// Rabin-Karp algorithm: Rolling string hash





#include <iostream>
#include <cmath>

using namespace std;


bool Match(string text, string pattern, int offset)
{
   cout << offset << endl;
   return text.substr(offset, pattern.length()) == pattern;
}

int ModPower(int base, int power, int mod)
{
   int result = 1;
   for (int i = 0; i < power; ++i)
   {
      result = (result*base) % mod;
   }
   return result;
}

int RabinKarp(string text, string pattern)
{
   int N = text.length();
   int k = pattern.length();
   const int B = 71;  // prime, larger than the alphabet
   const int M = 701; // N/M is number of collisions to expect
   int coeff = ModPower(B,k-1,M);  //pre-process

   if (k > N) return -1;   // no match possible

   int hp = 0;
   for (int i = 0; i < pattern.length(); ++i)
   {
      hp = (B*hp + pattern[i]) % M;    // hash the pattern
   }

   int ht = 0;
   for (int j = 0; j < k; ++j)
   {
      ht = (B*ht + text[j]) % M; // hash first block of text
   }

   if (ht == hp && Match(text,pattern,0))
   {
      return 0;
   }


   for (int j = k; j < N - k; ++j)
   {               // begin rolling hash through the text
      ht = ((ht - text[j-k]*coeff) % M + M) % M;
      ht = (B*ht) % M;
      ht = (ht + text[j]) % M;
      if (ht == hp && Match(text,pattern,j-k+1))
      {
         return j-k+1;
      }
   }

   return -1;  //not found
}







int main()
{
   string text = "MultisetisanassociativecontainerthatcontainsasortedsetofobjectsoftypeKey.Unlikeset,multiplekeyswithequalvaluesareallowed.SortingisdoneusingthekeycomparisonfunctionCompare.Search,insertion,andremovaloperationshavelogarithmiccomplexity.";

   string pattern;
   cout << "String to search for: ";
   cin >> pattern;

   cout << "Index is " << RabinKarp(text, pattern);


   return 0;
}
