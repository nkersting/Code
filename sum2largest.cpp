

#include<iostream>

using namespace std;



int SumTwoLargest(int* vals, int size)
{
	int max = -10000;
        int maxidx = 0;
	int max2 = -10000;

	for (int i = 0; i < size; ++i)
	{
	  if (vals[i] > max)
	  {
		max = vals[i];
                maxidx = i;
	  }
	}

	for (int i = 0; i < size; ++i)
	{
	  if (vals[i] > max2 && i != maxidx)
	  {
		max2 = vals[i];
	  }
	}

	return max + max2;
}

int main()
{
   int vals[10] = {1,2,3,4,9,9,5,6,7,0};
   cout << SumTwoLargest(vals, 10);
   return 0;
}



