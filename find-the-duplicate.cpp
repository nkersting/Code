// Given a sorted list containing (2^20 + 1) twenty-bit integers, how can you find one that appears at least twice?


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


///////////////////////////
void PrintListWithOneDuplicate()
{
  for (int i = 0; i <= 1<<20; ++i){
      cout << i << endl;
      if (i == 1000) { cout << i << endl;}   // the duplicate entry is 1000
   }
}
/////////////////////////
int search(vector<int>& numlist, int low, int high)
{
   if (high < low) { return numlist.at(low); }
   if (low == high) {
      return numlist.at(low);
   }
   if (numlist.at((low+high)/2) < (low + high)/2){
      return search(numlist, low, (low + high)/2);
   }
   return search(numlist, (low + high)/2 + 1, high); 
}
/////////////////////////


int main()
{
   ifstream myfile;
   myfile.open ("one-duplicate.txt");  

   vector<int> nums;
   string wrd = "";

   if (myfile.is_open())
   {
      while ( myfile.good() )
      {
         
         myfile >> wrd;
         nums.push_back(atoi(wrd.c_str()));
      
      }

      myfile.close();
   }


   int result = search(nums, 0, nums.size() - 1);

   cout << "The first duplicate found is " << result;


   return 1;
}
