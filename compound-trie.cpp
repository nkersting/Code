// Some languages allow the use of compound words, words that are the concatenation of words from the language's dictionary.
// We have defined a language that consists of a dictionary of distinct words. We want to know whether we should allow the use of compound words constructed by concatenating exactly two distinct dictionary words. The potential problem is that a compound word is ambiguous if either (or both) of the following conditions applies:

// the compound word is a dictionary word
// the compound word can be formed in more than one way.
// For example, if "am","eat","a", "meat", "hook", and "meathook" were all in the dictionary, then "meathook" would be ambiguous according to the first condition, and "ameat" would be ambiguous according to the second condition.

// Create a class CmpdWords that contains a method ambiguous that is given a String[] dictionary and that returns the number of ambiguous words that would result from allowing the compounding of distinct pairs of dictionary words. An ambiguous word should be counted only once, no matter how many different ways it could be formed.



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


void AddWord(Node* root, string word)
{
   if (word.length() == 0)
   {
      root->words_here++;
      return;
   }

   if (root->edges[(int)(word[0] - 'a')] != 0)
   {
      return AddWord(root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1));
   }
   else
   {
      root->edges[(int)(word[0] - 'a')] = new Node();
      return AddWord(root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1));
   }
}

void DFS(Node* root, string word)
{
   if (root->words_here > 0)
   {
      cout << word << endl;
   }

   for (int i = 0; i < 26; ++i)
   {
      if (root->edges[i] != 0)
      {
         DFS(root->edges[i], word + (char)((int)('a') + i));
      }
   }
}


int Combos(Node* master_root, Node* root, string word, int numwords)
{

   if (word.length() == 0)
   {        
      return numwords < 2 && root->words_here > 0;
   }

   if (root->edges[(int)(word[0] - 'a')] != 0)
   {
      if (root->edges[(int)(word[0] - 'a')]->words_here > 0)
      {
         int x = Combos(master_root, master_root, word.substr(1, word.length() - 1), numwords + 1);
         int y = Combos(master_root, root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1), numwords);
         return x + y;
      }
      return Combos(master_root, root->edges[(int)(word[0] - 'a')], word.substr(1, word.length() - 1), numwords); 
   }
   return 0;  
}


int main()
{
   // int N = 9;
   // string words[9] = {"all", "lla", "aba", "bab", "abb", "babas", "sbaba", "hi", "who"};

  // int N = 6;
  // string words[6] = {"am","eat","a", "meat", "hook","meathook"};

 int N = 4;
 string words[4] = {"abc","bca","bab","a"};


   Node* root = new Node();
   for (int i = 0; i < N; ++i)
   {
      AddWord(root, words[i]);
   }

   cout << "Dictionary contains: " << endl;
   DFS(root, "");
   cout << endl << endl;

   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (Combos(root, root, words[i] + words[j], 0) >= 2)
         {
            cout << words[i] + words[j] << endl;
         }
      }
   }


   return 0;
}
