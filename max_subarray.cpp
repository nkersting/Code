// find the maximum sum of elements over all sub-intervals of a given set




#include<iostream>
#include<vector>

using namespace std;




vector<int> MaxOverlapping(int vals[], int maxsize, int middle)
{
   pair<int, int> lowpair;
   pair<int, int> highpair;
   vector<int> best;

   int maxidx = middle;
   int maxsum = -1000;
   int tempsum = 0;
   for (int i = middle; i >= 0; --i)
   {
      tempsum += vals[i];
      if (tempsum >= maxsum)
      {
         maxsum = tempsum;
         maxidx = i;
      }
   }
   lowpair.first = maxidx;
   lowpair.second = maxsum;


   maxidx = middle + 1;
   maxsum = -1000;
   tempsum = 0;
   for (int i = middle + 1; i < maxsize; ++i)
   {
      tempsum += vals[i];
      if (tempsum >= maxsum)
      {
         maxsum = tempsum;
         maxidx = i;
      }
   }
   highpair.first = maxidx;
   highpair.second = maxsum;


   best.push_back(lowpair.second + highpair.second);
   best.push_back(lowpair.first);
   best.push_back(highpair.first);
   return best;
}


vector<int> MaxInterval(int vals[], int maxsize, int low, int high)       // O(n log n)
{
   if (low == high)
   {
      vector<int> sol;
      sol.push_back(vals[low]);
      sol.push_back(low);
      sol.push_back(low);
      return sol;
   }
   int middle = (high + low) / 2;
   
   
   vector<int> val1 = MaxInterval(vals, maxsize, low, middle);
   vector<int> val2 = MaxInterval(vals, maxsize, middle + 1, high);
   vector<int> val3 = MaxOverlapping(vals, maxsize, middle);
   
   if (val1.at(0) >= val2.at(0) && val1.at(0) >= val3.at(0)) {return val1;}
   else if (val2.at(0) >= val1.at(0) && val2.at(0) >= val3.at(0)) { return val2;}
   else { return val3;}
}


/////////////////////
vector<int> FastSubarray(int vals[], int maxsize)          // Note this runs in O(n)
{
   int index1 = 0;
   int index2 = 0;
   int sum = vals[0];
   int residual = 0;

   for (int i = 1; i < maxsize; ++i)
   {
      if (vals[i] > sum + vals[i])
      {
         index1 = i;
         index2 = i;
         sum = vals[i];
         residual = 0;
      }
      else if (residual + vals[i] > 0)
      {
         index2 = i;
         sum += vals[i] + residual;
         residual = 0;
      }
      else
      {
         residual += vals[i];
      }
   }

   vector<int> solution;
   solution.push_back(index1);
   solution.push_back(index2);
   solution.push_back(sum);


   return solution;
}
////////////////////


int main()
{

//   int vals[10] = {22, 32, -11, -54, 21, 99, -100, 21, 0, 3};
   //  int vals[10] = {-1, 2, 2, 2, 2, -1, -2, -3, -4, -5};
//   int vals[10] = {-1, -3, 2, 2, 2, -1, -2, -3, -4, -5};
   int vals[10] = {-1, -3, 2, 2, 2, -1, 0, 30, -4, -5};
   int nsize = 10;


   vector<int> solution = MaxInterval(vals, nsize, 0, nsize - 1);

   for (int i = 0; i < nsize; ++i)
   {
      cout << vals[i] << " ";
   }
   cout << endl;

   cout << "Maximum interval sum is " << solution.at(0) << endl;
   cout << "Between indices " << solution.at(1) << " and " << solution.at(2) << endl;

   vector<int> solution2 = FastSubarray(vals, nsize);
   cout << endl << endl << "Fast solution gives " << solution2.at(0) << " " 
        << solution2.at(1) << " " << solution2.at(2) << endl;

   return 1;
}



