// Given an input string, find all the english phrases extractable
// e.g. "tuesday november third" -> "many voted bush retired" for one

// since there are a huge number of anagrams, we make a few constraints:
// 1. no words less than 4 characters
// 2. all lowercase

// Unfortunately, this code prints out all permutations instead of combinations


#include<iostream>
#include<fstream>
#include<set>
#include<stack>
#include<vector>
#include<sstream>
#include<string>


using namespace std;


struct node
{
   string tentative_sentence; 
   int remaining[26];        // letters remaining to be used
   node(string input, int rem[])
      {
         tentative_sentence = input;
         for (int i = 0; i <26; ++i)
         {
            remaining[i] = rem[i];
         }
      }   
};
//////////////////////////
set<string> WordSearch(set<string>& dict, int avail[])
{
   set<string> found;
   found.clear();
 
   for (set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
   {
      int these_chars[26];
      bool is_good = true;
      for (int i = 0; i < 26; ++i)
      {
         these_chars[i] = 0;
      }
      for (int j = 0; j < it->length(); ++j)
      {
         these_chars[(int)((*it)[j]) - 97]++;
      }
      for (int k = 0; k < 26; ++k)
      {
         if (these_chars[k] > avail[k]) {is_good = false;}
      }
      if (is_good)
      {
         found.insert(*it);
      }
   }

   return found;
}
///////////////////
void DFS(set<string>& dict, vector<string>& results, string input)
{
   int initial[26];
   for (int i = 0; i < 26; ++i)
   {
      initial[i] = 0;
   }
   for (int i = 0; i < input.length(); ++i)
   {
      if (input[i] == ' ' || (int)input[i] > 122 || (int)input[i] < 97) { continue;}
      initial[(int)input[i] - 97]++;
   }

   node start_node("", initial);
   stack<node> node_stack;
   node_stack.push(start_node);
   set<string> found_words = WordSearch(dict, initial);
   cout << "Possible Words: ";
   for (set<string>::iterator it = found_words.begin(); it != found_words.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;

   while (!node_stack.empty())
   {
      node top_node = node_stack.top();
      node_stack.pop();

      int empty = true;
      for (int i = 0; i < 26; ++i)
      {
         if (top_node.remaining[i] != 0) {empty = false;}
      }
      if (empty == true)
      {
         results.push_back(top_node.tentative_sentence);
         cout << top_node.tentative_sentence << endl;
      }
      else
      {
         set<string> possible_words = WordSearch(found_words, top_node.remaining);
         for (set<string>::iterator it = possible_words.begin(); it != possible_words.end(); ++it)
         {
             int new_remaining[26];
            for (int i = 0; i < 26; ++i)
            {
               new_remaining[i] = top_node.remaining[i];
            }
            for (int j = 0; j < it->length(); ++j)
            {
               int index = (int)((*it)[j]) - 97;
               new_remaining[index]--;
            }

            string new_string(top_node.tentative_sentence + " " + *it);
            node_stack.push(node(new_string, new_remaining));
         }
      }



   }


}

//////////////////////////
bool GoodWord(string word)
{
   if (word.length() < 4) { return false;}
   for (int i = 0; i < word.length(); ++i)
   {
      if ((int)word[i] > 122 || (int)word[i] < 97) { return false; }
   }
   return true;
}

//////////////////
int main(){

   ifstream dictionary_file;
   dictionary_file.open("dictionary.txt");
   string word;
   set<string> dictionary;
   vector<string> sentences;
   string input_string;

   if (dictionary_file.is_open())
   {
      while(dictionary_file.good())
      {
         dictionary_file >> word;
         if (GoodWord(word)) {dictionary.insert(word);}
      }
      dictionary_file.close();
   }
 
   cout << "Enter a sentence: ";
   cin >> input_string;

   DFS(dictionary, sentences, input_string);

   return 1;
}


