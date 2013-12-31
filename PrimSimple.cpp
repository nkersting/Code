// A simpler way to do Prim's algorithm for MST:
// put the edges in a multiset and add the cheapest one with exactly one vertex in the current set of nodes;
// then remove from the multiset



#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


struct Edge
{
   int src, dest, wt;
   Edge(int s, int d, int w)
      {
         src = s;
         dest = d;
         wt = w;
      }
};

struct Graph
{
   int V,E;   // vertices, edges

   vector<Edge*> edges;
   Graph(int v, int e)
      {
         V = v;
         E = e;
      }
};
   
void AddEdge(Graph* g, int s, int d, int w)
{
   g->edges.push_back(new Edge(s,d,w));
}



struct EdgeCompare
{
   bool operator() (const Edge* e1, const Edge* e2)
      {
         return e1->wt < e2->wt;
      }
};


void PrimMST(Graph* graph)
{
   vector<Edge*> result;
   
   multiset<Edge*, EdgeCompare> edges;
   for (vector<Edge*>::iterator it = graph->edges.begin(); it != graph->edges.end(); ++it)
   {
      edges.insert(*it);
   }

   set<int> nodes;
   nodes.insert(0);   // start here

   while (nodes.size() < graph->V)
   {
      multiset<Edge*, EdgeCompare>::iterator target = edges.end();
      for (multiset<Edge*, EdgeCompare>::iterator it = edges.begin(); it != edges.end(); ++it)
      {         
         if (nodes.find((*it)->src) == nodes.end() ^ nodes.find((*it)->dest) == nodes.end())   // i.e. exactly one edge not in nodes
         {
            result.push_back(*it);
            target = it;
            nodes.insert((*it)->src);
            nodes.insert((*it)->dest);
            break;
         }
      }
      if (target != edges.end() ) 
      {        
         edges.erase(target);      
      }
      else
      {
         cout << "Graph not connected! " << endl;
         return;
      }

   }
   
   for (vector<Edge*>::iterator it = result.begin(); it != result.end(); ++it)
   {
      cout << (*it)->src << " " << (*it)->dest << " " << (*it)->wt << endl;
   }

}


int main()
{

   // CLRS Fig23.1
   Graph* graph = new Graph(9,14);   // note we will get a different answer from the Figure
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

   PrimMST(graph);

   return 0;
}
