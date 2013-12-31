// Divide-and-conquer method to find closest pair of points in a region



#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


struct Point
{
   double x,y;
   Point(int xx, int yy)
      {
         x = xx;
         y = yy;
      }
};

double Dist(Point p1, Point p2)
{
   return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                         (p1.y - p2.y)*(p1.y - p2.y)  );
}


const int MAXDIST = 10000;
double DirectCompare(Point P[], int numpoints, Point& p1, Point& p2)
{
   double mindist = MAXDIST;
   for (int i = 0; i < numpoints; ++i)
   {
      for (int j = i + 1; j < numpoints; ++j)
      {
         double d = Dist(P[i], P[j]);
         if (d < mindist)
         {
            mindist = d;
         }
      }
   }
   return mindist;
}

bool PointSort(Point p1, Point p2)
{
   return p1.y < p2.y;
}


double MinInStrip(vector<Point> points, double d, Point& p1, Point& p2)
{
   // first sort the list
   sort(points.begin(), points.end(), PointSort);

   double min = MAXDIST;
   for (int i = 0; i < points.size(); ++i)
   {
      for (int j = i + 1; j < points.size() && abs(points.at(i).y - points.at(j).y) <= d; ++j)
      {
         if (Dist(points.at(i), points.at(j)) < min)
         {
            min = Dist(points.at(i), points.at(j));
            p1 = points.at(i);
            p2 = points.at(j);
         }
      }
   }
   return min;
}

double ClosestDist(Point P[], int numpoints, Point& p1, Point& p2)
{
   if (numpoints <= 3)
   {
      return DirectCompare(P, numpoints, p1, p2);
   }

   int mid = numpoints/2;
   Point midpoint = P[mid];

   double d1 = ClosestDist(P, mid, p1, p2);
   double d2 = ClosestDist(P + mid, numpoints - mid, p1, p2);

   double mind = min(d1,d2);

   // form the strip
   vector<Point> stripPoints;
   for (int i = 0; i < numpoints; ++i)
   {
      if (abs(P[i].x - P[mid].x) <= mind)
      {
         stripPoints.push_back(P[i]);
      }
   }

   
   return min(mind, MinInStrip(stripPoints, mind, p1, p2));

}



int main()
{
   Point points[5] = {Point(0,0), Point(5,5), Point(4,6), Point(10,10), Point(3,7)};


   Point p1(0,0);
   Point p2(0,0);
   cout << "Closest distance is " << ClosestDist(points, 5, p1, p2) << endl;
   cout << "Between points (" << p1.x << ", " << p1.y << ") and (" << p2.x << ", " << p2.y << ")" << endl;

   return 0;
}
