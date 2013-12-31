// Largest Common Substring of two strings
// Memoization approach

#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int max(int a, int b)
{
   if (a > b) { return a;}
   else return b;
}



int L[100][100];

int LCS(string s1, string s2)
{
   if (s1.length() == 0 || s2.length() == 0) { return 0;}
   if (L[s1.length()-1][s2.length()-1] != -1)
   {
      return L[s1.length()-1][s2.length()-1];
   }

   if (s1[s1.length() - 1] == s2[s2.length() - 1])
   {
      L[s1.length()-1][s2.length()-1] = 1 + LCS(s1.substr(0,s1.length()-1), s2.substr(0,s2.length()-1));
   }
   else
   {
      L[s1.length()-1][s2.length()-1] = max(LCS(s1.substr(0,s1.length()-1), s2), 
                                            LCS(s1, s2.substr(0,s2.length() - 1)));
   }

   return L[s1.length()-1][s2.length()-1];
}


int main()
{
   string s1 = "ABCDEFGHI";
   string s2 = "ABCEEEXXXXXX";


   for (int i = 0; i < s1.length(); ++i)
   {
      for (int j = 0; j < s2.length(); ++j)
      {
         L[i][j] = -1;
      }
   }

   cout << LCS(s1,s2);


   return 0;
}
