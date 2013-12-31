// Implement a routine that prints all possible orderings of the characters in a string. In
// other words, print all permutations that use all the characters from the original
// string. For example, given the string “hat”, your function should print the strings
// “tha”, “aht”, “tah”, “ath”, “hta”, and “hat”. Treat each character in the input string as
// a distinct character, even if it is repeated. Given the string “aaa”, your routine should
// print “aaa” six times. You may print the permutations in any order you choose.


#include<iostream>
#include<vector>

using namespace std;


void Generate(vector<vector<int> >& perms, int max, int index, int current[] )
{
   if (index == max)
   {
      vector<int> curr_perm;
      for (int i = 0; i < max; ++i)
      {
         curr_perm.push_back(current[i]);         
      }
      perms.push_back(curr_perm);
      return;
   }
   for (int j = index; j < max; ++j)
   {
      swap(current[index], current[j]);
      Generate(perms, max, index + 1, current);
      swap(current[index], current[j]);
   }

}

int main()
{

   string input;
   vector<vector<int> > perms;
   cout << "Enter a string: ";
   cin >> input;

   // first generate all numerical permutations needed
   int N = input.length();
   vector<int> orig;
   for (int i = 1; i <= N; ++i)
   {
      orig.push_back(i);
   }
   Generate(perms, N, 0, &orig[0]);
   

   // now march down the permutations and print out the strings

   for (vector<vector<int> >::iterator it_outer = perms.begin(); it_outer != perms.end(); ++it_outer)
   {
      string current = "";
      for (vector<int>::iterator it_inner = it_outer->begin(); it_inner != it_outer->end(); ++it_inner)
      {
         current += input[*it_inner - 1];
      }
      cout << current << endl;
   }

   return 1;

}
