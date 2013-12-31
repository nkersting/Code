// Given a numeric phone keypad, how many N digit numbers are reachable 
// from a given starting number using only "knight's moves" ?


#include<iostream>
#include<queue>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<cstdlib>

using namespace std;


struct node
{
   int x; 
   int curr_digits;
   node(int ax, int curr)
      {
         x = ax;
         curr_digits = curr;
      }   
};



////////////////////////////////

int MaxNum(map<int, vector<int> > adj_list, int start, int num_digits)
{
   int num_sols = 0;

   node start_node = node(start,0);
   queue<node> q;
   q.push(start_node);
  
   while(q.empty() == false){
      node top = q.front();
      q.pop();

      if (top.curr_digits == num_digits)
      {
         num_sols++;
      }
      else
      {
         for (vector<int>::iterator iter = adj_list[top.x].begin(); iter != adj_list[top.x].end(); ++iter)
         {
            q.push(node(*iter, top.curr_digits + 1));
         }
      }
   }
    
   return num_sols;   
}
////////////////////
int RecurseSearch(map<int, vector<int> > adj_list, int currpos, int num_digits, int currdigits)
{
   if (currdigits == num_digits)
   {
      return 1;
   }
   int currcount = 0;
   for (vector<int>::iterator iter = adj_list[currpos].begin(); iter != adj_list[currpos].end(); ++iter)
   {
      currcount += RecurseSearch(adj_list, *iter, num_digits, currdigits + 1);
   }

   return currcount;

}

/////////////////////////
vector<int> TableSearch(map<int, vector<int> > adj_list, vector<int> last_results, int num_digits)
{
   if (num_digits == 0)
   {
      return last_results;
   }

   vector<int> these_results;   
   for (int i = 0; i <= 9; ++i){
      int count = 0;
      for (vector<int>::iterator iter = adj_list[i].begin(); iter != adj_list[i].end(); ++iter)
      {
         count += last_results.at(*iter);
      }
      these_results.push_back(count);
   }
   return TableSearch(adj_list, these_results, num_digits - 1);

}

//////////////////
int main(){


   int start = 1;
   int num_digits = 12;

   map<int,vector<int> > adj_list;
   for (int i = 0; i <= 9; ++i)
   {
      vector<int> connections;
      if (i == 1)
      {
         connections.push_back(6);
         connections.push_back(8);
      }
      else if (i == 2)
      {
         connections.push_back(7);
         connections.push_back(9);
      }
      else if (i == 3)
      {
         connections.push_back(4);
         connections.push_back(8);
      }
      else if (i == 4)
      {
         connections.push_back(3);
         connections.push_back(9);
         connections.push_back(0);
      }
      else if (i == 5)
      {
         continue;
      }
      else if (i == 6)
      {
         connections.push_back(7);
         connections.push_back(0);
         connections.push_back(1);
      }
      else if (i == 7)
      {
         connections.push_back(2);
         connections.push_back(6);
      }
      else if (i == 8)
      {
         connections.push_back(1);
         connections.push_back(3);
      }
      else if (i == 9)
      {
         connections.push_back(2);
         connections.push_back(4);
      }
      else if (i == 0)
      {
         connections.push_back(4);
         connections.push_back(6);
      }
         adj_list[i] = connections;
   } 

   cout << "Num solutions in BFS is " << MaxNum(adj_list, start, num_digits) << endl;

 
   vector<int> starting_vals(10,1);
   vector<int> solutions = TableSearch(adj_list, starting_vals, num_digits);
   cout << "Num solutions in table recursion is " << endl;
   for (vector<int>::iterator it = solutions.begin(); it != solutions.end(); ++it)
   {
      cout << *it << endl;
   }

   cout << "Num solutions in naive recursion is " << RecurseSearch(adj_list, start, num_digits, 0) << endl;

 
   return 1;
}


