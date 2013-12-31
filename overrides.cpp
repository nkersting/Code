

#include<iostream>

using namespace std;


class XYPoint
{
public: int xcoord;
public:  int ycoord;

public: XYPoint(int x, int y){
      xcoord = x;
      ycoord = y;
   };


public: XYPoint& operator+=(const XYPoint& p1)
      {
         xcoord += p1.xcoord;
         ycoord += p1.ycoord;
         return *this;
      };

public: XYPoint& operator++()
      {
         xcoord++;
         ycoord++;
         return *this;
      }

public: XYPoint operator++(int)
      {
         XYPoint tmp(*this);
         operator++();
         return tmp;
      }

};

inline XYPoint operator+(XYPoint lhs, const XYPoint& rhs)
{
   lhs += rhs;
   return lhs;
}



int main()
{
   XYPoint p1(1,1);
   XYPoint p2(-1,3);

   XYPoint p3 = p1 + p2;
   cout << "p3 is " << p3.xcoord << " " << p3.ycoord << endl;


   p1 += p2;
   cout << "p1 is " << p1.xcoord << " " << p1.ycoord << endl;


   ++p2;
   cout << "p2 is " << p2.xcoord << " " << p2.ycoord << endl;


   p2++;
   cout << "p2 is " << p2.xcoord << " " << p2.ycoord << endl;


   p2++;
   cout << "p2 is " << p2.xcoord << " " << p2.ycoord << endl;

   ++p2++++++++++++++++++++++++++++++++;
   cout << "p2 is " << p2.xcoord << " " << p2.ycoord << endl;


   return 0;
}
