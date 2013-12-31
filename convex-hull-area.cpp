// You are analyzing the behavior of an organism with peculiar growth patterns. Initially, you have placed the organisms at various spots in a rectangular tray. To precisely measure where each organism is, you have overlaid the tray with a Cartesian coordinate system.
// The initial state will be described in int[]s xs and ys. Organism i is located at coordinates (xs[i],ys[i]). You have noticed that if organisms are present at (x1,y1) and (x2,y2) then shortly afterward, there will also be an organism at ( (x1+x2)/2 , (y1+y2)/2 ). There is no truncation in this operation, so organisms can occur at non-integral coordinates. As far as you are concerned, the organisms are each points, and the process has been allowed to run until completion.


#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<set>

using namespace std;

const double EPSILON = 0.0001;

double SCross(pair<double,double> v1, pair<double,double> v2)
{
   return (v1.first * v2.second - v1.second*v2.first);
}

double SAngle(pair<double,double> v1, pair<double,double> v2)
{
   double vmag1 = v1.first*v1.first + v1.second*v1.second;
   double vmag2 = v2.first*v2.first + v2.second*v2.second;
   return SCross(v1,v2)/sqrt(vmag1*vmag2);
}

bool operator<(pair<double,double> p1, pair<double,double> p2) 
{
   return p1.first < p2.first;
}

bool operator==(pair<double,double>& p1, pair<double,double>& p2) 
{
   return abs(p1.first - p2.first) < EPSILON && abs(p1.second - p2.second) < EPSILON;
}


pair<double, double> operator-(const pair<double,double>& p1, const pair<double,double>& p2) 
{
   return pair<double, double>(p1.first - p2.first, p1.second - p2.second);
}


// negative cross-prod method
vector<pair<double,double> > ConvexHull(vector<pair<double,double> > points)
{
   vector<pair<double,double> > convex_hull;


   // find initial point
   sort(points.begin(), points.end());
   convex_hull.push_back(points.at(0));


   while(convex_hull.size() == 1 || !(convex_hull.back() == convex_hull.at(0)) )
   {
      
      for (vector<pair<double, double> >::iterator it = points.begin(); it != points.end(); ++it)
      {
         if (*it == convex_hull.back()) {continue;}


         // try to look for a point with no negative cross product with remaining points   
         pair<double, double> v1 = pair<double, double> (it->first - convex_hull.back().first,
                                                         it->second - convex_hull.back().second);
         bool failed = false;
         for (vector<pair<double, double> >::iterator it2 = points.begin(); it2 != points.end(); ++it2)
         {
            if (*it2 == convex_hull.back() || *it2 == *it) {continue;}
          

            pair<double, double> v2 = pair<double, double> (it2->first - convex_hull.back().first,
                                                            it2->second - convex_hull.back().second);
            if (SAngle(v2,v1) < 0)
            {
               failed = true;
               break;
            }
         }
         if (failed == false)
         {
            convex_hull.push_back(*it);
            break;
         }
      }
   }


   convex_hull.pop_back();  // the last point is the same as the first
   

   for (int i = 0; i < convex_hull.size(); ++i)
   {
      cout << convex_hull.at(i).first << " " << convex_hull.at(i).second << endl;
   }

   return convex_hull;
}


double ComputeArea(const vector<pair<double, double> >& points)
{
   pair<double, double> base = points.at(0);
   pair<double, double> head;
   pair<double, double> tail;

   double area = 0;
   for (int i = 2; i < points.size(); ++i)
   {
      head = points.at(i - 1);
      tail = points.at(i);
      area += 0.5*SCross(tail - base, head - base);
   }

   return area;
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


  
   vector<pair<double,double> > input;
   for (int i = 0; i < N; ++i)
   {
      input.push_back(pair<double,double>(xvals[i],yvals[i]));
   }

   vector<pair<double,double> > output = ConvexHull(input);

   cout << "Area is " << ComputeArea(output) << endl;

   return 0;
}



