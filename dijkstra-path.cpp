// Walking out of a weighted maze; see problem statement here:
// http://community.topcoder.com/stat?c=problem_statement&pm=2274&rd=5009
// However, we ignore the concept of "bombs" -- basically walking through a wall
// costs a certain penalty which figures into the objective function (total path length).




#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct node
{
   int xpos;
   int ypos;
   int cost;
   vector<pair<int,int> > path;
     
   node(int x, int y, int d)
      {
         xpos = x;
         ypos = y;
         cost = d;  
      }

};


// override the comparison operator for nodes so we construct a min-heap
bool operator<(const node &leftNode, const node &rightNode) {
 if (leftNode.cost != rightNode.cost) return leftNode.cost < rightNode.cost;
 return false;
}

bool operator<=(const node &leftNode, const node &rightNode) {
 if (leftNode.cost != rightNode.cost) return leftNode.cost < rightNode.cost;
 if (leftNode.cost == rightNode.cost) return true;
 return false;
}


////////////////

void SiftUp(node list[], int N)   // for a min-heap
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


void SiftDown(node list[], int arraySize, int index)  // for a min-heap
{
   // assumes the top of the heap is out-of-order, sifts down until is in-order
   int position = index;      // ordinal position in heap
   int child = 2*index;         // ordinal position in heap
   while (true)
   {
      child = 2*position;
      if (child >= arraySize) { break;}
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
   }
}



//////////////////////////////////

node FindNode(int x, int y, vector<node> nodes)
{
   node badnode(-1,-1,-1);
   for (vector<node>::iterator it = nodes.begin() + 1; it != nodes.end(); ++it)
   {
      if (it->xpos == x && it->ypos == y)
      {
         return *it;
      }
   }
   
   return badnode;
}

////////////////////////////////
int FindIndex(int x, int y, vector<node> nodeheap)     // this could be made faster by stopping when node cost exceeds target.cost
{
   int index = 1;
   for (vector<node>::iterator it = nodeheap.begin() + 1; it != nodeheap.end(); ++it)
   {
      if (it->xpos == x && it->ypos == y)
      {
         return index;
      }
      ++index;
   }
 
   return 0;  // not found
}
//////////////////////////
bool TestHeap(vector<node>& nodeheap)        // for debugging, test if heap still valid
{
   for (int i = 2; i < nodeheap.size(); ++i)
   {
      if (nodeheap.at(i).cost < nodeheap.at(i/2).cost) { return false;}
      if (2*i < nodeheap.size() &&  nodeheap.at(i).cost > nodeheap.at(2*i).cost) {return false;}
   }
   return true;
}


/////////////////////
void AddToPath(node& target, int x, int y)
{
   pair<int, int> thispair(x, y);
   target.path.push_back(thispair);
}



////////////

void  ProcessNeighbor(node thisnode, int x, int y, vector<node>& nodeheap, vector<vector<int> >& maze)
{
   node nextnode = FindNode(x,y,nodeheap);
   if (nextnode.cost != -1 &&
       y < maze.size() &&
       x < (maze.at(0)).size() &&
       x >= 0 && y >= 0)
      {
         int probe_cost = thisnode.cost + (maze.at(y)).at(x); 
         if (probe_cost < nextnode.cost)
         {
            int idx = FindIndex(nextnode.xpos, nextnode.ypos, nodeheap);
            if (idx != 0)
            {
               nodeheap.at(idx).cost = probe_cost;
               nodeheap.at(idx).path = thisnode.path;
               AddToPath(nodeheap.at(idx), x, y);
               if (nodeheap.at(idx).cost < nodeheap.at(idx / 2).cost)
               {
                  SiftUp(&nodeheap[0], idx);
               }
               else if (2*idx < nodeheap.size() && nodeheap.at(idx).cost > nodeheap.at(2*idx).cost)
               {
                  SiftDown(&nodeheap[0], nodeheap.size(), idx);
               }
            }
         }              
      }
}

///////////////////

const int MAXCOST = 10000;

