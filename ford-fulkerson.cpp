// maximum flow algorithm



#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>

using namespace std;



/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */

bool BFS(vector<vector<int> > rGraph, int s, int t, int parent[])
{
   int N = rGraph.size();

   // Creat visited array and initialized
   bool visited[N];
   memset(visited, 0 , sizeof(visited));

   queue<int> q;
   q.push(s);
   visited[s] = true;
   parent[s] = -1;

   // standard BFS
   while (!q.empty())
   {
      int u = q.front();
      q.pop();

      for (int v = 0; v < N; ++v)
      {
         if (visited[v] == false && rGraph[u][v] > 0) // there is a path with extra capacity
         {
            q.push(v);
            parent[v] = u;
            visited[v] = true;
         }
      }
   }

   return visited[t] == true;  // we can reach sink from source in BFS
}

int FordFulkerson(vector<vector<int> > capacities, int s, int t)
{
   int u, v;

   int N = capacities.size();

   // Create the residual graph, initialize to capacities
   vector<vector<int> > rGraph = capacities;


   int parent[N];
   int max_flow = 0;

   // Augment the flow while there is a path
   while (BFS(rGraph, s, t, parent))
   {
      int path_flow = INT_MAX;
      for (v = t; v != s; v = parent[v])  // walk from sink to source, take min flow
      {
         u = parent[v];
         path_flow = min(path_flow, rGraph[u][v]);
      }

      for (v = t; v != s; v = parent[v]) // now walk again and update residual graph
      {
         u = parent[v];
         rGraph[u][v] -= path_flow;
         rGraph[v][u] += path_flow;
      }

      max_flow += path_flow;
   }

   cout << endl;
   for (u = 0; u < N; ++u)
   {
      for (v = 0; v < N; ++v)
      {
         cout << rGraph[u][v] << " ";
      }
      cout << endl;
   }
   cout << endl;


   return max_flow;
}



int main()
{
   // int N = 4;
   // int capac[4][4] = {{0,4,3,2},
   //                         {0,0,0,4},
   //                         {0,0,0,3},
   //                         {0,0,0,0}};
  // for (int i = 0; i < N; ++i)
  //  {
  //     vector<int> thisrow;
  //     for (int j = 0; j < N; ++j)
  //     {
  //        thisrow.push_back(capac[i][j]);
  //     }
  //     capacities.push_back(thisrow);     
  //  }


  // Bipartite-matching
   int N = 10;

   vector<vector<int> > capacities;

   for (int i = 0; i < N; ++i)
   {
      vector<int> thisrow;
      for (int j = 0; j < N; ++j)
      {
         thisrow.push_back(0);
      }
      capacities.push_back(thisrow);     
   }

   capacities.at(0).at(1) = 1;
   capacities.at(0).at(2) = 1;   // super-source edges
   capacities.at(0).at(3) = 1;
   capacities.at(0).at(4) = 1;

   capacities.at(1).at(6) = 1;
   capacities.at(1).at(7) = 1;

   capacities.at(2).at(5) = 1;
   capacities.at(2).at(6) = 1;
   capacities.at(2).at(7) = 1;

   capacities.at(3).at(7) = 1;
   capacities.at(3).at(8) = 1;

   capacities.at(4).at(7) = 1;

   capacities.at(5).at(9) = 1;
   capacities.at(6).at(9) = 1;  // super-sink edges
   capacities.at(7).at(9) = 1;
   capacities.at(8).at(9) = 1;



   cout << "Max flow is " << FordFulkerson(capacities, 0, N-1) << endl;



////////// Skeina Fig 6.13

   int M = 7;
   vector<vector<int>> caps(M, vector<int>(M, 0));


   caps[0][1] = 5;
   caps[0][3] = 12;
   caps[1][4] = 7;
   caps[1][2] = caps[2][1] = 9;
   caps[2][4] = caps[4][2] = 3;
   caps[2][3] = caps[3][2] = 4;
   caps[3][5] = 7;
   caps[2][5] = caps[5][2] = 3;
   caps[4][6] = 5;
   caps[5][6] = 2;

   cout << "Max flow is " << FordFulkerson(caps, 0, M-1) << endl;
   

   return 0;
}
