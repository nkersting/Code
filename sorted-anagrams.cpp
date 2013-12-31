// Write a method to sort an array of strings so that all the anagrams are next to each other.


#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;


struct superstring
{
   string orig;
   string sorted;

   superstring(string input)
      {
         orig = input;
         sort(input.begin(), input.end());
         sorted = input;
      }
};


bool supercompare(superstring s1, superstring s2)
{
  return s1.sorted < s2.sorted;
}


bool supercompare2(string s1, string s2)
{
   sort(s1.begin(), s1.end());
   sort(s2.begin(), s2.end());
   return s1 < s2;
}

void PrintSorted(vector<string> inputs)
{
   vector<superstring> result;
   for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it)
   {
      result.push_back(superstring(*it));
   }

   sort(result.begin(), result.end(), supercompare);

   for (vector<superstring>::iterator it = result.begin(); it != result.end(); it++)
   {
      cout << it-> orig << " " << it->sorted << endl;
   }

}


void PrintSorted2(vector<string> inputs)
{
   sort(inputs.begin(), inputs.end(), supercompare2);

   cout << endl;
   for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); it++)
   {
      cout << *it << endl;
   }

}


int main()
{
   vector<string> inputs;
   inputs.push_back("abba");
   inputs.push_back("abbadd");
   inputs.push_back("baba");
   inputs.push_back("aabb");
   inputs.push_back("logarithm");
   inputs.push_back("algorithm");
   inputs.push_back("nice");
   inputs.push_back("whatever");


   // with custom objects
   PrintSorted(inputs);



   // with just a comparator
   PrintSorted2(inputs);


   return 1;
}
