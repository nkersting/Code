// using standard touch-tone phone key mappings from integers 0-9
// to english letters, how many words on average does a
// number sequence map to?



#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<sstream>

using namespace std;


//////////////////////////
bool GoodWord(string word)
{
   for (int i = 0; i < word.length(); ++i)
   {
      if ((int)word[i] > 122 || (int)word[i] < 97) { return false; }
   }
   return true;
}



int Keymap(char input)
{
   int code;
   if ((int)input >= 97 && 
       (int)input <= 118)
   {
      return (((int)input - 97) % 3 + 2);  // so 'a','b','c' go to 2, etc..
   }
   else if ((int)input >= 119 && 
       (int)input <= 122)
   {
      return 9;
   }
   return -1;   // no mapping
}



string Numberstring(string input)
{
   string output = "";

   for (int i = 0; i < input.length(); ++i)
   {
      int digit = Keymap(input[i]);
      if (digit != -1)
      {
         ostringstream convert; 
         convert << digit;
         output.append(convert.str());
      }
   }
   return output;
}


//////////////////
int main()
{

   ifstream dictionary_file;
   dictionary_file.open("dictionary.txt");
   string word;
   set<string> dictionary;
   vector<string> sentences;
   map<string, vector<string> > keyencodings;
 

   if (dictionary_file.is_open())
   {
      while(dictionary_file.good())
      {
         dictionary_file >> word;
         if (GoodWord(word)) {dictionary.insert(word);}
      }
      dictionary_file.close();
   }
 
 
   for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
   {
      keyencodings[Numberstring(*it)].push_back(*it);
   }

   ofstream outfile("out.txt");
   map<int, int> counts;
   for (map<string, vector<string> >::iterator it = keyencodings.begin(); it != keyencodings.end(); ++it)
   {
      if (counts.find((it->second).size())  != counts.end())
      {
         counts[(it->second).size()]++;
      }
      else
      {
         counts[(it->second).size()] = 1;
      }

   }

   int total_count = 0;
   int expectation = 0;
   for (map<int, int >::iterator it = counts.begin(); it != counts.end(); ++it)
   {
      outfile << it->second << " " << it->first << endl;
      expectation += it->first * it->second;
      total_count += it->second;
   }

cout << "Total words = " << total_count << endl;
cout << "Unique words = " << counts[1] << endl;
cout << "% non-unique words = " << 100.0*(1.0 - 1.0*counts[1] / total_count) << endl;
cout << "Expected Degeneracy = " << 1.0 * expectation / total_count << endl;

return 1;
}
