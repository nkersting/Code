// Given a text string with no spaces, parse into all the English words
// e.g. "peanutbutter" -> "peanut butter"
// Assumptions:
// 1. all lowercase, normal words in a given dictionary (set of strings)
// 2. no punctuation
//


#include <string>
#include <string.h>
#include <map>
#include <set>
#include <iostream>

using namespace std;

////////////////////////
bool AlreadyUsed(int aOfst, int aWlen, const map<int, bool>& aUsed)
{
  for (int i = aOfst; i < aOfst + aWlen; i++)
   {
      if (aUsed.find(i) != aUsed.end())
      {
         return true;
      }
   }
  return false;
}

/////////////////////////

void MarkUsed(int aOfst, int aWlen,  map<int, bool>& aUsed)
{
   for (int i = aOfst; i < aOfst + aWlen; i++)
   {
      aUsed[i] = true;
   }

}
/////////////////////////
void PrintWords(map<int, string> aWords)
{
   for (map<int, string>::const_iterator iter = aWords.begin(); iter != aWords.end(); iter++)
   {
      cout << iter->second << " " << endl;
   }
}

///////////////////////

int main()
{

   string inputString = "peanutbutterandjelly";
   cout << inputString << endl;

   string tmp[] = {"peanut", "butter", "pea", "nut", "p", "e", "a", "n", "u", "t", "and", "jelly", "an", "el", "but"};
   set<string> mainDictionary(tmp, tmp + sizeof(tmp)/sizeof(tmp[0]));
   map<int, string> parsedWords;
   map<int, bool> alreadyUsed;

   for (int wlen = 20; wlen > 0; wlen--)
   {
      for (int ofst = 0; ofst <= int(inputString.length()) - wlen; ofst++)
      {
         string targetString = inputString.substr(ofst, wlen);
         if (mainDictionary.find(targetString) != mainDictionary.end()
             && !AlreadyUsed(ofst, wlen, alreadyUsed))
         {
            parsedWords[ofst] = targetString;
            MarkUsed(ofst, wlen, alreadyUsed);
         }
      }
   }


   PrintWords(parsedWords);


   return 1;
}
