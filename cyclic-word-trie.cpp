// http://community.topcoder.com/stat?c=problem_statement&pm=7694
// We can think of a cyclic word as a word written in a circle. To represent a cyclic word, we choose an arbitrary starting position and read the characters in clockwise order. So, "picture" and "turepic" are representations for the same cyclic word.
// You are given a String[] words, each element of which is a representation of a cyclic word. Return the number of different cyclic words that are represented.

#include <iostream>
#include <vector>

using namespace std;


struct Node
{
   Node* edges[26];
   int words_here;
   Node()
      {
         for (int i = 0; i < 26; ++i)
         {
            edges[i] = 0;
         }
         words_here = 0;
      }
};


bool AddOrFindWord(Node* root, string word)
{
   if (word.length() == 0)
   {
      return root->words_here++ > 0;   // i.e. if there was already a word here return true, else add it
   }

   if (root->edges[(int)(word[0] - 'a')] != 0)
   {
      return AddOrFindWord(root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1));
   }
   else
   {
      root->edges[(int)(word[0] - 'a')] = new Node();
      return AddOrFindWord(root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1));
   }
}


void AddCyclicWords(Node* root, string word)
{
   for (int i = 1; i < word.length(); ++i)
   {
      AddOrFindWord(root, word.substr(i, word.length() - i) + word.substr(0,i));
   }
}

vector<string> CountCyclicWords(Node* root, vector<string> input)
{
   vector<string> output;
   for (vector<string>::iterator it = input.begin(); it != input.end(); ++it)
   {
      if (!AddOrFindWord(root, *it))
      {
         output.push_back(*it);
         AddCyclicWords(root, *it);
      }
   }
   return output;
}


int main()
{
   // int N = 5;
   // string words[5] = { "picture", "turepic", "icturep", "word", "ordw" };

   // int N = 7;
   // string words[7] = { "ast", "ats", "tas", "tsa", "sat", "sta", "ttt" };

   // int N = 5;
   // string words[5] = {"aaaa", "aaa", "aa", "aaaa", "aaaaa"};

   int N = 9;
   string words[9] = {"all", "lla", "aba", "bab", "abb", "babas", "sbaba", "hi", "who"};


   vector<string> input;
   for (int i = 0; i < N; ++i)
   {
      input.push_back(words[i]);
   }

   Node* root = new Node();

   vector<string> output = CountCyclicWords(root, input);
   for (vector<string>::iterator it = output.begin(); it != output.end(); ++it)
   {
      cout << *it << endl;
   }

   return 0;
}
