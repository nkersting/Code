// compute Levenshtein (edit) distance between two input strings






#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


int LevenshteinMatrix(string s, string t)
{
   vector<vector<int> > M;
   for (int i = 0; i <= s.length(); ++i)
   {
      vector<int> thisrow;
      for (int j = 0; j <= t.length(); ++j)
      {
         thisrow.push_back(0);
      }
      M.push_back(thisrow);
   }
   
 // source prefixes can be transformed into empty string by
  // dropping all characters
   for (int i = 1; i <= t.length(); ++i)
   {
      M.at(0).at(i) = i;
   }


// target prefixes can be reached from empty source prefix
  // by inserting every character
   for (int i = 1; i <= s.length(); ++i)
   {
      M.at(i).at(0) = i;
   }

   for (int i = 1; i <= s.length(); ++i)
   {
      for (int j = 1; j <= t.length(); ++j)
      {
         if (s[i-1] == t[j-1])
         {
            M.at(i).at(j) = M.at(i-1).at(j-1);  // no operation required
         }
         else
         {
            M.at(i).at(j) = min( M.at(i-1).at(j) + 1, M.at(i).at(j-1) + 1);
            M.at(i).at(j) = min(M.at(i).at(j), M.at(i-1).at(j-1) + 1);
         }
      }
   }

   for (int i = 0; i <= s.length(); ++i)
   {
      for (int j = 0; j <= t.length(); ++j)
      {
         cout << M.at(i).at(j) << " ";
      }
      cout << endl;
   }
   


   return M.at(s.length()).at(t.length());
}


int LevenshteinIterative(string s, string t)
{
   if (s == t) return 0;
   if (s.length() == 0) return t.length();
   if (t.length() == 0) return s.length();

   vector<int> upperrow;
   vector<int> lowerrow;

   for (int i = 0; i <= t.length(); ++i)
   {
      upperrow.push_back(i);
   }
   lowerrow = upperrow;

   for (int i = 0; i < s.length(); ++i)
   {
      lowerrow.at(0) = i;
      for (int j = 0; j < t.length(); ++j)
      {
         int cost = (s[i] == t[j] ? 0 : 1);
         lowerrow.at(j + 1) = min(
            upperrow.at(j + 1) + 1,   // insertion
            lowerrow.at(j) + 1       // deletion
            );

         lowerrow.at(j + 1) = min(upperrow.at(j) + cost,   // substitution
                                  lowerrow.at(j + 1));
      }
      upperrow = lowerrow; 
   }

   return lowerrow.at(t.length());
}


int main()
{
   string s1;
   string s2;

   cout << "Enter string1: ";
   cin >> s1;

   cout << "Enter string2: ";
   cin >> s2;

//   cout << "Distance is " << LevenshteinIterative(s1,s2) << endl;;

   cout << "Matrix distance is " << LevenshteinMatrix(s1,s2);

   return 1;

}
