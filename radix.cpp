// Radix sort




#include <iostream>
using namespace std;

void Radix(int a[])
{
   // first get the maximum number
   int max = 0;
   for (int i = 0; i < 10; ++i)
   {
      if (a[i] > max)
      {
         max = a[i];
      }
   }

   int exp = 1;
   while (max / exp > 1)
   {
      int buckets[10] = {0,0,0,0,0,0,0,0,0,0};
      int b[10];
      for (int i = 0; i < 10; ++i)
      {
         buckets[(a[i] / exp) % 10]++; 
      }
      for (int i = 1; i < 10; ++i)
      {
         buckets[i] += buckets[i-1]; 
      }
      for (int i = 9; i >= 0; --i)
      {
         b[--buckets[(a[i] / exp) % 10]] = a[i];
      }
      for (int i = 0; i < 10; ++i)
      {
         a[i] = b[i];
      }

   
      exp *= 10;      
   }

     

     return;

}




int main()
{
   int input[10] = {44,3,2,10,35,21,88,54,9,11};

   Radix(input);

   for (int i = 0; i < 10; ++i)
   {
      cout << input[i] << endl;
   }


}
