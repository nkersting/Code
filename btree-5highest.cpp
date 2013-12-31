//How do you find out the fifth maximum element in an Binary Search Tree in efficient manner.



#include <iostream>

using namespace std;

struct Node
{
   int data;
   Node* parent;
   Node* left;
   Node* right;
   Node (int input)
      {
         data = input;
      }
};


void MakeNode(Node* root, int val)
{
   if (val >= root->data)
   {
      if (root->right == 0)
      {
         root->right = new Node(val);
         root->right->parent = root;
      }
      else
      {
         MakeNode(root->right, val);
      }
   }
   else
   {
      if (root->left == 0)
      {
         root->left = new Node(val);
         root->left->parent = root;
      }
      else
      {
         MakeNode(root->left, val);
      }
   }
}


Node* FindMinimum(Node* root)
{
   if (root->left == 0)
   {
      return root;
   }
   return FindMinimum(root->left);
}

Node* FindMaximum(Node* root)
{
   if (root->right == 0)
   {
      return root;
   }
   return FindMaximum(root->right);
}



Node*  FindSuccessor(Node* curr)
{
   if (curr->right != 0)
   {
      return FindMinimum(curr->right);
   }
   Node* currparent = curr->parent;
   while (currparent != 0 && currparent->right == curr)
   {
      curr = currparent;
      currparent = curr->parent;
   }
   return currparent;
}


Node*  FindPredecessor(Node* curr)
{
   if (curr->left != 0)
   {
      return FindMaximum(curr->left);
   }
   Node* currparent = curr->parent;
   while (currparent != 0 && currparent->left == curr)
   {
      curr = currparent;
      currparent = curr->parent;
   }
   return currparent;
}


void PrintInOrder(Node* root)
{
   if (root != 0)
   {
      PrintInOrder(root->left);
      cout << root->data << " ";
      PrintInOrder(root->right);
   }
}

int main()
{
   int vals[10] = {0,3,4,1,7,5,6,8,1,55};

   Node* root = new Node(vals[0]);
   for (int i = 1; i < 10; ++i)
   {
      MakeNode(root, vals[i]);
   }

   PrintInOrder(root);
   cout << endl;

   Node* curr = FindMaximum(root);
   for (int i = 0; i < 4; ++i)
   {
      cout << curr->data << endl;      
      curr = FindPredecessor(curr);
   }

   return 0;
}
