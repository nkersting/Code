// Your chess club is playing a match against an opposing chess club. Each club enters N players into the match, and each player plays one game against a player from the other team. Each game that is won is worth 2 points, and each game that is drawn is worth 1 point. Your goal is to score as many points as possible.

// Your secret agents have determined the skill of every member of the opposing team, and of course you know the skill of every member of your own team. You can use this information to decide which opposing player will play against each of your players in order to maximize your score. Assume that the player with the higher skill in a game will always win, and if the players have the same skill then they will draw.


#include <iostream>
#include <limits>
#include <vector>

using namespace std;


struct Node
{
   vector<Node*> links;
   vector<int> weights;
};


// returns maximum capacity
int BipartiteMatch(Node* source, Node* sink) 
{
   int max = 0;


   return max;
}


// Loop : This has yet to be coded
// 1. Form bipartite network from the 0-weight edges
// 2. Check matching -- if perfect then finished
// 3. Find vertex cover and reprocess 0-edges
// 4. goto 1

// initial processing to reduce weights on edges (optional)
void ProcessList(vector<Node*>& list)
{
   for (vector<Node*>::iterator it = list.begin(); it != list.end(); ++it)
   {
      int min = numeric_limits<int>::max();
      for (vector<int>::iterator wit = (*it)->weights.begin(); wit != (*it)->weights.end(); ++wit)
      {
         if (*wit < min) { min = *wit; }
      }
      for (vector<int>::iterator wit = (*it)->weights.begin(); wit != (*it)->weights.end(); ++wit)
      {
         *wit -= min;
      }
   }

}



int main()
{
   int N = 3;
   int team1[3] = {10,5,1};
   int team2[3] = {10,5,1};

   vector<Node*> Alist;
   vector<Node*> Blist;
   for (int i = 0; i < N; ++i)
   {
      Node* a = new Node();
      Alist.push_back(a);
      for (int j = 0; j < N; ++j)
      {
         Node *b = new Node();
         Blist.push_back(b);
         a->links.push_back(b);
         a->weights.push_back(team1[i] > team2[j] ? 0 : team1[i] == team2[j] ? 1 : 2);  // here converting to min-cost problem
      }
   }


   //  ProcessList(Alist);
//   ProcessList(Blist);


   // copy the 0-nodes into a new network for bipartite matching
   vector<Node*> Alist0;
   vector<Node*> Blist0;
   for (int i = 0; i < N; ++i)
   {
      Blist0.push_back(new Node());
   }

   for (int i = 0; i < N; ++i)
   {
      Node* a = new Node();
      Alist0.push_back(a);
      for (int j = 0; j < Alist.at(i)->weights.size(); ++j)
      {
         if (Alist.at(i)->weights.at(j) == 0)
         {
            a->links.push_back(Blist0.at(j));
            a->weights.push_back(1);
         }
      }
   }
   


   // add supersource
   Node* ssource = new Node();
   for (int i = 0; i < N; ++i)
   {
      ssource->links.push_back(Alist0.at(i));
      ssource->weights.push_back(1);
   }

   // add supersink
   Node* ssink = new Node();
   for (int i = 0; i < N; ++i)
   {
      Blist0.at(i)->links.push_back(ssink);
      Blist0.at(i)->weights.push_back(1);
   }

   cout << BipartiteMatch(ssource, ssink) << endl; 


   return 0;
}



// 0)	
    	
// {5, 8}
// {7, 3}
// Returns: 4
// By playing 5 against 3 and 8 against 7, you can win both games.
// 1)	
    	
// {7, 3}
// {5, 8}
// Returns: 2
// This is the reverse of the previous case. By playing 7 against 5 and 3 against 8, you can win one game.
// 2)	
    	
// {10, 5, 1}
// {10, 5, 1}
// Returns: 4
// If you play matching pairs you will draw all three games for 3 points. However, playing 10-5, 5-1 and 1-10 gives you two wins and a loss, for 4 points.
// 3)	
    	
// {1, 10, 7, 4}
// {15, 3, 8, 7}
// Returns: 5
