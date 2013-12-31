




// Prim's algorithm for MST





#include <iostream>
#include <vector>
#include <set>

using namespace std;


struct Edge
{
   int src;
   int dest;
   int wt;
   Edge(){}
   Edge(int s, int d, int w)
      {
         src = s;
         dest = d;
         wt = w;
      }
};


struct Node
{
   int label;   // number of this node
   int weight;
   Edge inEdge;   // edge responsible for the assigned weight
   vector<Edge> edges;
   Node (int x, int w)
      {
         label = x;
         weight = w;
         inEdge = Edge(0,0,0);
      }
   Node (int x, int w, Edge e, vector<Edge> eds)
      {
         label = x;
         weight = w;
         inEdge = e;
         edges = eds;
      }

};

struct Graph
{
   int V,E;   // vertices, edges

   vector<Node*> nodes;
   Graph(int v, int e)
      {
         V = v;
         E = e;
      }
};
   
void AddEdge(Graph* g, int s, int d, int w)
{
   for (vector<Node*>::iterator it = g->nodes.begin(); it != g->nodes.end(); ++it)
   {
      if ((*it)->label == s)
      {
         (*it)->edges.push_back(Edge(s, d, w));
      }
      if ((*it)->label == d)
      {
         (*it)->edges.push_back(Edge(d, s, w));
      }
   }
}

struct NodeCompare
{
   bool operator() (const Node& n1, const Node& n2)
      {       
         return n1.weight < n2.weight;
      }
};


// note you must pass by reference here; otherwise the returned iterator is pointing to something unintended!!
// (spent 3 hours debugging this once!!)
multiset<Node, NodeCompare>::iterator FindNode(const multiset<Node, NodeCompare>& nodes, int label)
{
   for (multiset<Node, NodeCompare>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
   {
      if (it->label == label)
      {
         return it;
      }
   }
   return nodes.end();
}

/////////////////////////////////////////////////////////
const int MAXWEIGHT = 10000;

void Prim(Graph* graph)
{
   vector<Edge> result;

   multiset<Node, NodeCompare> tempnodes;
   for (vector<Node*>::iterator it = graph->nodes.begin(); it != graph->nodes.end(); ++it)
   {
      Node temp((*it)->label, (*it)->weight);
      temp.inEdge = (*it)->inEdge;
      temp.edges = (*it)->edges;
      tempnodes.insert(temp);
   }

   // loop: extract minimum element of the set, add its edge to result; update neighbors
   // repeat until set is empty

   while (!tempnodes.empty())
   {
      multiset<Node, NodeCompare>::iterator first = tempnodes.begin();
      result.push_back(first->inEdge);

       // update the edges of this node
      vector<Edge> first_edges = first->edges;
      tempnodes.erase(first);

      for (vector<Edge>::iterator it = first_edges.begin(); it != first_edges.end(); ++it)
      {
         multiset<Node, NodeCompare>::const_iterator curr = FindNode(tempnodes, it->dest);
         
         if (curr != tempnodes.end() && curr->weight > it->wt)
         {     
            int newlabel = curr->label;      
            vector<Edge> newEdges = curr->edges;
            tempnodes.erase(curr);
            tempnodes.insert(Node(newlabel, it->wt, Edge(it->src, it->dest, it->wt), newEdges));
         }
      }

   }

   for (vector<Edge>::iterator it = result.begin(); it != result.end(); ++it)
   {
      cout << it->src << " " << it->dest << " " << it->wt << endl;
   }

}
//////////////////////////////////////////////////////////////////////////////

int main()
{
  
   // CLRS Fig23.1
   Graph* graph = new Graph(9,14);   // note we will get a different answer from the Figure

   graph->nodes.push_back(new Node(0,0));
   for (int i = 1; i < 9; ++i)
   {
      (graph->nodes).push_back(new Node(i,MAXWEIGHT));
   }


   AddEdge(graph, 0, 1, 4);          // (multiple MSTs are possible in general)
   AddEdge(graph, 0, 7, 8);
   AddEdge(graph, 1, 2, 8);
   AddEdge(graph, 1, 7, 11);
   AddEdge(graph, 2, 3, 7);
   AddEdge(graph, 2, 8, 2);
   AddEdge(graph, 2, 5, 4);
   AddEdge(graph, 3, 4, 9);
   AddEdge(graph, 3, 5, 14);
   AddEdge(graph, 4, 5, 10);
   AddEdge(graph, 5, 6, 2);
   AddEdge(graph, 6, 7, 1);
   AddEdge(graph, 6, 8, 6);
   AddEdge(graph, 7, 8, 7);

   Prim(graph);

   return 0;
}
