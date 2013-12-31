// given a list of time entries for a certain person uploading files to your website, identify
// all intervals where usage goes above 10 uploads / hour



#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<vector>


using namespace std;


pair<int,int> FirstOffending(vector<int> times)
{
   int start = 0;
   int startval = 0;
   int count = 0;
   int interval = 60;  // minutes
   int tolerance = 10;
   int index = 0;
   for (vector<int>::iterator it = times.begin(); it != times.end(); ++it)
   {
      if (*it - startval >= interval)
      {
         if (count >= tolerance)
         {
            return pair<int,int>(start, index);
         }
         start = index;
         startval = *it;
         count = 0;
      }
      index++;
      count++;
   }
   return pair<int,int>(-1,-1);
}

int main()
{
   srand(time(NULL));

   vector<int> times;
   int now = 0;
   for (int i = 0; i < 1000; ++i)
   {
      now += rand() % 10 + 1;
      times.push_back(now);
   }

   pair<int,int> vals = FirstOffending(times);
   cout << "Interval is " << vals.first << " " << vals.second << endl;
   if (vals.first == -1) { cout << "No offenders!"; }
   else
   {
      for (int i = vals.first; i < vals.second; ++i)
      {
         cout << times.at(i) << " "; 
      }
      cout << endl;
   }

}


