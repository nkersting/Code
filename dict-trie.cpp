// Suppose all the spaces are removed from a document. How can you recover the words?
// Answer: represent your dictionary as a trie, then walk through the string and parse
// as you go (there may be more than one correct parsing)




#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;


const int ALPH_SIZE = 26;   // assuming lower-case words a-z

struct node{
   int words_here;
   node* edges[ALPH_SIZE];
   node()
      {
         words_here = 0;
         for (int i = 0; i < ALPH_SIZE; ++i)
         {
            edges[i] = 0;
         }        
      }
};

int ToInt(char input)
{
   int result = (int)input - (int)('a');
   if (result < 0 || result >= ALPH_SIZE)
   {
      cout << "illegal char" << endl;
      return 0;
   }
   return result;
}


void AddNode(node* root, string word)
{
   if (word.length() > 0)
   {
      if (root->edges[ToInt(word[0])] != 0)
      {
         AddNode(root->edges[ToInt(word[0])], word.substr(1,word.length() - 1));
         return;
      }      
      root->edges[ToInt(word[0])] = new node();
      AddNode(root->edges[ToInt(word[0])], word.substr(1,word.length() - 1));
   }
   else
   {
      (root->words_here)++;
   }
}


void TraverseAndPrint(node* root, string built_word)
{
   for (int j = 0; j < root->words_here; ++j)
   {
      cout << built_word << endl;
   }
   for (int i = 0; i < ALPH_SIZE; ++i)
   {
      if (root->edges[i] != 0)
      {
         built_word +=  (char)(int('a') + i);
         TraverseAndPrint(root->edges[i], built_word);
         built_word = built_word.substr(0, built_word.length() - 1);
      }
   }

}


void ParseAndPrint(node* root, node* subroot, string test, vector<string> result, string built)
{
   if (test.length() == 0)
   {
      if (subroot->words_here > 0)
      {
         result.push_back(built);
         for (vector<string>::iterator it = result.begin(); it != result.end(); ++it)
         {
            cout << *it << " ";
         }
         cout << endl;
      }
      return;
   }
   
   if (subroot->words_here > 0)     // already have built a word match, add to result, go back to root and repeat
   {
      result.push_back(built);
      ParseAndPrint(root, root, test, result, "");
      result.pop_back();
   }
   if (subroot->edges[ToInt(test[0])] != 0)  // we can continue building a word
   {
      ParseAndPrint(root, subroot->edges[ToInt(test[0])], test.substr(1, test.length() - 1), result, built + test[0]);
   }
}



bool GoodWord(string word)
{
   if (word.length() < 3) { return false;}
   for (int i = 0; i < word.length(); ++i)
   {
      if (word[i] > 'z' || word[i] < 'a') { return false; }
   }
   return true;
}

int main()
{

//   int N = 3;
//   string input[] = {"hello", "hell", "one"};
   // node* root = new node();
   // for (int i = 0; i < N; ++i)
   // {
   //    AddNode(root, input[i]);
   // }

   //   TraverseAndPrint(root, "");


   int N = 0;
   ifstream dictionary_file;
   dictionary_file.open("dictionary.txt");
   string word;
   node* root = new node();
   while(dictionary_file.good())
   {
      dictionary_file >> word;
      if (GoodWord(word)) 
      {
         N++;
         AddNode(root, word);
      }
   }




//   string test = "oneonehellohellone";
   //  string test = "hell";

   //  string test = "extraextraordinarypeanutbutteralgorithmbelieflight";
   string test = "pluralforbiddeneverywordmorethreecharacter";
   vector<string> result;
   ParseAndPrint(root, root, test, result, "");

   return 0;
}
