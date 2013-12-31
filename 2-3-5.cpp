// There are some data represented by(x,y,z). Now we want to find the Kth least data. We say (x1, y1, z1) > (x2, y2, z2) when value(x1, y1, z1) > value(x2, y2, z2) where value(x,y,z) = (2^x)*(3^y)*(5^z). Now we can not get it by calculating value(x,y,z) or through other indirect calculations as lg(value(x,y,z)). How to solve it?



#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct Triple
{
   int a;
   int b;
   int c;

   Triple(int x, int y, int z)
      {
         a = x;
         b = y;
         c = z;
      }
};


vector<int> AllTriples(int N, vector<Triple>& factors)
{
   vector<int> solutions;

   queue<int> q2;
   queue<int> q3;
   queue<int> q5;

   queue<Triple > tq2;
   queue<Triple > tq3;
   queue<Triple > tq5;

   q2.push(2);
   q3.push(3);
   q5.push(5);
   
   tq2.push(Triple (1,0,0));
   tq3.push(Triple (0,1,0));
   tq5.push(Triple (0,0,1));

   solutions.push_back(1);
   factors.push_back(Triple (0,0,0));
   int x;
   Triple y(0,0,0);
   while (solutions.back() < N)
   {
      if (q2.front() <= q3.front() && q2.front() <= q5.front())
      {
         x = q2.front();
         y = tq2.front();
         factors.push_back(y);
         solutions.push_back(x);
         tq2.pop();
         q2.pop();
         q2.push(x * 2);
         q3.push(x * 3);
         q5.push(x * 5);
         tq2.push(Triple(y.a + 1, y.b, y.c));
         tq3.push(Triple(y.a, y.b + 1, y.c));
         tq5.push(Triple(y.a, y.b, y.c + 1));
      }
      else if (q3.front() <= q2.front() && q3.front() <= q5.front())
      {
         x = q3.front();
         y = tq3.front();
         factors.push_back(y);
         solutions.push_back(x);
         tq3.pop();
         q3.pop();
         q3.push(x * 3);
         q5.push(x * 5);         
         tq3.push(Triple(y.a, y.b + 1, y.c));
         tq5.push(Triple(y.a, y.b, y.c + 1));
      }
      else
      {
         x = q5.front();
         y = tq5.front();
         factors.push_back(y);
         solutions.push_back(x);
         tq5.pop();
         q5.pop();
         q5.push(x * 5);
         tq5.push(Triple(y.a, y.b, y.c + 1));
      }
   }

   return solutions;
}

bool operator<(const Triple& t1, const Triple& t2)
{
   return  t1.a != t2.a ? t1.a < t2.a
      : t1.b != t2.b ? t1.b < t2.b
      : t1.c < t2.c;
}


int main()
{
   Triple input[10] = {Triple(1,1,1), Triple(1,1,2), Triple(2,1,1),  Triple(1,2,1), Triple(3,0,1),
                       Triple(1,3,0), Triple(0,0,1), Triple(3,1,1),  Triple(1,3,1), Triple(2,1,2)};


   vector<Triple> factors;
   vector<int> sols = AllTriples(1000, factors);
   

   for (int i = 0; i < sols.size(); ++i)
   {
      cout << sols.at(i) << " " << factors.at(i).a << " " << factors.at(i).b 
           << " " << factors.at(i).c << endl;
   } 


   map<Triple, int> tripleToInt;
   for (int i = 0; i < factors.size(); ++i)
   {
      tripleToInt[factors.at(i)] = i;
   }


   int positions[500];
   for (int i = 0; i < 500; ++i)
   {
      positions[i] = 0;
   }
   for (int i = 0; i < 10; ++i)
   {
      positions[tripleToInt[input[i]]]++;
   }
   for (int i = 0; i < 100; ++i)
   {
      if (positions[i] > 0)
      {
         cout << factors.at(i).a << " " << factors.at(i).b << " " << factors.at(i).c << endl;
      }
   }


   return 0;
}
