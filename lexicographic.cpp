// radix sort on strings composed of capital letters

#include<iostream>
#include<vector>

using namespace std;

class Test
{
private: int a;

public: Test()
      {
         a = 0;
      }
public: void SetVal(int x, Test* targ)
      {
         targ->a = x;
      }

   int GetVal()
      {
         return a;
      }
};



void StringRadix(vector<string>& input)
{
   int N = input.size();
   //first find maximum
   int max = 0;
   for (int j = 0; j < N; ++j)
   {
      if (input[j].length() > max)
      {
         max = input[j].length();
      }
   }

   for (int i = 0; i < max; ++i)
   {
      int buckets[27]; // need to include a "zero" at position 0
      for (int k = 0; k <= 26; ++k)
      {
         buckets[k] = 0;
      }
      string temp[N];
      for (int k = 0; k < N; ++k)
      {
         temp[k] = "";
      }
      
      for (int j = 0; j < N; ++j)
      {
         string x = input.at(j);
         if (x.length() <= i)
         {
            buckets[0]++;
         }
         else
         {
            buckets[(int)(x[x.length() - i - 1]) - (int)('A') + 1]++;
         }
      }
      for (int k = 1; k <= 26; ++k)
      {
         buckets[k] += buckets[k-1];
      }
      for (int j = N-1; j >= 0; --j)
      {
         string x = input.at(j);
         if (x.length() <= i)
         {
            temp[--buckets[0]] = x;
         }
         else
         {
            temp[--buckets[(int)(x[x.length() - i - 1]) - (int)('A') + 1]] = x;
         }
      }
      for (int j = 0; j < N; ++j)
      {
         input.at(j) = temp[j];
      }
   }

}


int main()
{

   // first some silliness to test accessibility of private members

   Test c1;
   Test c2;

   c1.SetVal(1,&c1);
   cout << "c1 is " << c1.GetVal() << endl;
   c2.SetVal(2,&c1);
   cout << "c1 is " << c1.GetVal() << endl;

   // so apparently one can access other instances' private members from within a method of that class


   vector<string> inputs;
   inputs.push_back("A");
   inputs.push_back("B");
   inputs.push_back("C");
   inputs.push_back("AA");
   inputs.push_back("AAB");
   inputs.push_back("DDE");
   inputs.push_back("ZA");

   StringRadix(inputs);
   for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it)
   {
      cout << *it << " ";
   }
   cout << endl;

   return 0;
}


