

#include <iostream>
#include <vector>

using namespace std;

void Merge(int s[], int low, int middle, int high)
{
   int i;
   vector<int> buffer1, buffer2;
   for (i = middle; i >= low; i--)
   {
      buffer1.push_back(s[i]);
   }
   for (i = high; i >= middle + 1; --i)
   {
      buffer2.push_back(s[i]);
   }

   i = low;
  while (!buffer1.empty() && !buffer2.empty())
  {
	if (buffer1.back() <= buffer2.back())
	{
	  s[i++] = buffer1.back();
	  buffer1.pop_back();
	}
	else
	{
	  s[i++] = buffer2.back();
	  buffer2.pop_back();
	}
  }

  while (!buffer1.empty())
  {
	s[i++] = buffer1.back();
	buffer1.pop_back();
  }
  while (!buffer2.empty())
  {
	s[i++] = buffer2.back();
	buffer2.pop_back();
  }

}



void MergeSort(int list[], int low, int high)
{
   if (low >= high) { return;}
   int middle = (low + high) / 2;

   MergeSort(list, low, middle);
   MergeSort(list, middle + 1, high);
   Merge(list, low, middle, high);
}

int Test(int& x)
{
   x = 1;
   int y = 2;

   return x = y;
//   return x;

}

int main()
{
   int x = 0;
   cout << "Testing: x(1) = y(2) : " << Test(x) << " now x is " << x << endl << endl;
   cout << "Now x is " << x << endl << endl;
   
   int vals[10] = {2,1,0,-2,7,10, 44,-100,9,0};


   MergeSort(vals, 0, 9);

   for (int i = 0; i < 10; ++i)
   {  
      cout << vals[i] << " ";
   }
   cout << endl;
}
