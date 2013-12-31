// Given a sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string.
// Example: find “ball” in [“at”, “”, “”, “”, “ball”, “”, “”, “car”, “”, “”, “dad”, “”, “”] will return 4
// Example: find “ballcar” in [“at”, “”, “”, “”, “”, “ball”, “car”, “”, “”, “dad”, “”, “”] will return -1


#include<iostream>

using namespace std;


int FindWord(string list[], int N, string target)
{
   int low = 0;
   int high = N - 1;
   while (low <= high)
   {
      int middle = (low + high) / 2;
      while (list[middle].length() == 0 && middle < high)        // we have a null string
      {
         middle += 1;
      }
      if (list[middle].length() == 0)    // we still have a null string
      {
         middle = (low + high) / 2;
         while (middle > low && list[middle].length() == 0)    
         {
            middle -= 1;
         }
      }
      if (list[middle].length() == 0) { return -1;}  // give up
      if (list[middle] == target) { return middle;}    // now we must have a non-null string
      if (list[middle] < target)
      {
         low = middle + 1;
      }
      else
      {
         high = middle - 1;
      }
   }

   return -1;
}


int main()
{
   string input[10] = {"one", "", "", "two", "", "", "", "who", "", ""};
   string target;

   cout << "Search for which word?" << endl;
   cin >> target;

   cout << FindWord(input, 10, target);

   return 1;
}
