// recursively compute a^n  for any (a,n)


#include<iostream>
#include <cmath>


using namespace std;

int IntPower(double a, int n)
{
   if (n == 0) {return 1;}
   if (n == 1) {return a;}

   return (n % 2 == 0  ? 1 : a ) * IntPower(a,n/2) * IntPower(a, n/2);
}


int main()
{
   double a;
   double n;
   cout << "Enter a: ";
   cin >> a;
   cout << endl << "Enter n: ";
   cin >> n;

   if (n < 0)
   {
      cout << endl << 1.0/IntPower(a,floor(abs(n)))*pow(a,abs(n)-floor((abs(n))));
   }
   else
   {

      cout << endl << IntPower(a,floor(n))*pow(a,n-floor(n));
   }

   return 1;
}
