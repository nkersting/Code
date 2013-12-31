// Huffman codes given a list of chars/freqs


#include <iostream>
#include <map>
#include <set>

using namespace std;

struct Node
{
   char val;
   int freq;
   Node* left;
   Node* right;
   Node (char input, int f, Node* l, Node* r)
      {
         val = input;
         freq = f;
         left = l;
         right = r;
      }
};

struct NodeCompare
{
   bool operator()(const Node* n1, const Node* n2)
      {
         return n1->freq < n2->freq;
      }
};

Node* Huffman(const map<char,int>& charFreqs)
{
   multiset<Node*, NodeCompare> nodes;

   //initialize leaf nodes
   for (map<char,int>::const_iterator it = charFreqs.begin(); it != charFreqs.end(); ++it)
   {
      Node* this_node = new Node(it->first, it->second, 0, 0);
      nodes.insert(this_node);
   }

   for (multiset<Node*, NodeCompare>::iterator it = nodes.begin(); it != nodes.end(); ++it)
   {
      cout << (*it)->val << " " << (*it)->freq << endl;
   }
   cout << endl << endl;

   while (nodes.size() > 1)
   {
      multiset<Node*, NodeCompare>::iterator it1 = nodes.begin();
      Node* n1 = *it1;
      nodes.erase(it1);
      
      multiset<Node*, NodeCompare>::iterator it2 = nodes.begin();
      Node* n2 = *it2;
      nodes.erase(it2);

      Node* parent = new Node('\0', n1->freq + n2->freq, n1->freq > n2->freq ? n2 : n1, 
                              n1->freq > n2->freq ? n1 : n2);
      if (nodes.empty())
      {
         return parent;
      }
      
      nodes.insert(parent);
   }

   return *(nodes.begin());

}


void PrintCodes(Node* root, string code)
{
   if (root->left)
   {
      PrintCodes(root->left, code + '0');
   }
   if (root->right)
   {
      PrintCodes(root->right, code + '1');

   }
   if (!root->left && !root->right) // leaf node
   {
      cout << root->val << " " << root->freq << " " << code << endl;
   }
}


int main()
{
   map<char,int> charFreqs;
   for (int i = 1; i <= 10; ++i)
   {
      charFreqs.insert(pair<char, int>( (char)(i+96), i*i*i));
   }

   // GeeksForGeeks example http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
   // charFreqs.insert(pair<char,int>('a',5));
   // charFreqs.insert(pair<char,int>('b',9));
   // charFreqs.insert(pair<char,int>('c',12));
   // charFreqs.insert(pair<char,int>('d',13));
   // charFreqs.insert(pair<char,int>('e',16));
   // charFreqs.insert(pair<char,int>('f',45));

   Node* root = Huffman(charFreqs);

   PrintCodes(root, "");


   return 0;
}
