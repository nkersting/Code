
// In the first half of the 20th century, around the time that Tagalog became the national language of the Philippines, a standardized alphabet was introduced to be used in Tagalog school books (since then, the national language has changed to a hybrid "Pilipino" language, as Tagalog is only one of several major languages spoken in the Philippines).

// Tagalog's 20-letter alphabet is as follows:

// a b k d e g h i l m n ng o p r s t u w y
// Note that not all letters used in English are present, 'k' is the third letter, and 'ng' is a single letter that comes between 'n' and 'o'.

// You are compiling a Tagalog dictionary, and for people to be able to find words in it, the words need to be sorted in alphabetical order with reference to the Tagalog alphabet. Given a list of Tagalog words as a String[], return the same list in Tagalog alphabetical order.




#include<iostream>

using namespace std;

const int ALPH_SIZE = 21;
const string Letters[ALPH_SIZE] = {"a","b","k","d","e","g","h","i","l","m","n","ng","o","p","r","s","t","u","w","y",""};

struct node{
   node* edges[ALPH_SIZE];
   node(){
      for (int i = 0; i < ALPH_SIZE; ++i)
      {
         edges[i] = 0;
      }
   }
};


int Keyconvert(char input)
{
   if (input == 'q') { return 11;}
   for (int i = 0; i < ALPH_SIZE; ++i)
   {
      if (Letters[i][0] == input) { return i;}
   }
   return -1; //shouldn't get here
}


void AddNode(string vals, node* root)
{
   if (vals.length() > 0)
   {
      for (int i = 0; i < ALPH_SIZE; ++i)
      {
         if (root->edges[Keyconvert(vals[0])] != 0)
         {
            AddNode(vals.substr(1,vals.length() - 1), root->edges[Keyconvert(vals[0])]);
            return;
         }
      }
      root->edges[Keyconvert(vals[0])] = new node();   
      AddNode(vals.substr(1,vals.length() - 1), root->edges[Keyconvert(vals[0])] );
   }    
   else
   {
      root->edges[ALPH_SIZE - 1] = new node();       // then end of a word is an 'empty' node
   }
}


void TraverseAndPrint(node* root, string path)
{
   bool found = false;
   for (int i = 0; i < ALPH_SIZE; ++i)
   {
      if (root->edges[i] != 0)
      {
         path += Letters[i];
         TraverseAndPrint(root->edges[i], path);
         found = true;
         path = path.substr(0,path.length() - 1);
      }     
   }
   if (found == false) { cout << path << endl;}
}


int main()
{
//   int N = 4;
   //  string input[] = {"abakada","alpabet","tagalog","ako"};

   // int N = 6;
   // string input[] = {"ang","ano","anim","alak","alam","alab"};

   // int N = 6;
   // string input[] = {"siya","niya","kaniya","ikaw","ito","iyon"};

   // int N = 7;
   // string input[] = {"knilngiggnngginggn","ingkigningg","kingkong","dingdong","dindong","dingdont","ingkblot"};

 
   // int N = 4;
   // string input[] = {"silangang", "baka", "bada", "silang"};

   // pre-process inputs to have one key per character
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < input[i].length(); ++j)
      {
         if (input[i][j] == 'n' && j + 1 < input[i].length() && input[i][j+1] == 'g')
         {
            input[i] = input[i].substr(0,j) + 'q' + input[i].substr(j+2,input[i].length() - j - 2);  // 'q' doesn't ordinarily appear in tagalog, so we can convert to 'ng' later
         }
      }
   }

   for (int i = 0; i < N; ++i)
   {
      cout << input[i] << " ";
   }
   cout << endl;
   cout << endl;


   node* root = new node();
   for (int i = 0; i < N; ++i)
   {
      AddNode(input[i], root);
   }


   TraverseAndPrint(root, "");

   return 0;
}





