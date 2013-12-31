// Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?



#include<iostream>

using namespace std;

bool UniqueChars(string input)
{
  int ascii_counts[130];
  for (int i = 0; i < 130; ++i)
  {
    ascii_counts[i] = 0;
  }

  for (int j = 0; j < input.length(); ++j)
  {
    if (++ascii_counts[(int)input[j]] >= 2)
    {
       return false;
    }    
  }
  return true;
}


int main()
{
  string input;

  cout << "Enter a string: ";
  cin >> input;

  cout << (UniqueChars(input) ? "Unique!" : "Duplicates!" ) << endl;
  

  return 1;
}
