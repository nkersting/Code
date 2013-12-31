
#include <iostream>

using namespace std;



int BSearchWithBreak(int list[], int N, int x)
{
  int low = 0;
  int high = N -1;

  while (low <= high)
  {
     int middle = (low + high) / 2;
     if (list[middle] == x) {return middle;}

     if (list[low] < list[middle])  // normal interval
     {
        if (list[middle] < x)
        {
           low = middle + 1;
        }
        else if (list[low] <= x)
        {
           high = middle - 1;
        }
        else
	  {
             low = middle + 1;
	  }
     }
     else if (list[low] == list[middle])
     {
        low += 1;
     }
     else
     {
        if (list[middle] > x)
        {
           high = middle - 1;
        }
        else if (list[high] >= x)
        {
           low = middle + 1;
        }
        else
        {
           high = middle - 1;
        }

     }

  }
  return -1;
}


int main()
{
 int input[10] = {5,6,7,8,9,0,1,2,3,4};
//   int input[10] = {0,1,2,3,4,5,6,7,8,9};
   //  int input[10] = {1,1,2,1,1,1,1,1,1,1};

   int num;
   cout << "Enter number to search for:";
   cin >> num;

   cout << BSearchWithBreak(input, 10, num) << endl;

   return 0;
}
