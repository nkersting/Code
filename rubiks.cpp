// naive BFS for Rubik's Cube
// Probably too inefficient to give a solution

#include<iostream>
#include<vector>
#include<queue>


using namespace std;


void ABC(int state[][3][3], int turns, int row)
{
   // faces 0 -> 2 -> 5 -> 4

   if (turns == 0) { return;}
   if (turns == 1)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[0][row][i] = state[2][row][i];
         state[2][row][i] = state[5][row][i];
         state[5][row][i] = state[4][row][i];
         state[4][row][i] = state[0][row][i];
      }
   }
   else if (turns == 2)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[0][row][i] = state[5][row][i];
         state[2][row][i] = state[4][row][i];
         state[5][row][i] = state[0][row][i];
         state[4][row][i] = state[2][row][i];
      }
   }
   else if (turns == 3)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[0][row][i] = state[4][row][i];
         state[2][row][i] = state[0][row][i];
         state[5][row][i] = state[2][row][i];
         state[4][row][i] = state[5][row][i];
      }
   }   
}


void XYZ(int state[][3][3], int turns, int col)
{
   // faces 1 -> 2 -> 3 -> 4

   if (turns == 0) { return;}
   if (turns == 1)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[1][i][col] = state[4][i][col];
         state[2][i][col] = state[1][i][col];
         state[3][i][col] = state[2][i][col];
         state[4][i][col] = state[3][i][col];
      }
   }
   else if (turns == 2)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[1][i][col] = state[3][i][col];
         state[2][i][col] = state[4][i][col];
         state[3][i][col] = state[1][i][col];
         state[4][i][col] = state[2][i][col];
      }
   }
   else if (turns == 3)
   {
      for (int i = 0; i < 3; ++i)
      {
         state[1][i][col] = state[2][i][col];
         state[2][i][col] = state[3][i][col];
         state[3][i][col] = state[4][i][col];
         state[4][i][col] = state[1][i][col];
      }
   }   
}

struct Node
{
   int state[6][3][3];
   vector<string> path;

   Node(int s[][3][3], vector<string> p)
      {
         for (int i = 0; i < 6; ++i)
         {
            for (int j = 0; j < 3; ++j)
            {
               for (int k = 0; k < 3; ++k)
               {
                  state[i][j][k] = s[i][j][k];
               }
            }
         }
         path = p;
      }

   Node(int a, int b, int c, int x, int y, int z, Node curr)
      {
         for (int i = 0; i < 6; ++i)
         {
            for (int j = 0; j < 3; ++j)
            {
               for (int k = 0; k < 3; ++k)
               {
                  state[i][j][k] = curr.state[i][j][k];
               }
            }
         }
         

         ABC(state, a, 0);
         ABC(state, b, 1);
         ABC(state, c, 2);
         XYZ(state, x, 0);
         XYZ(state, y, 1);
         XYZ(state, z, 2);

         path = curr.path;         
         if (a != 0) { path.push_back("a" + a); }
         if (b != 0) { path.push_back("b" + b); }
         if (c != 0) { path.push_back("c" + c); }
         if (x != 0) { path.push_back("x" + x); }
         if (y != 0) { path.push_back("y" + y); }
         if (z != 0) { path.push_back("z" + z); }
      }
};


bool operator==(const Node& n1, const Node& n2)
{
     for (int i = 0; i < 6; ++i)
         {
            for (int j = 0; j < 3; ++j)
            {
               for (int k = 0; k < 3; ++k)
               {
                  if (n1.state[i][j][k] != n2.state[i][j][k])
                  {
                     return false;
                  }
               }
            }
         }
     return true;
}

bool IsUniform(Node n)
{
   for (int side = 0; side < 6; ++side)
   {
      bool goodside = true;
      for (int i = 0; i < 3; ++i)
      {
         for (int j = 0; j < 3; ++j)
         {
            if (n.state[side][i][j] != n.state[side][0][0])
            {
               goodside = false;
               break;
            }
         }
         if (!goodside) { break;}
      }
      if (goodside) { return true;}
   }
   return false;
}

