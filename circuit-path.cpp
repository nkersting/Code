// TOPCODER Escape Graphing Problem:http://community.topcoder.com/stat?c=problem_statement&pm=1593&rd=4494


#include<iostream>
#include<queue>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<cstdlib>

using namespace std;

struct edgenode
{

   int y;           // adjacency
   int weight;
    edgenode(int neighbor, int w)
      {
         y = neighbor;
         weight = w;
      }
};


struct node
{
   int x; 
   int curr_cost;
   node(int ax, int acurr_cost)
      {
         x = ax;
         curr_cost = acurr_cost;
      }
   
};

//////////////////////////
vector<int>::iterator find(vector<int> vec, int element)
{
   for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
   {
      if (*iter == element) return iter;
   }
   return vec.end();
}


////////////////////////////////

int MaxCost(map<int, vector<edgenode> > adjacency_list, int node_count)
{
   int max_cost = 0;  
   vector<int> start_nodes;
   for (int i = 0; i < node_count; ++i)
   {
      int only_out_edges = true;
      for (int j = 0; j < node_count; ++j)
      {
         for (vector<edgenode>::iterator it = adjacency_list[j].begin(); it != adjacency_list[j].end(); ++it)
         {
            if (it->y == i) {only_out_edges = false;}
         }

      }

      if (only_out_edges == true) {start_nodes.push_back(i);}
   }

   while (start_nodes.size() > 0)
   {
      int start_node = start_nodes.back();
      start_nodes.pop_back();
      node start(start_node,0);  
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
         if (adjacency_list.find(top.x) != adjacency_list.end())
         {
            if ((adjacency_list.find(top.x)->second).size() != 0)
            {
               for (vector<edgenode>::iterator it = adjacency_list[top.x].begin(); it != adjacency_list[top.x].end(); ++it)
               {
                  q.push(node(it->y, top.curr_cost + it->weight)); 
               }
            }
         }
       
      }
   }
   return max_cost;   
}


//////////////////
int main(){

//   string connections = "{\"1 2\",\"2\",\"\"}";
//   string weights = "{\"5 3\",\"7\",\"\"}";

//   string connections = "{\"1 2 3 4 5\",\"2 3 4 5\",\"3 4 5\",\"4 5\",\"5\",\"\"}";
//   string weights = "{\"2 2 2 2 2\",\"2 2 2 2\",\"2 2 2\",\"2 2\",\"2\",\"\"}";

//   string connections = "{\"1\",\"2\",\"3\",\"\",\"5\",\"6\",\"7\",\"\"}";
//   string weights =  "{\"2\",\"2\",\"2\",\"\",\"3\",\"3\",\"3\",\"\"}";


//   string connections = "{\"\",\"2 3 5\",\"4 5\",\"5 6\",\"7\",\"7 8\",\"8 9\",\"10\",\"10 11 12\",\"11\",\"12\",\"12\",\"\"}";
//   string weights ="{\"\",\"3 2 9\",\"2 4\",\"6 9\",\"3\",\"1 2\",\"1 2\",\"5\",\"5 6 9\",\"2\",\"5\",\"3\",\"\"}";


   string connections = "{\"\",\"2 3\",\"3 4 5\",\"4 6\",\"5 6\",\"7\",\"5 7\",\"\"}";
   string weights = "{\"\",\"30 50\",\"19 6 40\",\"12 10\",\"35 23\",\"8\",\"11 20\",\"\"}";
         

 
   for (int i = 0; i < connections.length(); ++i)
   {
      if (connections[i] == ',' ||
          connections[i] =='{' ||
          connections[i] == '}') connections[i] = ' ';
   }

   for (int i = 0; i < weights.length(); ++i)
   {
      if (weights[i] == ',' ||
         weights[i] == '{' ||
         weights[i] == '}' ) weights[i] = ' ';
   }
   

   cout << connections << endl;
   cout << weights << endl;



   map<int, vector<edgenode> > adjacency_list; 


   int quote_count = 0;
   stringstream ss(connections);
   stringstream tt(weights);
   while (ss.good())
   {
      string node_input;
      string weight_input;
      ss >> node_input;
      tt >> weight_input;
      if (node_input[0] == '\"' && node_input[node_input.length() - 1] == '\"')
      {
         if (node_input.length() > 2)
         {
            int connection_node = (atoi)(node_input.substr(1,node_input.length() - 2).c_str());
            int connection_weight = (atoi)(weight_input.substr(1,weight_input.length() -2).c_str());
            adjacency_list[quote_count++].push_back(edgenode(connection_node, connection_weight));
         }
         else
         {
            quote_count++;
         }
      }
      else if (node_input[0] == '\"')
      {
         int connection_node = (atoi)(node_input.substr(1,node_input.length() - 1).c_str());
         int connection_weight = (atoi)(weight_input.substr(1,weight_input.length() -1).c_str());
         adjacency_list[quote_count].push_back(edgenode(connection_node, connection_weight));
      }
      else if (node_input[node_input.length() - 1] == '\"')
      {
         int connection_node = (atoi)(node_input.substr(0,node_input.length() - 1).c_str());
         int connection_weight = (atoi)(weight_input.substr(0,weight_input.length() -1).c_str());
         adjacency_list[quote_count++].push_back(edgenode(connection_node, connection_weight));
      }
      else if (node_input.length() > 0)
      {
         int connection_node = (atoi)(node_input.c_str());
         int connection_weight = (atoi)(weight_input.c_str());
         adjacency_list[quote_count].push_back(edgenode(connection_node, connection_weight));
      }

   }

 
   for (int i = 0; i < quote_count; ++i)
   {
      for (vector<edgenode>::iterator iter = adjacency_list[i].begin(); iter != adjacency_list[i].end(); ++iter)
      {
         cout << i << "  (" << iter->y << ", " << iter->weight << ") ";
      }
      cout << endl;
   }

   cout << "Number of nodes = " << quote_count << endl;
   cout << "Max cost is " << MaxCost(adjacency_list, quote_count) << endl;
 



   




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
