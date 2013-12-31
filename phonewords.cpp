// If a person dials a sequence of numbers on the telephone, what possible words/strings can be formed from the letters associated with those numbers?


#include <iostream>
#include <vector>
#include <map>

using namespace std;


void PhoneWords(vector<int> nums, map<int, string> chars, vector<string>& words, string word)
{
   if (nums.size() == 0)
   {
      words.push_back(word);
      return;
   }

   int currnum = nums.back();
   nums.pop_back();
   if (chars[currnum].length() == 0) 
   {
      PhoneWords(nums, chars, words, word);
   }
   for (int i = 0; i < chars[currnum].length(); i++)
   {
      PhoneWords(nums, chars, words, word + chars[currnum][i]);
   }
}


int main()
{
   map<int, string> chars;
   chars[1] = "";
   chars[2] = "ABC";
   chars[3] = "DEF";
   chars[4] = "GHI";
   chars[5] = "JKL";
   chars[6] = "MNO";
   chars[7] = "PQRS";
   chars[8] = "TUV";
   chars[9] = "WXYZ";
   chars[0] = "";

   string numstring;
   cout << "Enter your number: ";
   cin >> numstring;

   vector<int> input;
   for (int i = 0; i < numstring.length(); ++i)
   {
      input.push_back(static_cast<int>(numstring[i]) - static_cast<int>('0'));
   }

   vector<string> words;
   PhoneWords(input, chars, words, "");

   for (vector<string>::iterator it = words.begin(); it != words.end(); ++it)
   {
      cout << *it << endl;
   }

   return 0;

}
