
// You need to write a function to climb n steps you can climb either 1 step at a time or 2 steps a time, write a function to return number of ways to climb a ladder with n step.


// These turn out to be Fibonacci numbers!

#include <iostream>
using namespace std;


int ClimbNSteps(int N)
{
   if (N == 1 || N == 0) 
   {
      return 1;
   }
   if (N < 0)
   {
      return 0;
   }

   return ClimbNSteps(N-1) + ClimbNSteps(N-2);

}



int ClimbNIterative(int N)
{
   int* ans = new int[N];
  
   ans[0] = 1;
   ans[1] = 1;
 
   for (int i = 2; i <= N; ++i)
   {
      ans[i] = ans[i-1] + ans[i-2];
   }

   return ans[N];

}


int main()
{
   cout << ClimbNSteps(1) << endl;
 cout << ClimbNSteps(2) << endl;
   cout << ClimbNSteps(3) << endl;
   cout << ClimbNSteps(4) << endl;
   cout << ClimbNSteps(5) << endl;
   cout << ClimbNSteps(6) << endl;
   cout << ClimbNSteps(0) << endl;
   cout << ClimbNSteps(-1) << endl;
   cout << ClimbNSteps(10) << endl;
  cout << ClimbNSteps(20) << endl;



  cout << ClimbNIterative(0) << endl;
  cout << ClimbNIterative(1) << endl;
  cout << ClimbNIterative(2) << endl;
  cout << ClimbNIterative(3) << endl;
  cout << ClimbNIterative(4) << endl;
  cout << ClimbNIterative(5) << endl;
  cout << ClimbNIterative(20) << endl;
  cout << ClimbNIterative(41) << endl;
  cout << ClimbNIterative(42) << endl;
  cout << ClimbNIterative(43) << endl;
  cout << ClimbNIterative(44) << endl;
  cout << ClimbNIterative(45) << endl;

   return 0;
}
