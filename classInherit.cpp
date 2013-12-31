

#include<iostream>

using namespace std;



class A
{
public:
   int a;
   private:
   int b;

   friend class E;  // without this, E cannot access the private members/methods of A

public: A(){}
public:  A (int x, int y)
      {
         a = x; 
         b = y;
      }
private: void Area()
      {
         cout << "Area is " <<  3*3 << endl;
      }

};

class B: protected A
{
public:
   int c;

public: B(){}
public:  B (int x, int y):A(x,y)
      {
         c = x;
      }

public: void showA()
      {

         cout << "from within:" <<  a << endl;
      };

};

class C: public B
{
public: C (int x, int y): B(x,y)
      {
         
      }
public: void showB()
      {
         cout << "inside the last class:" << a << endl;
      }
};


class D: protected A
{
public: D(int x, int y): A(x,y)
      {
         
      }
   public: void showD()
      {
         cout << "inside the D class:" << a << endl;
      }

};


class E
{
public:  void Area()
      {
          A tt = A(1,1);
          tt.Area();      
      }

};

   int main()
   {
      A first(1,2);
      B second(3, 4);
      C third(5,6);
      D fourth(9,9);
      E test;
      //   first.Area();
      cout << first.a << endl;
      cout << second.c << endl;
//      cout << second.a << endl;
      second.showA();
      third.showB();

      fourth.showD();
      //  fourth.Area();
      test.Area();
   }
