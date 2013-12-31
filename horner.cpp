// Given a list of coefficients for a polynomial in x,
// determine the value at x = 2 using Horner's Method




#include<iostream>

using namespace std;


int Horner(int coeff[], int max, int index, int x)
{
   if (index >= max) { return 0;}

   return coeff[index] + x*Horner(coeff, max, ++index, x);

}


int main()
{
   int coeff[6] = {1,-1,1,-1,1,-1};
   int x = 2;
   int N = 6;
   
   cout << Horner(coeff, N,  0, x);

   return 1;
}
