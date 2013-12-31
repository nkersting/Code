// Write a function that reverses the order of the words in a string. For example, your
// function should transform the string “Do or do not, there is no try.” to “try. no is
// there not, do or Do”. Assume that all words are space delimited and treat punctuation
// the same as letters.



#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

string Reverse(string input)
{
   vector<string> reverse;
   stringstream ss(input);


   while (ss.good())
   {
      string thisString;
      ss >> thisString;
      reverse.push_back(thisString);
   }

   string result;
   int count = 0;
   for (vector<string>::iterator it = reverse.end() - 1; it != reverse.begin() - 1; --it)
   {
      result.append(*it);
      if (++count != reverse.size())
      {
         result.append(" ");
      }
   }

   return result;
}



int main()
{
   cout << Reverse("hello there, dude.") << endl;
   return 1;

}
