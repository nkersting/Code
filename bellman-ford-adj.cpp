// Bellman-Ford solution to multiple inequalities, using adjacency list instead of matrix




#include <iostream>
#include <vector>
#include <map>

using namespace std;



vector<int> BellmanFord(const vector<vector<int> >&  edges, int N)
{
   vector<int> distances(N, 0);
   
   for (int i = 1; i <= N; ++i)  // algorithm requires N relaxation cycles
   {
      for (vector<vector<int> >::const_iterator it = edges.begin(); it != edges.end(); ++it)
      {
         if (distances.at(it->at(1)) > distances.at(it->at(0)) + it->at(2))
         {
            distances.at(it->at(1)) = distances.at(it->at(0)) + it->at(2);
         }       
      }
   }

   for (vector<vector<int> >::const_iterator it = edges.begin(); it != edges.end(); ++it)
   {
      if (distances.at(it->at(1)) > distances.at(it->at(0)) + it->at(2))
      {
         cout << "Negative cycle!" << endl;
      }       
   }

   return distances;
}

vector<int> MakeEdge(int i, int j, int w)
{
   vector<int> edge;
   edge.push_back(i-1);
   edge.push_back(j-1);
   edge.push_back(w);
   return edge;
}

int main()
{
   // Our System:
   // x1 - x2 <= -5
   // x2 - x4 <= 4
   // x4 - x5 <= 0
   // x5 - x3 <= -1
   // x3 - x2 <= -3
   
   // int N = 5;  // vertices;
   // vector<vector<int> >  edges;  // three elements each: i, j, weight
   // edges.push_back(MakeEdge(2,1,-5));
   // edges.push_back(MakeEdge(4,2,4));
   // edges.push_back(MakeEdge(5,4,0));
   // edges.push_back(MakeEdge(3,5,-1));
   // edges.push_back(MakeEdge(2,3,-3));


   // CLRS ex. 24.4-1
   int N = 6;  // vertices
   vector<vector<int> >  edges;  // three elements each: i, j, weight
   edges.push_back(MakeEdge(2,1,1));
   edges.push_back(MakeEdge(4,1,-4));
   edges.push_back(MakeEdge(3,2,2));
   edges.push_back(MakeEdge(5,2,7));
   edges.push_back(MakeEdge(6,2,5));
   edges.push_back(MakeEdge(6,3,10));
   edges.push_back(MakeEdge(2,4,2));
   edges.push_back(MakeEdge(1,5,-1));
   edges.push_back(MakeEdge(4,5,3));
   edges.push_back(MakeEdge(3,6,-8));

   vector<int> sol = BellmanFord(edges, N);
   
   for (vector<int>::iterator it = sol.begin(); it != sol.end(); ++it)
   {
      cout << *it << endl;
   }


   return 0;
}
