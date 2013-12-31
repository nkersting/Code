// simple counting sort


#include <iostream>


using namespace std;




void CountSort(int list[], int N)
{
   int buckets[10];
   int temp[N];

     for (int j = 0; j < 10; ++j)
   {
      buckets[j] = 0;
   }


   for (int i = 0; i < N; ++i)
   {
      buckets[list[i]]++;
      temp[i] = 0;
   }

   for (int j = 1; j < 10; ++j)
   {
      buckets[j] += buckets[j-1];
   }


   
   for (int i = N-1; i >= 0; --i)
   {
      temp[--buckets[list[i]]] = list[i];
   }

   for (int j = 0; j < N; ++j)
   {
      list[j] = temp[j];
   }


}




int main()
{
   int nums[20] = {1,1,2,0,5,1,9,3,8,5,3,8,7,6,4,0,0,4,6,6};


   CountSort(nums, 20);

    for (int j = 0; j < 20; ++j)
   {
      cout <<  nums[j] << " ";
   }

   return 0;
}
