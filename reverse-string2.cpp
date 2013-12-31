

#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

string ReverseWords(string input)
{
   vector<string> words;
   stringstream ss(input);
   string test;
   while (ss.good())
   {
      ss >> test;
      words.push_back(test);
   }

   string output = "";
   for (vector<string>::reverse_iterator it = words.rbegin(); it != words.rend(); ++it)
   {
      output.append(*it);
      output += ' ';
   }

   return output;
}


void ReverseInPlace(string& input)
{
   for (int i = 0; i < input.length() / 2; ++i)
   {	
      char temp = input[i];
      input[i] = input[input.length() - i - 1];
      input[input.length() - i - 1] = temp;
   }

   int begin = 0;
   char temp;
   for (int i = 0; i <= input.length(); ++i)
   {
      if (input[i] == ' ' || input[i] == '\0')
      {
         for (int j = begin; j < (i - begin) / 2 + begin; ++j)
         {
            temp = input[j];
            input[j] = input[i - j + begin - 1];
            input[i - j + begin - 1] = temp;
         } 
         begin = i+1;
      }
   }
}

int main()
{
   string input = "hello there man";
  
   cout << ReverseWords(input) << endl;

   ReverseInPlace(input);
   cout << input;

   return 0;
}
