

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <algorithm>


using namespace std;

///////////////////////////////////////////////

int main(int argc, char* argv[]) 
{
   /*  int a = 1;
   int b = 2;

   cout << "(a, b) = " << "(" << a << ", " << b << ")" << endl;

   a = a^b;
   b = a^b;
   a = a^b;


   cout << "(a, b) = " << "(" << a << ", " << b << ")" << endl;
   */


   int N = 1000;
   int array1[N];
   int array2[N];

   int M = 1000000; 

   for (int i = 0; i < N; i++)
   {
      array1[i] = 1;
      array2[i] = 2;
   }


//   cout << "(a, b) = " << "(" << array1[0] << ", " << array2[0] << ")" << endl;

   clock_t time1s = clock();
   for (int j = 0; j < M; j++)
   {
      for (int i = 0; i < N; i++)
      {
         array1[i]  = array1[i] ^ array2[i];
         array2[i]  = array1[i] ^ array2[i];
         array1[i]  = array1[i] ^ array2[i];
      }
   }
   clock_t time1f = clock();
   cout << "XOR time is " << time1f - time1s << endl;

   clock_t time2s = clock();
   for (int j = 0; j < M; j++)
   {
      for (int i = 0; i < N; i++)
      {
         int temp = array2[i];
         array2[i]  = array1[i];
         array1[i]  = temp;
      }
   }
   clock_t time2f = clock();
   cout << "TEMP time is " << time2f - time2s << endl;


//   cout << "(a, b) = " << "(" << array1[0] << ", " << array2[0] << ")" << endl;

   


  return 1;

   
    
}
