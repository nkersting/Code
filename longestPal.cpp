//Write a function to find out longest palindrome in a given string

#include<iostream>
using namespace std;



bool IsPalindrome(string input)
{
   for (int i = 0; i < input.length() / 2; ++i)
   {
      if (input[i] != input[input.length() - i - 1])
      {
         return false;
      }
   }
   return true;
}


string LongestPalindrome(string input)
{
   for (int window = input.length(); window > 0; --window)
   {
      for (int offset = 0; offset <= input.length() - window; ++offset)
      {
         if (IsPalindrome(input.substr(offset, window)))
         {
            return input.substr(offset, window);
               }
      }
   }
   return "";
}


int main()
{
   cout << LongestPalindrome("") << endl;
   cout << LongestPalindrome("ababababababababab") << endl;
   cout << LongestPalindrome("radar") << endl;
   cout << LongestPalindrome("radars") << endl;
   cout << LongestPalindrome("xradar") << endl;
   cout << LongestPalindrome("zasabbaeee") << endl;
   cout << LongestPalindrome("abcdefghi") << endl;
   cout << LongestPalindrome("nolemonsnomelonwhatareyousaying?") << endl;
   return 0;
}



