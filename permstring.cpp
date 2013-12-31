
// Write a method to compute all permutations of a string



#include<iostream>
#include<vector>

using namespace std;


// recursive solution
void StringPermsVerbose(string input, vector<string>& outputs, string curr, int index)
{
   if (index == input.length())
   {
      outputs.push_back(curr);
      return;
   }

   for (int i = 0; i <= curr.length(); ++i)  // number of chars to print before the chosen one
   {
      string temp;
      for (int j = 0; j < i; ++j)
      {
         temp += curr.at(j);
      }
      temp += input.at(index);
      for (int j = i; j < curr.length(); ++j) 
      {
         temp += curr.at(j);
      }
      StringPermsVerbose(input, outputs, temp, index + 1);
   }
}

void StringPermsCuter(string input, vector<string>& outputs, string curr, int index)
{
   if (index == input.length())
   {
      outputs.push_back(curr);
      return;
   }

   for (int i = 0; i <= curr.length(); ++i)  // number of chars to print before the chosen one
   {
      StringPermsCuter(input, outputs, curr.substr(0, i) + input.at(index) + curr.substr(i, curr.length() - i), index + 1);
   }
}


void StringPermsSwap(string input, vector<string>& outputs, int index)
{
   if (index == input.length())
   {
      outputs.push_back(input);
      return;
   }

   for (int j = index; j < input.length(); ++j)
   {
      swap(input.at(index), input.at(j));
      StringPermsSwap(input, outputs, index + 1);
      swap(input.at(index), input.at(j));
   }
}



int main(int argc, char** argv)
{
	if (argc != 2) { return 0;}

	string input = argv[1];
	vector<string> results;
//        StringPermsVerbose(input, results, "", 0);
//	StringPermsCuter(input, results, "", 0);
        StringPermsSwap(input, results, 0);

	for (vector<string>::iterator it = results.begin(); it != results.end(); ++it)
{
	cout << *it << endl;
}

return 1;
}
