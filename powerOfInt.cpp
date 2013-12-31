

#include <iostream>
#include <string.h>

using namespace std;


void Power(int n, int p, int digits[])
{
   int temp[100];

   digits[0] = 1;
   for (int i = 0; i < p; ++i)
   {
      for (int k = 0; k < 100; ++k)
      {
         temp[k] = 0;
      }

      for (int j = 0; j < 100; ++j)
      {
         int x = digits[j]*n;
         temp[j] += x % 10;
         temp[j+1] += x / 10;
      }

      for (int k = 0; k < 100; ++k)
      {
         digits[k] = 0;
      }

      for (int j = 0; j < 100; ++j)
      {
         digits[j] += temp[j] % 10;
         digits[j+1] += temp[j] / 10;
      }
   }
}


int main()
{
   int input[100];
//   memset(input, 0, 100);
   
   for (int i = 99; i >= 0; --i)
   {
      input[i] = 0;
   }


   Power(7,77,input);

   for (int i = 99; i >= 0; --i)
   {
      cout << input[i];
   }


   return 0;
}
