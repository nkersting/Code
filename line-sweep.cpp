// Given a list of two-dimensional rectangles, compute the area of their union.Given a list of two-dimensional rectangles, compute the area of their union.




#include<iostream>
#include<vector>


using namespace std;


int Area(int p[][4], int N)
{
   int area = 0;
   int minx = 1000;
   int maxx = -1000;
   for (int i = 0; i < N; ++i)
   {
      if (p[i][0] < minx)
      {
         minx = p[i][0];
      }
      if (p[i][2] > maxx)
      {
         maxx = p[i][2];
      }
   }


   for (int xsweep = minx; xsweep < maxx; ++xsweep)
   {
      int miny = 1000;
      int maxy = -1000;
      for (int i = 0; i < N; ++i)
      {
         if (p[i][0] <= xsweep && p[i][2] > xsweep)
         {
            if (p[i][1] < miny) { miny = p[i][1];}  
            if (p[i][3] > maxy) { maxy = p[i][3];}  
         }         
      }
    
      if (miny != 1000 && maxy != -1000)
      {
         area += maxy - miny;
      }
   }


   return area;
}



int main()
{
   int N = 3;
   int points[N][4];
   points[0] = {1,3,5,6};
   points[1] = {3,1,7,5};
   points[2] = {4,4,9,7};   //3 overlapping, area = 35


   // int N = 3;
   // int points[N][4];
   // points[0] = {1,3,3,6};
   // points[1] = {4,1,5,5};
   // points[2] = {7,4,9,7};   //nonoverlapping, area = 16

   cout << Area(points, N);


}
