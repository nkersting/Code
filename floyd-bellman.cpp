

#include <iostream>


using namespace std;

const int X = 10000;

void Floyd(int M[][5])
{
   for (int k = 0; k < 5; ++k)
   {
      for (int i = 0; i < 5; ++i)
      {
         for (int j = 0; j < 5; ++j)
         {
            if (M[i][j] > M[i][k] + M[k][j])
            {
               M[i][j] = M[i][k] + M[k][j];
            }
         }
      }
   }
}

void Bellman(int M[][5], int d[])
{
   for (int k = 0; k < 5; ++k)
   {
      for (int i = 0; i < 5; ++i)
      {
         for (int j = 0; j < 5; ++j)
         {
            if (d[i] > d[j] + M[j][i])
            {
               d[i] = d[j] + M[j][i];
            }
         }
      }
   }
}


void PrintM(int weights[][5])
{
  for (int i = 0; i < 5; ++i)
   {
      for (int j = 0; j < 5; ++j)
      {
         if (weights[i][j] == X)
         {
            cout <<  "X ";
         }
         else
         {
            cout << weights[i][j] << " ";
         }
      }
      cout << endl;
   }
}


int main()
{
   int weights[5][5] = { {X, 1, 3, 5, 9},
                         {X, X, 1, X, X},
                         {X, X, X, 2, X},
                         {X, X, X, X, 3},
                         {X, X, X, X, X} };

 
   PrintM(weights);
   cout << endl << endl;


   int distances[5] = {0, X, X, X, X};
   Bellman(weights, distances);
   for (int i = 0; i < 5; ++i)
   {
      cout << distances[i] << " ";
   }
   cout << endl << endl;
   
   Floyd(weights);
   PrintM(weights);


}
