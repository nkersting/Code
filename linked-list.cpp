// find the middle node of a linked list




#include <iostream>

using namespace std;


class Node
{
public:  Node* next;
   int data;

   Node(int val)
      {
         data = val;
      }
};

bool FrontInsert(Node** head, int val)
{
   Node* newNode = new Node(val);
   if (!newNode) { return false; }
   newNode->next = *head;
   *head = newNode;
   return true;
}

void Insert(Node* previous, Node* newbie)
{
   newbie->next = previous->next;
   previous->next = newbie;
}

bool DeleteNode(Node** head, Node* target)
{
   Node* curr = *head;
   if (target == *head)
   {
      *head = curr->next;
      delete target;
      return true;
   }

   while (curr != 0)
   {
      if (curr->next == target)
      {
         curr->next = target->next;
         delete target;
         return true;
      }
      curr = curr->next;
   }
   return false;
}

void DeleteList(Node** head)
{
   Node* curr = *head;
   while (curr != 0)
   {
      Node* next = curr->next;
      delete curr;
      curr = next;
   }
   *head = 0;
}


Node* FindNode(Node* head, int val)
{
   while (head != 0 && head->data != val)
   {
      head = head->next;
   } 
   return head;
}


void Traverse(Node* head)
{
   Node* curr = head;
   while (curr != 0)
   {
      cout << curr->data << " ";
      curr = curr->next;
   }
   cout << endl;
}


Node* FindMiddle(Node* head)
{
   Node* slowcurr = head;
   Node* fastcurr = head;

   while (fastcurr->next != 0 && fastcurr->next->next != 0)
   {
      slowcurr = slowcurr->next;
      fastcurr = fastcurr->next->next;
   }
   return slowcurr;
}

int main()
{
   // Node* head = new Node(42);
   // Insert(head, new Node(66));
   // Traverse(head);

   // FrontInsert(&head, -100);
   // Traverse(head);

   // Node* tempNode = new Node(88);
   // Insert(head, tempNode);
   // Traverse(head);

   // DeleteNode(&head, tempNode);
   // Traverse(head);

   Node* head = new Node(1);
   for (int i = 21; i >= 2; --i)
   {
      Node* temp = new Node(i);
      Insert(head, temp);
   }
   
   Traverse(head);

   cout << FindMiddle(head)->data;


   return 0;
}
