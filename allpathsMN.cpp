// Given a grid of m X n. Find out the all possible ways to move from (0,0) to (m,n)

#include<iostream>
#include<vector>
#include<queue>

using namespace std;


struct Node{
   int x;
   int y;
   vector<pair<int, int> > path;
   vector<vector<bool> > visited;
   Node(int i, int j, vector<pair<int, int> > parent, vector<vector<bool> > v)
      {
         x = i;
         y = j;
         path = parent;
         path.push_back(pair<int,int>(i,j) );
         visited = v;
         visited.at(j).at(i) = true;
      }
};



int NumPaths(int M, int N)
{
   int count = 0;
   vector<vector<bool> > temp (M, vector<bool>(N,false));
   vector<pair<int,int> > temp2;
   Node source(0,0, temp2 ,temp);

   queue<Node> nodes;
   nodes.push(source);

   while (!nodes.empty())
   {
      Node top = nodes.front();
      nodes.pop();

      if (top.y == M-1 && top.x == N-1)
      {
         ++count;
         for (vector<pair<int, int> >::iterator it = top.path.begin(); it != top.path.end(); ++it)
         {
            cout << it->first << " " << it->second << endl;
         }
         cout << endl << endl;
         continue;
      }

      for (int i = -1; i <= 1; ++i)
      {
         for (int j = -1; j <= 1; ++j)
         {
            if (!(i == 0 ^ j ==0)) // trick to just get up/down/left/right moves
            {
               continue;
            }
            if (top.x + i < 0 || top.x + i >= N ||    
                   top.y + j < 0 || top.y + j >= M ||   // don't go out of matrix 
                      top.visited.at(top.y + j).at(top.x + i) == true)  // or where already been
            {
               continue; 
            }
            nodes.push(Node(top.x + i, top.y + j, top.path, top.visited));
         }
      }           
   }
   return count;
}



int main()
{
   cout << NumPaths(4,4);

   return 0;
}
