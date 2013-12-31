// Write a method to generate the nth Fibonacci number.

#include<iostream>
#include<vector>

using namespace std;


int Fibonacci(int n)
{
   if (n == 0) { return 0;}
   if (n == 1) { return 1;}
   return (Fibonacci(n-1) + Fibonacci(n-2));
}


int Fibonacci2(int n)
{
   vector<int> F;
   F.push_back(0);
   F.push_back(1);
   for (int i = 2; i <= n; ++i)
   {
      F.push_back(F.at(i-1) + F.at(i-2));
   }
   return F.back();
}

int main()
{
   for (int i = 0; i < 10; ++i)
   {
      cout << Fibonacci(i) << endl;
   }
   cout << endl;

   for (int i = 0; i < 10; ++i)
   {
      cout << Fibonacci2(i) << endl;
   }
   cout << endl;

   return 1;

}


