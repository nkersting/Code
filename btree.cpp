//Given two binary trees, write a compare function to check if they are equal or not. Being equal means that they have the same value and same structure.



#include<iostream>


using namespace std;


struct Node
{
   int data;
   Node* left;
   Node* right;

   Node(int input)
      {
         data = input;
      }
};

void MakeNode(Node* root, int val)
{
   Node* curr = root;
   Node* next = curr->left;
   if (val >= curr->data) { next = curr->right;}
   while (next != 0)
   {
      curr = next;
      if (val >= next->data)
      {
         next = next->right;
      }
      else
      {
         next = next->left;
      }
   }
   if (val < curr->data)
   {
      curr->left = new Node(val);
   }
   else
   {
      curr->right  = new Node(val);
   }
}


void MakeNodeRecurse(Node* root, int val)
{
   
   if (val >= root->data)
   {
      if (root->right == 0)
      {
         root->right = new Node(val);
      }
      else
      {
         MakeNodeRecurse(root->right, val);
      }
   }
   else
   {
      if (root->left == 0)
      {
         root->left = new Node(val);
      }
      else
      {   
         MakeNodeRecurse(root->left, val);
      }
   }
}

int FindMin(Node* root)
{
   Node* curr = root;
   Node* next = curr->left;
   while (next != 0)
   {
      curr = next;
      next = next->left;
   }
   return curr->data;
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

void PrintPostOrder(Node* root)
{
   if (root != 0)
   {
      PrintInOrder(root->left);
      PrintInOrder(root->right);
      cout << root->data << " ";
   }
}

void PrintPreOrder(Node* root)
{
   if (root != 0)
   {
      cout << root->data << " ";
      PrintInOrder(root->left);
      PrintInOrder(root->right);
   }
}

int main()
{
   int vals1[10] = {30,3,4,4,5,6,1,2,3,10};
   int vals2[10] = {30,3,4,4,5,-6,1,2,3,10};

   Node* root1 = new Node(vals1[0]);
   for (int i = 1; i < 10; ++i)
   {
      MakeNode(root1, vals1[i]);
   }


   Node* root2 = new Node(vals2[0]);
   for (int i = 1; i < 10; ++i)
   {
      MakeNode(root2, vals2[i]);
   }

   PrintInOrder(root1);
   cout << endl;
   PrintInOrder(root2);
   cout << endl << endl;


   PrintPostOrder(root1);
   cout << endl;
   PrintPostOrder(root2);
   cout << endl << endl;

   PrintPreOrder(root1);
   cout << endl;
   PrintPreOrder(root2);
   cout << endl << endl;

   Node* root3 = new Node(25);
   for (int i = 0; i < 10; ++i)
   {
      MakeNodeRecurse(root3, vals1[i]);
   }
   PrintInOrder(root3);

//   cout << FindMin(root1);

   return 0;
}

