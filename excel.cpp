
// convert an Excel column name to an integer


#include<iostream>

using namespace std;


int Convert(string input)
{
   int value = 0;
   int power = 1;
   for (int i = input.length() - 1; i >= 0; --i)
   {
      value += power*(input[i] - 'A' + 1);
      power *= 26;
   }
   return value;
}





int main()
{
   string input;
   cout << "Enter excel column:";
   cin >> input;

   cout << Convert(input);

   return 0;
}
