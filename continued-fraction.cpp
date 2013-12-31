// Compute continued fraction expansion of a decimal number


#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;



void FindHeadAndTail(int num, int den, int& head, int& tail)
{
   head = 0;
   while (num >= den)
   {
      head++;
      num -= den;
   }
   tail = num;
}



vector<int> ContinuedFraction(double x)
{
   vector<int> solution;
   int exp = 10;
   while (exp*x - floor(exp*x) != 0)
   {
      exp *= 10;
   }

   int den = x*exp;
   int num = exp;

   int head = 0;
   int tail = 1;
   int temp = 0;

   cout << x << " " << exp << " " << x*exp << " " << num << " " << den << endl << endl;
   while (tail != 0)
   {
      FindHeadAndTail(num, den, head, tail);
      solution.push_back(head);
      num = den;
      den = tail;
   }

   return solution;

}


int main()
{
   // cout << "Max double is " << numeric_limits<double>::max() << endl;
   // cout << "Min double is " << numeric_limits<double>::min() << endl;
   // cout << "Max float is " << numeric_limits<float>::max() << endl;
   // cout << "Min float is " << numeric_limits<float>::min() << endl;



   // double x = 1;
   // for (int i = 0; i < 30; ++i)
   // {
   //    x /= 2;
   //    cout << x << endl;
   // }

   double x;
   cout << "Enter a decimal number less than 1: ";
   cin >> x;

   vector<int> expansion = ContinuedFraction(x);

   for (vector<int>::iterator it = expansion.begin(); it != expansion.end(); ++it)
   {
      cout << *it << " ";
   }




   return 0;
}
