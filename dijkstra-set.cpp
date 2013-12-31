// Here we attempt to use Dijkstra to solve the "lifeguard problem": a swimmer is located at the corner of a matrix (in water),
// while the lifeguard starts at the opposite corner (on sand), must find shortest path to swimmer.

// Instead of using a heap, we use a multiset


#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;


struct Node
{
   double cost;
   int weight;
   int x;
   int y;
   vector<pair<int,int> > path;
   Node(int i, int j, double c, int w)
      {
         x = i;
         y = j;
         cost = c;
         weight = w;
         path.push_back(pair<int,int>(x,y));
      }
};

struct NodeCompare
{
   bool operator()(const Node& n1, const Node& n2)
      {
         return n1.cost < n2.cost;
      }

};



void SetTest()   // verifying that multiset can be used as a mutable priority queue
{
   multiset<Node, NodeCompare> nodes;
   for (int i = 0; i < 5; ++i)
   {
      for (int j = 0; j < 5; ++j)
      {
         nodes.insert(Node(i,j,i*j,1));
         cout << i*j << " ";
      }
   }
   cout << endl << endl;

   multiset<Node,NodeCompare>::iterator first = nodes.begin();
   cout << "First node is " << first->x << " " << first->y << " " << first->cost << endl; 

   Node newnode(first->x, first->y, 100,1);
   nodes.erase(first);
   nodes.insert(newnode);

   for (multiset<Node,NodeCompare>::iterator it = nodes.begin(); it != nodes.end(); ++it)
   {
      cout << it->x << " " << it->y << " " << it->cost << endl;
   }
}

multiset<Node,NodeCompare>::iterator FindNode(const multiset<Node, NodeCompare>& nodes, int i, int j)
{
   for (set<Node, NodeCompare>::iterator it = nodes.begin(); it != nodes.end(); ++it)
   {
      if (it->x == i && it->y == j) 
      { 
         return it;
      }
   }
   return nodes.end(); 
}


// return path from 0,0 to (N-1, N-1)
vector<pair<int,int> > Dijkstra(multiset<Node, NodeCompare>& nodes, int N)
{
   vector<pair<int,int> > the_path;  //

   multiset<Node,NodeCompare>::iterator best = nodes.begin();

   while (!nodes.empty())
   {
      multiset<Node,NodeCompare>::iterator best = nodes.begin();

      if (best->x == N-1 && best->y == N-1)
      {
         the_path = best->path;
         the_path.push_back(pair<int,int>(N-1, N-1));
         return the_path;
      }
      int x = best->x;
      int y = best->y;
      double curr_cost = best->cost;
      vector<pair<int,int> >  curr_path = best->path;
      nodes.erase(best);

      //modify neighboring nodes
      for (int i = -2; i <= 2; ++i)
      {
         for (int j = -2; j <= 2; ++j)
         {
            if (i == 0 && j == 0 ) { continue;}
            multiset<Node,NodeCompare>::iterator next = FindNode(nodes, x + i, y + j);
            if (next != nodes.end())
            {
               if (next->cost > curr_cost + sqrt(i*i + j*j)*next->weight)  // update node based on a contrived measure of 'distance'
               {
                  Node replacer(next->x, next->y, curr_cost + sqrt(i*i + j*j)*next->weight, next->weight);
                  replacer.path = curr_path;
                  replacer.path.push_back(pair<int,int>(next->x, next->y));
                  nodes.erase(next);
                  nodes.insert(replacer);
               }
            }
         }
      }
   }
   return the_path;
}


int main()
{
//   SetTest();

   multiset<Node, NodeCompare> nodes;


   // Graph models interface between beach and ocean
   int MAXCOST = 10000;
   int BEACHWEIGHT = 1;
   int OCEANWEIGHT = 2;
   int N = 20; 
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (i == 0 && j == 0)
         {
            nodes.insert(Node(0,0,0,1));
         }
         else if (i < N/2)
         {
            nodes.insert(Node(j,i,MAXCOST,BEACHWEIGHT));    // beach
         }
         else
         {
            nodes.insert(Node(j,i,MAXCOST,OCEANWEIGHT));    // ocean
         }
      }
   }


   vector<pair<int,int> > path = Dijkstra(nodes, N);


   char field[N][N];
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (i >= N/2)
         {
            field[i][j] = '~';
         }
         else
         {
            field[i][j] = '.';
         }
      }
   }

   for (vector<pair<int,int> >::iterator it = path.begin(); it != path.end(); ++it)
   {
      field[it->second][it->first] = 'X';
   }

   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         cout << field[i][j] << " ";
      }
      cout << endl;
   }

   return 0;
}
