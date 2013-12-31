// Implement a function that prints all possible combinations of the characters in a
// string. These combinations range in length from one to the length of the string. Two
// combinations that differ only in ordering of their characters are the same combination.
// In other words, “12” and “31” are different combinations from the input string
// “123”, but “21” is the same as “12”.

#include<iostream>
#include<vector>

using namespace std;



int main()
{

   string input;
   cout << "Enter a string: ";
   cin >> input;

   // loop over all combinations
   int N = input.length();
   for (int combo = 1; combo < 1<<N ; ++combo)
   {
      string combo_string = "";
      for (int i = 0; i < N; ++i)
      {
         if ( (combo >> i) % 2 == 1)
         {
            combo_string += input[i];
         }
      }
      cout << combo_string << endl;
   }

   
   return 1;

}
