// TOPCODER Escape Graphing Problem:http://community.topcoder.com/stat?c=problem_statement&pm=1593&rd=4494


#include<iostream>
#include<queue>
#include<vector>


using namespace std;


struct node
{
   int X;
   int curr_cost;

   node(int x, int cost)
      {
         X = x;
         curr_cost = cost;
      }
};


////////////////////////////////

int MaxCost(int adjacency[][3], int dim)
{
   int max_cost = 0;  
 
 
      node start(0,0);
      queue<node> q;
      q.push(start);

      while(q.empty() == false){
         node top = q.front();
         q.pop();

         if (top.curr_cost > max_cost)
         {
            max_cost = top.curr_cost;
         }
         

         // add a node for each possible edge
         for (int j = 0; j < dim; ++j)
         {
            int this_cost = adjacency[top.X][j];
            if (this_cost != -1 )
            {
               q.push(node(j, top.curr_cost + this_cost));               
            }
         }

      }

   return max_cost;   
}


//////////////////
int main(){

   int adjacency[3][3] = {{-1,5,3},{-1,-1,7},{-1,-1,-1}};
   


   cout << "Max cost is " << MaxCost(adjacency, 3) << endl;
 



   




   return 1;
}


/*

An essential part of circuit design and general system optimization is critical path analysis. On a chip, the critical path represents the longest path any signal would have to travel during execution. In this problem we will be analyzing chip designs to determine their critical path length. The chips in this problem will not contain any cycles, i.e. there exists no path from one component of a chip back to itself.



Given a String[] connects representing the wiring scheme, and a String[] costs representing the cost of each connection, your method will return the size of the most costly path between any 2 components on the chip. In other words, you are to find the longest path in a directed, acyclic graph. Element j of connects will list the components of the chip that can be reached directly from the jth component (0-based). Element j of costs will list the costs of each connection mentioned in the jth element of connects. As mentioned above, the chip will not contain any cyclic paths. For example:
connects = {"1 2",
            "2",
            ""}
costs    = {"5 3",
            "7",
            ""}
In this example, component 0 connects to components 1 and 2 with costs 5 and 3 respectively. Component 1 connects to component 2 with a cost of 7. All connections mentioned are directed. This means a connection from component i to component j does not imply a connection from component j to component i. Since we are looking for the longest path between any 2 components, your method would return 12.
 


*/
