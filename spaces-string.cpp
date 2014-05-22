// Given a string, find the best way to remove spaces from it.

// input ==> a,a,b, , , c, , ,d,e

// output ==> aabcde — all spaces are removed..


#include<iostream>
using namespace std;


string RemoveSpaces(string s)  // linear in space and time
{
   string t = "";
   int i = 0;
   while (s[i])
   {
      if (s[i] != ' ')
      {
         t += s[i];
      }
      ++i;
   }
   return t;
}

void RemoveSpaces2(string& s) // constant space, quadratic time
{
   int i = 0;
   while (s[i])
   {
      if (s[i] == ' ')
      {
         int j = i+1;
         while (s[j])
         {
            if (s[j] != ' ')
            {
               swap(s[i],s[j]);
               break;
            }
            j++;
         }
      }
      i++;
   }
 
   i = 0;
   while (s[i++] != ' ');     // mark last non-space character
   s[i] = '\0';         // terminate the string
}


int main()
{
   string input = "this is a wonderful test";
   cout << RemoveSpaces(input) << endl;

   RemoveSpaces2(input);
   cout << input << endl;


   return 0;
}
