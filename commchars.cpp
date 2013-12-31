// Write a function f(a, b) which takes two character string arguments and returns a string containing only the characters found in both strings in the order of a. Write a version which is order N-squared and one which is order N.


#include<iostream>
#include<set>

using namespace std;

string CommonTwo(char* a, char* b)
{
   set<char> chars;
  
   int count = 0;
   while (a[count++] != '\0')
   {
      int innercount = 0;
      while (b[innercount++] != '\0')
      {
         if (a[count] == b[innercount])
         {
            chars.insert(a[count]);
            break;
         }
      }
   }
  
   string common;
   for (set<char>::iterator it = chars.begin(); it != chars.end(); ++it)
   {
      common += *it;
   }

   return common;
}


string CommonTwoN(char *a, char *b)
{
   string common;
   set<char> chars;
   int count = 0;
   while (b[count] != '\0')
   {
      chars.insert(b[count++]);
   }
   count = 0;
   while (a[count] != '\0')
   {
      if (chars.find(a[count]) != chars.end() && common.find(a[count]) == string::npos)
      {
         common += a[count];
      }
      count++;
   }
   return common;
}

int main()
{
   cout << CommonTwo("hellopyre", "jelly") << endl; 
   cout << CommonTwoN("hellopyre", "jelly") << endl;

   return 0;
}
