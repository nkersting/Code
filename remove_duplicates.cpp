
// Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. NOTE: One or two additional variables are fine. An extra copy of the array is not.
// FOLLOW UP
// Write the test cases for this method.

#include<iostream>

using namespace std;

string RemoveDuplicates(string input)
{
   
   int position = 0;
   while (input.length() > position++)
   {
      if (input.find(input[position], 0) < position)
      {
         input = (input.substr(0,position)).append(input.substr(position + 1, input.length() - position - 1));
         position--;
      }

   }

   return input;

}



int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    char* input = argv[1];
    cout << input << endl;
    string in_string(input);
    cout <<     RemoveDuplicates(in_string);
    return 1;
  }
  else { return 0;}

}


// Test Cases:
// 1. buss
   // 2. has
   // 3. aaa_!44
   // 4. (null)
   // 5. aaaaaaaaa
   // 6. abababa
   // 7. aabbbb
