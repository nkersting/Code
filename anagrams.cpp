// Write a method to decide if two strings are anagrams or not.


#include<algorithm>
#include<iostream>
using namespace std;


bool AreAnagrams(string s1, string s2)
{
   if (s1.length() != s2.length()) { return false;}
   sort(s1.begin(), s1.end());
   sort(s2.begin(), s2.end());

   for (int i = 0; i < s1.length(); ++i)
   {
      if (s1[i] != s2[i]) {return false;}
   }
	
   return true;

}

bool AreAnagrams2(string s1, string s2)
{
   sort(s1.begin(), s1.end());
   sort(s2.begin(), s2.end());
   return s1 == s2;
}


int main()
{
   cout << AreAnagrams2("logarithm", "algorithmic") << endl;
   cout << AreAnagrams2("logarithm", "algorithm") << endl;

   return 1;

}
