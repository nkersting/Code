
// Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in place?


#include<iostream>
#include<vector>

using namespace std;

vector<vector<int> >  Rotate(vector<vector<int> > M)
{
   vector<vector<int> > P;
   for (int i = 0; i < M.size(); i++)
   {
      vector<int> this_row;
      for (int j = 0; j < M.size(); j++)
      {
         this_row.push_back(M.at(M.size() - j - 1).at(i));
      }
      P.push_back(this_row);        
   }
   return P;
}



void RotateInPlace(vector<vector<int> >& M)
{
   int N = M.size();
   for (int layer = 0; layer < N / 2; ++layer)
   {
      for (int offset = layer; offset < N - layer - 1; ++offset)
      {
         // reserve top element
         int top = M.at(layer).at(offset);

         // copy left onto top
         M.at(layer).at(offset) = M.at(N - 1 - offset).at(layer);

         // copy bottom onto left
         M.at(N - 1 - offset).at(layer) = M.at(N - layer - 1).at(N - 1 - offset);

         // copy right onto bottom
         M.at(N - layer - 1).at(N - 1 - offset) = M.at(offset).at(N - layer - 1);

         // copy top onto right
         M.at(offset).at(N - layer - 1) = top;

      }
   }
}



int main()
{
   vector<vector<int> > M;
   for (int i = 0; i < 10; ++i)
   {
      vector<int> this_row;
      for (int j = 0; j < 10; ++j)
      {
         this_row.push_back(j);
      }
      M.push_back(this_row);
   }


   for (vector<vector<int> >::iterator it = M.begin(); it != M.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); 
           it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   cout << endl << endl;

   vector<vector<int> > Q = Rotate(M);

   for (vector<vector<int> >::iterator it = Q.begin(); it != Q.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); 
           it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   cout << endl << endl;


   RotateInPlace(M);
   for (vector<vector<int> >::iterator it = M.begin(); it != M.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); 
           it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   cout << endl << endl;


  return 1;
}

