	
// A palindrome is a String that is spelled the same forward and backwards. Given a String base that may or may not be a palindrome, we can always force base to be a palindrome by adding letters to it. For example, given the word "RACE", we could add the letters "CAR" to its back to get "RACECAR" (quotes for clarity only). However, we are not restricted to adding letters at the back. For example, we could also add the letters "ECA" to the front to get "ECARACE". In fact, we can add letters anywhere in the word, so we could also get "ERCACRE" by adding an 'E' at the beginning, a 'C' after the 'R', and another 'R' before the final 'E'. Your task is to make base into a palindrome by adding as few letters as possible and return the resulting String. When there is more than one palindrome of minimal length that can be made, return the lexicographically earliest (that is, the one that occurs first in alphabetical order).


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;



vector<string> ShortestPals(string input)
{

   map<string, vector<string> > pals;  // our dynamic array

   for (int k = 0; k < input.length(); ++k)     // palindrome of X is X
   {
      pals[input.substr(k,1)].push_back(input.substr(k,1));
   }

   for (int i = 2; i <= input.length(); ++i)   // window length
   {
      for (int j = 0; j <= input.length() - i; ++j) // offset
      {
         string temp = input.substr(j,i);
         if (temp[0] == temp[temp.length() - 1])
         {
            if (temp.length() == 2)
            {
               pals[temp].push_back(temp);
            }
            else
            {
               for (vector<string>::iterator it = pals[temp.substr(1, temp.length() - 2)].begin(); it != pals[temp.substr(1, temp.length() - 2)].end(); ++it)
               {
                  pals[temp].push_back(temp[0] + *it + temp[0]);
               }
            }
            continue;
         }

         for (vector<string>::iterator it = pals[temp.substr(1, temp.length() - 1)].begin(); it != pals[temp.substr(1, temp.length() - 1)].end(); ++it)
         {
            pals[temp].push_back(temp[0] + *it + temp[0]);
         }

         for (vector<string>::iterator it = pals[temp.substr(0, temp.length() - 1)].begin(); it != pals[temp.substr(0, temp.length() - 1)].end(); ++it)
         {
            pals[temp].push_back(temp[temp.length() - 1] + *it + temp[temp.length() - 1]);
         }
      }
   }
   
   return pals[input];
}



bool IsPalindrome(string input)
{
   for (int i = 0; i < input.length()/2; ++i)
   {
      if (input[i] != input[input.length() - i - 1]) { return false;}
   }
   return true;
}


struct PalCompare
{
   bool operator()(const string& p1, const string& p2)
      {
         if (p1.length() != p2.length())
         {
            return p1.length() < p2.length();
         }
         else
         {
            return p1 < p2;
         }
      }
} myCompare;


int main()
{
    string input = "RACE";   // answer is "ECARACE"
   //   string input = "TOPCODER";  // answer is "REDTOCPCOTDE"
   // string input = "MADAMIMADAM"; // already a palindrome, so "MADAMIMADAM"
   //   string input = "ALRCAGOEUAOEURGCOEUOOIGFA";  // answer is "AFLRCAGIOEOUAEOCEGRURGECOEAUOEOIGACRLFA" !
   // string input = "OOOOOA";
   //  string input = "OOA";
//     string input = "OOAAAAA";

   vector<string> pals = ShortestPals(input);

   sort(pals.begin(), pals.end(), myCompare);

   cout << pals.at(0);



   return 0;
}



