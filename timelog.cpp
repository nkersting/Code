// Find places in a time log where the user log-ins exceed LIMIT/60 sec




#include <iostream>

using namespace std;


void FindViolations(int nums[], int N, int limit, int interval)
{
   int prev = 0;
   int count = 0;
   for (int i = 0; i < N; ++i)
   {
      while (nums[i] - nums[prev] > interval)
      {
         ++prev;
         --count;
      }
      if (++count >= limit)
      {
         cout << prev << " " << i << endl;
      }

   }


}


int main()
{
   int times[20] = {1,2,3,4,20,30,31,32,33,61,100,101,102,103,141,142,193,194,195,210};

   FindViolations(times, 20, 5, 60);

   return 0;
}