int Dijkstra(vector<vector<int> > maze, int startx, int starty, int endx, int endy, int bombs)
{

   // initialize nodes
   vector<node> nodeheap;
   int mincost = MAXCOST;
   node startnode(startx, starty, 0);
   AddToPath(startnode, startx, starty);
   
   nodeheap.push_back(node(-1,-1,-1));  // dummy node so our heap starts at index 1
   nodeheap.push_back(startnode);
   for (int i = 0; i < maze.size(); ++i)  // loop over rows
   {
      for (int j = 0; j < (maze.at(0)).size(); ++j) // assume all rows have same width
      {
         if (i != starty || j != startx)
         {
            node thisnode(j, i, MAXCOST);
            nodeheap.push_back(thisnode);
         }
      } 
   }


   // construct the heap
   for (int pos = 1; pos < nodeheap.size(); ++pos)
   {
      SiftUp(&nodeheap[0], pos);
   }


   while (nodeheap.size() > 1)      // recall the lowest element is a dummy filler
   {
      node currnode = nodeheap.at(1);  // must be lowest-cost node
      swap(nodeheap.at(1), nodeheap.at(nodeheap.size() - 1));
      nodeheap.pop_back();       // we're done with this node, remove it
      SiftDown(&nodeheap[0], nodeheap.size(), 1);  // reorder the heap

      if (currnode.cost == MAXCOST)
      {
         cout << "No exit!" << endl;
         break;            // no good vertices left
      }
      if (currnode.xpos == endx && currnode.ypos == endy)
      {
         cout << "Success! " << currnode.path.size() << " steps." << endl;
         mincost = currnode.cost;

         // draw the solution path
         cout <<  maze.size() << " " << (maze.at(0)).size() << endl;
         for (int i = 0; i < maze.size(); ++i)
         {
            for (int j = 0; j < (maze.at(0)).size(); ++j)
            {
               int found = 0;
               for (vector<pair<int,int> >::iterator it = currnode.path.begin();
                    it != currnode.path.end(); ++it)
               {
                  if (j == it->first  && i == it->second) {found = 1;}
               }
               if (found == 1)
               {
                  cout << "X ";
               }
               else
               {
                  cout << (maze.at(i)).at(j) << " ";
               }
            }
            cout << endl;
         }
   

       


         break;   // we reached the exit
      }

      ProcessNeighbor(currnode, currnode.xpos, currnode.ypos - 1, nodeheap, maze); // top
      ProcessNeighbor(currnode, currnode.xpos - 1, currnode.ypos, nodeheap, maze); // left
      ProcessNeighbor(currnode, currnode.xpos + 1, currnode.ypos, nodeheap, maze); // right
      ProcessNeighbor(currnode, currnode.xpos, currnode.ypos + 1, nodeheap, maze); // bottom
   }

   return mincost;

}






int main()
{
   // read in the maze structure into an array

   // ifstream infile("maze1.txt", fstream::in);
   // int startx = 5;
   // int starty = 0;
   // int endx = 2;
   // int endy = 3;
   // int bombs = 1;


   // ifstream infile("maze2.txt", fstream::in);
   // int startx = 0;
   // int starty = 0;
   // int endx = 10;
   // int endy = 0;
   // int bombs = 1;

   ifstream infile("maze3.txt", fstream::in);
   int startx = 8;
   int starty = 0;
   int endx = 0;
   int endy = 46;
   int bombs = 1;
  

   vector<vector<int> > maze;
   vector<int> row;
   char inchar;

   const int WALL_PENALTY = 3;
   while(infile.good())
   {
      inchar = 'x';
      infile >> inchar;
      switch (inchar)
      {
      case 'x':
         break;
      case ',':
         maze.push_back(row);
         row.clear();
         break;         
      case '.':
         row.push_back(1);
         break;
         
      case '#':
         row.push_back(WALL_PENALTY);
         break;

      default:
         row.push_back(1);    
         break;
      }
   }

   
   // cout <<  maze.size() << " " << (maze.at(0)).size() << endl;
   // for (int i = 0; i < maze.size(); ++i)
   // {
   //    for (int j = 0; j < (maze.at(0)).size(); ++j)
   //    {
   //       cout << (maze.at(i)).at(j) << " ";
   //    }
   //    cout << endl;
   // }
   

    

   // Call the Dijkstra algorithm
     cout << "Minimum path is " << Dijkstra(maze, startx, starty, endx, endy, bombs) << endl;



   return 1;
}






// Problem Statement
    	
// Bomb Man is trapped inside a maze shaped like a grid. You must help him find the exit as fast as possible. The maze will be given as a String[] where each element corresponds to a row in the grid and each character in an element corresponds to a cell in that row. '#' marks a wall, '.' an empty cell, 'B' the start position of Bomb Man and 'E' the exit. Below is an example of a maze in this format, given as a String[]:

// {".....B.",
//  ".#####.",
//  ".#...#.",
//  ".#E#.#.",
//  ".###.#.",
//  "......."}
// In each time unit, Bomb Man can move one cell up, down, left or right. Thus, in the maze above, he can reach the exit in 14 time units by just walking.

// To be able to reach the exit quicker, Bomb Man is in possession of a number of bombs, each of which can blow a hole in a wall and thus open up new passages. Instead of moving in any of the four cardinal directions, Bomb Man can (if he has bombs left) blow a hole in a wall located in any of the four neighboring squares. The bomb will go off in the time unit after he has placed the bomb, creating an empty cell that Bomb Man can enter in the time unit after that. That is, if he places a bomb in time unit t, he can enter the cell earliest in time unit t+2. In the maze above, Bomb Man can then reach the exit in 8 time units by first walking left, placing a bomb, waiting for the bomb to explode, and then walking down, down, left, left and down.

// Create a class BombMan containing the method shortestPath which takes a String[] maze, containing the maze in the format described above, and an int bombs, the number of bombs in Bomb Man's possession. The method should return an int, the least number of time units required for Bomb Man to reach the exit. If it's not possible for Bomb Man to reach the exit, return -1 (see example 1).
