// Computes convex hull of a collection of points using Graham's Scan


#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

class Point
{
public:
   double x,y;
   pair<double,double> point;
   double angle;
   Point(double xc, double yc)
      {
         x = xc;
         y = yc;
         point.first = x;
         point.second = y;
      }
};


bool PointCompare(const pair<double,double>& p1, const pair<double,double>& p2)
{
   return (p1.second != p2.second ? p1.second < p2.second : p1.first < p2.first);
}

bool AngleCompare(const  Point& p1, const Point& p2)
{
   return p1.angle != p2.angle ? p1.angle < p2.angle : p1.x < p2.x;
}

double SCross(pair<double,double> v1, pair<double,double> v2)
{
   return (v1.first * v2.second - v1.second*v2.first);
}


double SDot(pair<double,double> v1, pair<double,double> v2)
{
   return (v1.first * v2.first + v1.second*v2.second);
}

pair<double,double> operator-(const pair<double,double>& p1, const pair<double,double>& p2)
{
   return pair<double,double>(p1.first - p2.first, p1.second - p2.second);
}

bool operator==(const pair<double,double>& p1, const pair<double,double>& p2)
{
   return p1.first == p2.first && p1.second == p2.second;
}

bool operator!=(const pair<double,double>& p1, const pair<double,double>& p2)
{
   return !(p1 == p2);
}


double SAngle(pair<double,double> v1, pair<double,double> v2)
{
   double vmag1 = v1.first*v1.first + v1.second*v1.second;
   double vmag2 = v2.first*v2.first + v2.second*v2.second;
   if (vmag1 == 0 || vmag2 == 0) return 0;
   double sinang = SCross(v1,v2)/sqrt(vmag1*vmag2);
   
   if (SDot(v1,v2) < 0)
   {
      return 3.14159 - asin(sinang);
   }
   else
   {
      return asin(sinang);
   }
}

vector<pair<double,double> > Graham(vector<pair<double,double> > points)
{
   vector<pair<double,double> > hull;
   vector<Point> sPoints;
   for (vector<pair<double, double> >::iterator it = points.begin(); it != points.end(); ++it)
   {
      sPoints.push_back(Point(it->first, it->second));
   }

   sort(points.begin(), points.end(), PointCompare);


   // give each Point an angle w.r.t. the first point on the hull and x-axis
   for (vector<Point>::iterator it = sPoints.begin(); it != sPoints.end(); ++it)
   {
      it->angle = SAngle(pair<double,double>(1.0,0.0), it->point  - points.at(0));
   }
   sort(sPoints.begin(), sPoints.end(), AngleCompare);


   // Graham's Scan requires you plug in the first three points
   hull.push_back(sPoints.at(0).point);      
   hull.push_back(sPoints.at(1).point);      
   hull.push_back(sPoints.at(2).point);  

   for (vector<Point>::iterator it = sPoints.begin() + 3; it != sPoints.end(); ++it)
   {
      while (SCross(hull.back() - hull.at(hull.size() - 2), it->point - hull.back()) < 0)
      {
         hull.pop_back();
      }
      hull.push_back(it->point);
   }

   return hull;
}


int main()
{
   // int N = 5;        // square with point in middle
   // double xvals[5] = {0,1,0.5,0,1};
   // double yvals[5] = {0,1,0.5,1,0};


   // int N = 6;               // equilateral triangle with points in middle
   // double xvals[6] = {0, 1, 0.5, 0.2, 0.5, 0.7};
   // double yvals[6] = {0, 0, 0.5*sqrt(3), 0.01, 0.3, 0.1};


   int N = 8;               // hexagon with two points in middle
   double xvals[8] = {1, 1.5, 0.5, 1.5, 2, 1.5, 0.5, 0};
   double yvals[8] = {1, 1, 0, 0, 0.5*sqrt(3), sqrt(3), sqrt(3), 0.5*sqrt(3)};


   // int N = 4;                 // line
   // double xvals[4] = {0, 0, 0, 0};
   // double yvals[4] = {.1, .2, .3, .4};

   // int N = 7;
   // double xvals[7] ={2,1,6,5,3,7,9};
   // double yvals[7] = {2,5,1,5,7,6,4};

  
   vector<pair<double,double> > input;
   for (int i = 0; i < N; ++i)
   {
      input.push_back(pair<double,double>(xvals[i],yvals[i]));
   }

   vector<pair<double,double> > output = Graham(input);


   for (vector<pair<double, double> >::iterator it = output.begin(); it != output.end(); ++it)
   {
      cout << it->first << " " << it->second << endl;
   }


   return 0;
}
