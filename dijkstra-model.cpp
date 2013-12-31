// Template for Dijkstra-type problems


#include<iostream>
#include<vector>

using namespace std;

struct Node
{
   int index;
   int cost;
   vector<pair<Node*,int> > edges;
   vector<int> path;
   Node (int idx)
      {
         index = idx;
      }
};

// override the comparison operator for nodes so we construct a min-heap
inline bool operator<(const Node &leftNode, const Node &rightNode) {
 if (leftNode.cost != rightNode.cost) return leftNode.cost < rightNode.cost;
 return false;
}

inline bool operator==(const Node &leftNode, const Node &rightNode) {
 return leftNode.cost == rightNode.cost;
}

inline bool operator!=(const Node &leftNode, const Node &rightNode) {
   return !operator==(leftNode, rightNode);
}

inline bool operator>(const Node &leftNode, const Node &rightNode)
{
   return operator<(rightNode, leftNode);
}

inline bool operator<=(const Node &leftNode, const Node &rightNode)
{
   return !operator>(leftNode, rightNode);
}

inline bool operator>=(const Node &leftNode, const Node &rightNode)
{
   return !operator<(leftNode, rightNode);
}



void SiftDown(Node list[], int arraySize, int index)  // for a min-heap
{
   // assumes the top of the heap is out-of-order, sifts down until is in-order
   int position = index;      // ordinal position in heap
   int child = 2*index;         // ordinal position in heap
   while (child < arraySize)
   {
      if (child + 1 < arraySize)
      {
         if (list[child + 1] < list[child])
         {
            child += 1;
         }
      }
      if (list[position] <= list[child]) {break;}  // heap is now correctly ordered
      swap(list[position], list[child]);    // sift down
      position = child;
      child = 2*position;
   }
}

void SiftUp(Node list[], int N)   // for a min-heap
{
   int position = N; 
   while (position > 1)
   {
      int parent = position / 2;
      if (list[parent] <= list[position]) { break; }
      swap(list[parent], list[position]);
      position = parent;
   }
}

int FindHeapPos(vector<Node> nodeheap, int index)
{
   for (int i = 1; i < nodeheap.size(); ++i)
   {
      if (nodeheap.at(i).index == index) { return i;} 
   }
   cout << "Find Index Error!" << endl;
   return -1;
}

const int MAXCOST = 10000;
int Dijkstra(vector<Node> nodeheap, int dest)
{
   int mincost = MAXCOST;
   while (nodeheap.size() > 1)      // recall the lowest element is a dummy filler
   {

      Node currnode = nodeheap.at(1);  // must be lowest-cost node
      swap(nodeheap.at(1), nodeheap.at(nodeheap.size() - 1));
      nodeheap.pop_back();       // we're done with this node, remove it
      SiftDown(&nodeheap[0], nodeheap.size(), 1);  // reorder the heap

      if (currnode.cost == MAXCOST)
      {
         cout << "No exit!" << endl;
         break;            // no good vertices left
      }
      if (currnode.index == dest)
      {
         cout << "Success! " << currnode.path.size() << " steps." << endl;
         for (int i = 0; i < currnode.path.size(); ++i)
         {
            cout << "Node at " << currnode.path.at(i) << endl;
         }
         mincost = currnode.cost;
         break;   // we reached the exit
      }

      for (vector<pair<Node*,int> >::iterator it = currnode.edges.begin();
           it != currnode.edges.end(); ++it)
      {
         if ((it->first)->cost > currnode.cost + it->second)  // Dijkstra
         {
            int idx = FindHeapPos(nodeheap, (it->first)->index);
            nodeheap.at(idx).cost = currnode.cost + it->second;
            nodeheap.at(idx).path = currnode.path;
            nodeheap.at(idx).path.push_back(currnode.index);
            if (nodeheap.at(idx) < nodeheap.at(idx/2))
            {
               SiftUp(&nodeheap[0], idx);  // reorder
            }        
         }
      }   
   }

  return mincost;
}







int main()
{
   // set up a toy network of 5 nodes
   vector<Node> nodeheap;

   ////////////// pointer style ////////////////
   // Node* node1 = new Node(1);
   // node1->cost = 0;
   // Node* node2 = new Node(2);
   // node2->cost = MAXCOST;
   // Node* node3 = new Node(3);
   // node3->cost = MAXCOST;
   // Node* node4 = new Node(4);
   // node4->cost = MAXCOST;
   // Node* node5 = new Node(5);
   // node5->cost = MAXCOST;

   // node1->edges.push_back(pair<Node*,int>(node2, 2));
   // node1->edges.push_back(pair<Node*,int>(node3, 1));
   // node1->edges.push_back(pair<Node*,int>(node4, 4));
   // node2->edges.push_back(pair<Node*,int>(node5, 3));
   // node3->edges.push_back(pair<Node*,int>(node5, 5));
   // node4->edges.push_back(pair<Node*,int>(node5, 0));

   // nodeheap.push_back(*node1);   // dummy to shift start index
   // nodeheap.push_back(*node1);
   // nodeheap.push_back(*node2);
   // nodeheap.push_back(*node3);
   // nodeheap.push_back(*node4);
   // nodeheap.push_back(*node5);


   //////////////////////  address style //////////////////////
   Node node1(1);
   node1.cost = 0;
   Node node2(2);
   node2.cost = MAXCOST;
   Node node3(3);
   node3.cost = MAXCOST;
   Node node4(4);
   node4.cost = MAXCOST;
   Node node5(5);
   node5.cost = MAXCOST;

   node1.edges.push_back(pair<Node*,int>(&node2, 2));
   node1.edges.push_back(pair<Node*,int>(&node3, 1));
   node1.edges.push_back(pair<Node*,int>(&node4, 4));
   node2.edges.push_back(pair<Node*,int>(&node5, 3));
   node3.edges.push_back(pair<Node*,int>(&node5, 5));
   node4.edges.push_back(pair<Node*,int>(&node5, 0));

   nodeheap.push_back(node1);   // dummy to shift start index
   nodeheap.push_back(node1);
   nodeheap.push_back(node2);
   nodeheap.push_back(node3);
   nodeheap.push_back(node4);
   nodeheap.push_back(node5);


   cout << "Minimum path is " << Dijkstra(nodeheap, 5) << endl;

   return 0;
}
