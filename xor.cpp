


#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{

   int M = 1000000; 


   for (int N = 1; N < 1000; N += 100)
   {

      int array1[N];
      int array2[N];

      for (int i = 0; i < N; i++)
      {
         array1[i] = 1;
         array2[i] = 2;
      }


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
      int XORtime =  time1f - time1s;

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
      int TEMPtime = time2f - time2s;

      clock_t time3s = clock();
      for (int j = 0; j < M; j++)
      {
         for (int i = 0; i < N; i++)
         {
            array1[i]  = array1[i] + array2[i];
            array2[i]  = array1[i] - array2[i];
            array1[i]  = array1[i] - array2[i];
         }
      }
      clock_t time3f = clock();
      int PLUStime =  time3f - time3s;

      cout << N << " " << TEMPtime << " " << XORtime << " " << PLUStime << endl;
   }



  
  return 1;

   
    
}