vector<string> BFS(int S[][3][3])
{
   queue<Node> states;
   vector<string> path;
   vector<Node> visited;

   states.push(Node(S, path));
   while(!states.empty())
   {
      cout << "Now looking at " << states.size() << " states" << endl;
      Node top = states.front();
      states.pop();
      visited.push_back(top);

      // check state for one uniform face
      if (IsUniform(top))
      {
         return top.path;
      }

      for (int a = 0; a < 4; ++a)  // rot(a)
      {
         for (int b = 0; b < 4; ++b)  // rot(b)
         {
            if (b == a) { continue;}
            for (int c = 0; c < 4; ++c)  // rot(c)
            {
               if (c == b || c == a) { continue; }
               for (int x = 0; x < 4; ++x)  // rot(x)
               {
                  for (int y = 0; y < 4; ++y)  // rot(a)
                  {                     
                     if (x == y ) { continue; }
                     for (int z = 0; z < 4; ++z)  // rot(a)
                     {
                        if (z == x || z == y) { continue; }
                        Node trial = Node(a,b,c,x,y,z,top);
                        for (vector<Node>::iterator it = visited.begin(); it != visited.end(); ++it)
                        {
                           if (*it == trial) { break; }
                        }
                        states.push(trial);
                     }
                  }
               }
            }
         }
      }
   }
   return path;
}



int main()
{
   int S[6][3][3];   // State for the cube: 6 sides * 3x3 on each side

   // initialize State
   S[0][0][0] = 1;
   S[0][0][1] = 6;
   S[0][0][2] = 3;
   S[0][1][0] = 3;
   S[0][1][1] = 4;
   S[0][1][2] = 5;
   S[0][2][0] = 2;
   S[0][2][1] = 4;
   S[0][2][2] = 5;

   S[1][0][0] = 2;
   S[1][0][1] = 2;
   S[1][0][2] = 6;
   S[1][1][0] = 5;
   S[1][1][1] = 1;
   S[1][1][2] = 3;
   S[1][2][0] = 4;
   S[1][2][1] = 4;
   S[1][2][2] = 1;

   S[2][0][0] = 4;
   S[2][0][1] = 1;
   S[2][0][2] = 6;
   S[2][1][0] = 5;
   S[2][1][1] = 3;
   S[2][1][2] = 1;
   S[2][2][0] = 5;
   S[2][2][1] = 6;
   S[2][2][2] = 6;

   S[3][0][0] = 4;
   S[3][0][1] = 1;
   S[3][0][2] = 2;
   S[3][1][0] = 4;
   S[3][1][1] = 2;
   S[3][1][2] = 6;
   S[3][2][0] = 3;
   S[3][2][1] = 1;
   S[3][2][2] = 1;

   S[4][0][0] = 6;
   S[4][0][1] = 2;
   S[4][0][2] = 3;
   S[4][1][0] = 6;
   S[4][1][1] = 6;
   S[4][1][2] = 4;
   S[4][2][0] = 2;
   S[4][2][1] = 2;
   S[4][2][2] = 3;

   S[5][0][0] = 1;
   S[5][0][1] = 3;
   S[5][0][2] = 4;
   S[5][1][0] = 5;
   S[5][1][1] = 5;
   S[5][1][2] = 2;
   S[5][2][0] = 5;
   S[5][2][1] = 3;
   S[5][2][2] = 5;

   // S[5][0][0] = 3;
   // S[5][0][1] = 3;
   // S[5][0][2] = 3;
   // S[5][1][0] = 3;
   // S[5][1][1] = 3;
   // S[5][1][2] = 3;
   // S[5][2][0] = 3;
   // S[5][2][1] = 3;
   // S[5][2][2] = 3;



   vector<string> moves;
   // Perform BFS and stop when one side is uniform

   moves = BFS(S);

   cout << moves.size() << " moves required!" << endl;
   
   // for (vector<string>::iterator it = moves.begin(); it != moves.end(); ++it)
   // {
   //    cout << *it << " ";
   // }

}
