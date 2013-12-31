// Solve the Towers of Hanoi with 3 stacks
// Iterative solution: if all the discs start on A, then perform the sequence:
// 1. legal move between A and C
// 2. legal move between A and B
// 3. legal move between B and C
// 4. Repeat 1-3 until stack is totally on C

// Recursive solution: n = 1 is trivial
// To move N discs from A to C:
// 1. move N-1 discs to B
// 2. move the Nth disc from A to C
// 3. move N-1 discs from B to C

#include<iostream>
#include<stack>
#include<vector>


using namespace std;



int Hanoi(stack<int> s[])
{

   int N = s[0].size();
   int count = 0;
   int fakemoves = 0;
   int pos1 = 0;
   int pos2 = 2;
   int small = 0;
   int big = 2;
   int incr = (N % 2) == 0 ? 2 : 1;
   while(s[2].size() < N )    // need to move all discs onto third stack
   {
      count++;
  
      pos1 = (count % 3) == 0 ? 1 : 0;  // 001001001 ...
      pos2 = ((count + incr) % 3) == 0 ? 1 : 2; // 21221221... if N odd,  1221221221 if even

      if (s[pos1].empty() && s[pos2].empty()) { fakemoves++; continue;}   
      if (s[pos1].empty()) { small = pos2; big = pos1;}
      else if (s[pos2].empty()) { small = pos1; big = pos2;}
      else
      {
         small = s[pos1].top() < s[pos2].top() ? pos1 : pos2;
         big = small == pos1 ? pos2 : pos1;
      }
      s[big].push(s[small].top());
      s[small].pop();      
      
   }
   return count - fakemoves;
}



class DStack
{
private: vector<int> mStack;

public: void Push(int val)
      {
         mStack.push_back(val);
      }

public: void Pop()
      {
         mStack.pop_back();
      }

public: int Top()
      {
         return mStack.back();
      }
   
public: int At(int i)
      {
         return mStack.at(i);
      }

public: int Size()
      {
         return mStack.size();
      }
};



void StackMoveN(DStack s[], int source, int target, int N, int& count)
{
   if (N == 1)
   {
      int topdisc = s[source].Top();
      s[source].Pop();
      s[target].Push(topdisc);
      count++;


      cout << source << " " << target << "        ";

      for (int i = 0; i < 3; ++i)
      {
         for (int j = 0; j < s[i].Size(); ++j)
         {
            cout << s[i].At(j);
         }
         cout << "  ";
      }
      cout << endl;


      return;
   }
   int middle = 3 - source - target;   // i.e. choose the one remaining stack
   StackMoveN(s, source, middle, N - 1, count);
   StackMoveN(s, source, target, 1, count);
   StackMoveN(s, middle, target, N - 1, count);
}


int main()
{

   int N;  // number of discs 

   cout << "How many discs? ";
   cin >> N;


   // iterative solution

   stack<int> stacks[3];
   for (int i = N; i > 0; --i)
   {
      stacks[0].push(i);
   }

   cout <<    Hanoi(stacks) << " moves required." << endl;   // should be 2^N - 1



   // recursive solution below

   DStack dstacks[3];
   for (int i = N; i > 0; --i)
   {
      dstacks[0].Push(i);
   }

   int count = 0;
   StackMoveN(dstacks,0,2,N,count);
   cout << count << " moves required." << endl;
   return 1;
}



      

