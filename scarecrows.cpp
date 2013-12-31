
// Given the Given the coordinates of possible locations for the scarecrows and the maximum number of scarecrows the farmer can afford to buy, calculate the largest area that can be guarded by these scarecrows. The farmer's field is a rectangular area, and all locations given will be inside this area.coordinates of possible locations for the scarecrows and the maximum number of scarecrows the farmer can afford to buy, calculate the largest area that can be guarded by these scarecrows. The farmer's field is a rectangular area, and all locations given will be inside this area.


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

double ComputeArea(const vector<pair<double, double> >& points)  // assumes CCW order
{
   pair<double, double> base = points.at(0);
   pair<double, double> head;
   pair<double, double> tail;

   double area = 0;
   for (int i = 2; i < points.size(); ++i)
   {
      head = points.at(i - 1);
      tail = points.at(i);
      area += 0.5*SCross(head - base, tail - base);
   }

   return area;
}                 


// using at most "limit" of the points 
double ComputeMaxArea(const vector<pair<double, double> >& points, int limit) 
{
   cout << "Points on convex hull: " << points.size() << "    Limit is " << limit << endl;
   if (limit < points.size() - 2) 
   {
      cout << "Large number of combinations expected ... aborting" << endl;
      return 0;
   }

   if (limit >= points.size())
   {
      return ComputeArea(points);
   }
   else if (limit == points.size() - 1)
   {
      double max = 0;
      double temp = 0;
      vector<pair<double, double> > reduced_points;
      for (int i = 0; i < points.size(); ++i)
      {       
         reduced_points.clear();
         for (int j = 0; j < points.size(); ++j)
         {
            if (i != j)
            {
               reduced_points.push_back(points.at(j));
               temp = ComputeArea(reduced_points);
               if (temp > max)
               {
                  max = temp;
               }
            }           
         }
      }
      return max;
   }
   else
   {
      // assume exactly two points missing from hull
      double max = 0;
      double temp = 0;
      vector<pair<double, double> > reduced_points;
      for (int i = 0; i < points.size(); ++i)
      {
         for (int k = 0; k < points.size(); ++k)
         {
            reduced_points.clear();
            for (int j = 0; j < points.size(); ++j)
            {
               if (i != j &&  k != j && i != k)
               {
                  reduced_points.push_back(points.at(j));
                  temp = ComputeArea(reduced_points);
                  if (temp > max)
                  {
                     max = temp;
                  }
               }
            }
         }
      }
      return max;
   }
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


   // int N = 7;
   // double xvals[7] ={2,1,6,5,3,7,9};
   // double yvals[7] = {2,5,1,5,7,6,4};
   // int limit = 4;

   // int N = 8;
   // double xvals[8] = {183,229,723,510,395,936,447,328};
   // double yvals[8] = {1000,823,0,412,786,446,312,286};
   // int limit = 15;

   // int N = 15;
   // double xvals[15] = {33,36,26,8,12,8,28,19,8,37,9,22,31,30,25};
   // double yvals[15] = {12,8,6,16,27,7,31,33,35,22,22,36,29,22,32};
   // int limit = 8;

  
   int N = 40;
   double xvals[40] = {327,196,744,91,709,38,944,300,927,715,835,874,958,667,748,511,377,956,184,956,
 809,925,12,45,184,180,169,374,914,398,954,875,286,422,76,315,497,209,512,938};
   double yvals[40] = {913,843,73,213,903,444,444,905,352,54,194,207,373,57,105,959,932,480,843,424,
 140,661,578,616,851,132,135,936,676,23,578,737,74,959,724,924,955,854,958,376};
   int limit = 25;


   vector<pair<double,double> > input;
   for (int i = 0; i < N; ++i)
   {
      input.push_back(pair<double,double>(xvals[i],yvals[i]));
   }

   vector<pair<double,double> > output = Graham(input);


   // for (vector<pair<double, double> >::iterator it = output.begin(); it != output.end(); ++it)
   // {
   //    cout << it->first << " " << it->second << endl;
   // }

   cout << endl << "Area is " << ComputeMaxArea(output, limit);


   return 0;
}

