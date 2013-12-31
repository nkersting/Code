// TOPCODER Escape Graphing Problem:http://community.topcoder.com/stat?c=problem_statement&pm=1170&rd=4371 


#include<iostream>
#include<queue>
#include<vector>


using namespace std;


struct node
{
   int X, Y;
   int curr_hits;

   node(int x, int y, int hits)
      {
         X = x;
         Y = y;
         curr_hits = hits;
      }
};

//////////////////////
int HitVal(int x, int y, vector<pair<pair<int, int>, pair<int, int> > >& forbidden,
  vector<pair<pair<int, int>, pair<int, int> > >& hitsquares )
{
  
   for (vector<pair<pair<int, int>, pair<int, int> > >::iterator it = forbidden.begin(); it != forbidden.end(); ++it)
   {
      if (it->first.first <= x && it->second.first >= x &&
          it->first.second <= y && it->second.second >= y ){
         return 2;
      }
   }

   for (vector<pair<pair<int, int>, pair<int, int> > >::iterator it = hitsquares.begin(); it != hitsquares.end(); ++it)
   {
      if (it->first.first <= x && it->second.first >= x &&
          it->first.second <= y && it->second.second >= y ){
         return 1;
      }
   }


   return 0;
}

////////////////////////////////

int minHits(int boardsize, int hits_max, vector<pair<pair<int,int>, pair<int,int> > >& forbidden,
            vector<pair<pair<int, int>, pair<int, int> > >& hitsquares)
{
   bool visited[boardsize][boardsize];
 
   for (int hits_req = 0; hits_req < hits_max; ++hits_req){


      for (int i = 0; i < boardsize; ++i){
         for (int j = 0; j < boardsize; ++j){
            visited[i][j] = false;
         }
      }
   

      node start(0,0,0);
      queue<node> q;
      q.push(start);

      while(q.empty() == false){
         node top = q.front();
         q.pop();

         if (visited[top.X][top.Y]) continue;   // make sure didn't already hit this square
         visited[top.X][top.Y] = true;
         
         if (top.X == boardsize - 1 && top.Y == boardsize - 1)
         {
            return top.curr_hits;  // guaranteed to be the minimum
         }

         for (int xDelta = -1; xDelta <= 1; ++xDelta){
            for (int yDelta = -1; yDelta <= 1; ++yDelta){
               if (xDelta*yDelta == 0)         // forbid diagonal moves
               {
                  int new_X = top.X + xDelta;
                  int new_Y = top.Y + yDelta;
                  int this_hits = HitVal(new_X, new_Y, forbidden, hitsquares);
                  if (new_X >= 0 && new_X < boardsize &&
                      new_Y >= 0 && new_Y < boardsize && 
                      this_hits <= 1 && this_hits + top.curr_hits <= hits_req
                     )
                  {
                     q.push(node(new_X, new_Y, top.curr_hits + this_hits));
                  }
               }
            }
         }

      }

   }

   return -1;   // no path found
}


