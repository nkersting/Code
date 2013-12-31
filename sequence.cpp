// Given a Data Structure having first n integers and next n chars. A = i1 i2 i3 … iN c1 c2 c3 … cN.Write an in-place algorithm to rearrange the elements of the array ass A = i1 c1 i2 c2 … 
// in cn

#include <iostream>

using namespace std;

void Rotate(int vals[], int low, int high)
{
   for (int i = high - 1; i >= low; --i)
   {
      vals[i+1] = vals[i];
   }
}


void InPlace(int vals[], int total)
{
   int N = total / 2;
   for (int j = 0; j < N; ++j)
   {
      int temp = vals[N + j];
      Rotate(vals, 2*j + 1, N + j);
      vals[2*j + 1] = temp;
   }
}


int main()
{
   int charinput[10] = {'a','b','c','d','e','f','g','h','i','j'};
   int intinput[10] = {1,2,3,4,5,6,7,8,9,10};

   int input[20];
   for (int j = 0; j < 10; ++j)
   {
      input[j] = intinput[j];
   }
   for (int j = 10; j < 20; ++j)
   {
      input[j] = charinput[j - 10];
   }


   InPlace(input, 20);

   for (int i = 0; i < 20; ++i)
   {
      if (i % 2 == 0)
      {
         cout << input[i] << endl;
      }
      else
      {
         cout << (char)(input[i]) << endl;
      }

   }

   return 0;
}
