// Kruskal's algorithm for minimal spanning tree



#include <iostream>
#include <vector>
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



bool EdgeCompare (const Edge* e1, const Edge* e2)
{
   return e1->wt < e2->wt;
}

struct Subset
{
   int parent;
   int rank;
};

int FindRoot(Subset subsets[], int index)
{
   if (subsets[index].parent != index)
   {
      subsets[index].parent = FindRoot(subsets, subsets[index].parent);
   }

   return subsets[index].parent;
}

// Union by Rank
void Union(Subset subsets[], int x, int y)
{
   int xroot = FindRoot(subsets, x);
   int yroot = FindRoot(subsets, y);

   // attach smaller rank tree under root of higher rank tree
   if (subsets[xroot].rank < subsets[yroot].rank)
   {
      subsets[xroot].parent = yroot;   // path compression
   }
   else if (subsets[xroot].rank > subsets[yroot].rank)
   {
      subsets[yroot].parent = xroot;
   }
   else       // ranks are the same, so choose one way to append and increment rank
   {
      subsets[yroot].parent = xroot;
      subsets[xroot].rank++;
   }
}


void Kruskal(Graph* graph)
{
   vector<Edge*> result;

   sort(graph->edges.begin(), graph->edges.end(), EdgeCompare);

   int numV = graph->V;
   Subset subsets[numV];
   for (int v = 0; v < numV; ++v)
   {
      subsets[v].parent = v;
      subsets[v].rank = 0;
   }

   int edge_count = 0;
   int index = 0;
   while (edge_count < numV - 1 && index < graph->E)
   {
      Edge* next_edge = graph->edges.at(index++);
      int x = FindRoot(subsets, next_edge->src);
      int y = FindRoot(subsets, next_edge->dest);

      // include this edge if it doesn't make a cycle
      if (x != y)
      {
         result.push_back(next_edge);
         Union(subsets, x, y);
         edge_count++;
      }
   }
   
   for (vector<Edge*>::iterator it = result.begin(); it != result.end(); ++it)
   {
      cout << (*it)->src << " " << (*it)->dest << " " << (*it)->wt << endl;
   }

}


int main()
{

   // Graph* graph = new Graph(4,5);

   // AddEdge(graph, 0, 1, 10);
   // AddEdge(graph, 0, 2, 6);
   // AddEdge(graph, 0, 3, 5);
   // AddEdge(graph, 1, 3, 15);
   // AddEdge(graph, 2, 3, 4);


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

   Kruskal(graph);

   return 0;
}