//////////////////
int main(){



   vector<pair<pair<int, int>, pair<int, int> > > forbidden;
   vector<pair<pair<int, int>, pair<int, int> > > hitsquares;

/*
   int hits_max = 200; // replace this with a binary search
   int boardsize = 20;

   int forbiddenvals[4] = {5,5,10,10};
   int hitvals[4] = {0,0,20,20};

   for (int i = 0; i < 4; i += 4){                                
      pair<int, int> f1(forbiddenvals[i], forbiddenvals[i+1]);
      pair<int, int> f2(forbiddenvals[i+2], forbiddenvals[i+3]);
      pair<pair<int, int>, pair<int, int> > f3(f1, f2);
      forbidden.push_back(f3);
   }

   for (int i = 0; i < 4; i += 4){
      pair<int, int> f1(hitvals[i], hitvals[i+1]);
      pair<int, int> f2(hitvals[i+2], hitvals[i+3]);
      pair<pair<int, int>, pair<int, int> > f3(f1, f2);
      hitsquares.push_back(f3);
   }
*/



   int hits_max = 2000; // replace this with a binary search
   int boardsize = 500;

   int forbiddenvals[8] = {0,251,249,500,251,0,500,249};
   int hitvals[8] = {0,0,250,250,250,250,500,500}; 

   for (int i = 0; i < 8; i += 4){                                
      pair<int, int> f1(forbiddenvals[i], forbiddenvals[i+1]);
      pair<int, int> f2(forbiddenvals[i+2], forbiddenvals[i+3]);
      pair<pair<int, int>, pair<int, int> > f3(f1, f2);
      forbidden.push_back(f3);
   }

   for (int i = 0; i < 8; i += 4){
      pair<int, int> f1(hitvals[i], hitvals[i+1]);
      pair<int, int> f2(hitvals[i+2], hitvals[i+3]);
      pair<pair<int, int>, pair<int, int> > f3(f1, f2);
      hitsquares.push_back(f3);
   }



   cout << "Minimum is " << minHits(boardsize, hits_max, forbidden, hitsquares) << endl;
 



   




   return 1;
}


/*
Problem Statement
    	You are playing a video game that involves escaping from a dangerous area. Within the area there are DEADLY regions you can't enter, HARMFUL regions that take 1 life for every step you make in them, and NORMAL regions that don't affect you in any way. You will start from (0,0) and have to make it to (500,500) using only Up, Left, Right, and Down steps. The map will be given as a String[] deadly listing the DEADLY regions and a String[] harmful listing the HARMFUL regions. The elements in each of these parameters will be formatted as follows:

Input format(quotes for clarity): "X1 Y1 X2 Y2" where

(X1,Y1) is one corner of the region and

(X2,Y2) is the other corner of the region

The corners of the region are inclusive bounds (i.e. (4,1) and (2,2) include x-values between 4 and 2 inclusive and y-values between 1 and 2 inclusive). All unspecified regions are considered NORMAL. If regions overlap for a particular square, then whichever region is worst takes effect (e.g. DEADLY+HARMFUL = DEADLY, HARMFUL+NORMAL = HARMFUL, HARMFUL+HARMFUL = HARMFUL, DEADLY+NORMAL=DEADLY).

Damage taken at each step occurs based on the destination square and not on the starting square (e.g. if the square (500,500) is HARMFUL you WILL take a point of damage stepping onto it; if the square (0,0) is HARMFUL you WON'T take a point of damage stepping off of it; this works analogously for DEADLY squares). 

Return the least amount of life you will have to lose in order to reach the destination. Return -1 if there is no path to the destination. Your character is not allowed to leave the map (i.e. have X or Y less than 0 or greater than 500). 

 
Definition
    	
Class:	Escape
Method:	lowest
Parameters:	String[], String[]
Returns:	int
Method signature:	int lowest(String[] harmful, String[] deadly)
(be sure your method is public)
    
 
Notes
-	If two harmful regions overlap, the area where they overlap is exactly the same as non-overlapping harmful regions (i.e. the effect is NOT cumulative, and the overlapping region still takes exactly 1 life)
 
Constraints
-	deadly will contain between 0 and 50 elements inclusive
-	harmful will contain between 0 and 50 elements inclusive
-	Each element of deadly and harmful will be of the form (quotes for clarity): "X1 Y1 X2 Y2"

where X1,Y1,X2, and Y2 are integers between 0 and 500 inclusive and contain no leading zeros
-	Each element of deadly and harfmul will contain no leading, trailing or extra whitespace
 
Examples
0)	
    	
{}
{}
Returns: 0
There are no DEADLY or HARMFUL regions.
1)	
    	
{"500 0 0 500"}
{"0 0 0 0"}
Returns: 1000
(0,0) is DEADLY but that doesn't affect our path since we never step onto it (only from it). The rest of the map is NORMAL.
2)	
    	
{"0 0 250 250","250 250 500 500"}
{"0 251 249 500","251 0 500 249"}
Returns: 1000
Just enough space to get around the DEADLY regions.
*/
