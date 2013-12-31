// Given a (decimal - e.g. 3.72) number that is passed in as a string, print the binary representation. If the number can not be represented accurately in binary, print “ERROR”

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;




void PrintBinary(double x)
{
   int left = floor(x);
   vector<int> digits;
   while (left > 0)
   {
      digits.push_back(left & 1);
      left = left >> 1;
   }

   double decimals = x - floor(x);
   vector<int> subdigits;
   while (decimals < 1<<10)   // arbitrary 10-digit precision
   {
      decimals = decimals*2;
      int test = floor(decimals);
      subdigits.push_back(test % 2);
   }

   vector<string> final;
   for (vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it)
   {
      final.push_back(*it == 1 ? "1" : "0");
   }
   final.push_back(".");

   for (vector<int>::iterator it = subdigits.begin(); it != subdigits.end(); ++it)
   {
      final.push_back(*it == 1 ? "1" : "0");
   }


   for (vector<string>::iterator it = final.begin(); it != final.end(); ++it)
   {
      cout << *it;
   }
}


int main()
{
   PrintBinary(3.71);


   return 0;
}
