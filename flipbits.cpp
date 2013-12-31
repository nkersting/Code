//Write a function that flips the bits inside a byte 

#include<iostream>

using namespace std;


int FlipBits(int n)
{
  return n^255;
}



int main()
{
   cout << FlipBits(11);

   return 0;
}


