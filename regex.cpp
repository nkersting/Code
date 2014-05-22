// You have to write a function checkRegex() which takes two strings as input, one string represents a regex expression and other is an input string to match with the regex expression passed as the other parameter. Return true if it matches, else false.

// Regex may contain characters ‘a-z’, ‘.’ and ‘*’ where ‘.’ matches any character and ‘*’ means 0 or more occurrences of the previous character preceding it.

// Examples:

// 1) a*b matches b,ab,aab

// 2) a.b matches aab, abb, acb,…, azb

// 3) .* matches all the valid strings formed by using the lowercase letters


#include<iostream>
#include<vector>

using namespace std;

vector<string> RegEx(string reg, string input)  // broken; doesn't handle '*' well
{
   vector<string> results;

      int start = 0;
      int len = 0;
      int idx = 0;
      for (int i = 0 ; i < input.length(); ++i)
      {
         if (idx == reg.length())
         {
            results.push_back(input.substr(start,len));
            start = i+1;
            idx = 0;
            len = 0;
            continue;
         }
         if (reg[idx] == '.' || input[i] == reg[idx])
         {
            len++;
            idx++;
            continue;
         }
         else if (reg[idx] == '*')
         {
            vector<string> backPortion = RegEx(reg.substr(idx+1,reg.length()-idx-1), input.substr(i+1, input.length() - 1 - i));
            for (auto x: backPortion)
            {
               results.push_back(input.substr(start, len) + x);
            }
            idx = 0;
            len = 0;
            start = i+1;
         }
         else    // match broken
         {
            idx = 0;
            len = 0;
            start = i+1;
         }
      }
   
   return results;
}


int main()
{
   string input = "abcdeafg";
   string reg1 = "a*";

   vector<string> results = RegEx(reg1, input);

   for (auto x: results)
   {
      cout << x << endl;
   }

   return 0;
}
