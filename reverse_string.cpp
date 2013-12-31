// Write code to reverse a C-Style String. (C-String means that “abcd” is represented as five characters, including the null character.)


#include<iostream>

using namespace std;

void ReverseString(char* input)
{
  // first get length
  int length = 0;
  while (input[length] != '\0')
  {
    length++;
  }
  
  char temp;
  for (int i = 0; i < length / 2; ++i)
  {
    temp = input[i];
    input[i] = input[length - i - 1];
    input[length - i - 1] = temp;
   }
}

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    char* input = argv[1];
    cout << input << endl;
    ReverseString(input);
    cout << input << endl;
    return 1;
  }
  else { return 0;}

}
