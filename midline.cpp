// find line midway between two points

#include<iostream>
#include<cmath>

using namespace std;

const double epsilon = 0.0001;

pair<double, double> LineParams(double x1, double x2, double y1, double y2)
{
   if (abs(x2 - x1) <= epsilon)
   {
      return pair<double,double> (0, (y1 + y2) / 2);
   }
   if (abs(y2 - y1) <= epsilon)
   {
      return pair<double, double> ((x1 + x2)/ 2 + epsilon, (x1 + x2) / 2 + epsilon);   // interpret m  = b as vertical line
   }
   double m = (y2 - y1) / (x2 - x1);
   return pair<double, double> (-1/m, (y1 + y2)/2 + (1/m)*(x1+x2)/2);
}

int main()
{
//   pair<double, double> line = LineParams(0,1,1,0);
   pair<double, double> line = LineParams(1,0.5,0,1);

   cout << line.first << " " << line.second << endl;  // slope and intercept
   return 0;
}
