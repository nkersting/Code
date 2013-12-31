// recursively compute a^n  for integers  n >= 0



#include<iostream>


using namespace std;

int Power(int a, int n)
{
   if (n == 0) {return 1;}
   if (n == 1) {return a;}

   return (n % 2 == 0  ? 1 : a ) * Power(a,n/2) * Power(a, n/2);

}


int main()
{
   int a;
   int n;
   cout << "Enter a: ";
   cin >> a;
   cout << endl << "Enter n: ";
   cin >> n;

   cout << endl << Power(a,n);

   return 1;
}
