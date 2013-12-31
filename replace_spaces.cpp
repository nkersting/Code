//Write a method to replace all spaces in a string with ‘%20’.

#include<iostream>

using namespace std;


void ReplaceSpaces(string& s1)
{
   for (int i = 0; i < s1.length(); ++i)
   {
      if (s1[i] == ' ')
      {
         s1 = s1.substr(0, i).append("%20").append(s1.substr(i+1, s1.length() - i - 1));
      }

   }
}

int main()
{
//   string input("hello there");
   string input("   ");
   ReplaceSpaces(input);
   cout << input << endl;

   return 1;
}
