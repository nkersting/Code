// Write a program for displaying the ten most frequent words in a file such that your program should be efficient in all complexity measures.


#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<sstream>

using namespace std;

struct PairCompare
{
   bool operator()(const pair<string,int>& p1, const pair<string,int>& p2)
      {
         return p1.second > p2.second;
      }

};


void MapFreqs(vector<string> input, map<string, int>& freqs)
{
   for (vector<string>::iterator it = input.begin(); it != input.end(); ++it)
   {
      if (freqs.find(*it) == freqs.end())
      {
         freqs.insert(pair<string, int>(*it, 1));
      }
      else
      {
         freqs[*it]++;
      }
   }
}

void FillSet(multiset<pair<string, int>, PairCompare>& sortedfreqs, map<string, int> freqs)
{
   for (map<string,int>::iterator it = freqs.begin(); it != freqs.end(); ++it)
   {
      sortedfreqs.insert(pair<string, int>(it->first, it->second));
   }

}


int main()
{
   vector<string> input;

   stringstream ss("Select a random element in the data set as a pivot, and use it to partition the data into sets of elements less than and greater than the pivot. From the sizes of these sets, we know the position of the pivot in the total order, and hence whether the median lies to the left or right of this point. Now we recur on the appropriate subset until it converges on the median. This takes (on average) O(lg n) iterations, with the cost of each iteration being roughly half that of the previous one. This defines a geometric series that converges to a linear-time algorithm, although if you are very unlucky it takes the same time as quicksort");

   while(ss.good())
   {
      string temp;
      ss >> temp;
      input.push_back(temp);
   }

   map<string,int> freqs;
   multiset<pair<string, int>, PairCompare> sortedfreqs;

   MapFreqs(input, freqs);
   FillSet(sortedfreqs, freqs);

   
   for (multiset<pair<string, int>, PairCompare>::iterator it = sortedfreqs.begin(); it != sortedfreqs.end(); ++it)
   {
      cout << it->first << " " << it->second << endl;
   }

   return 0;
}


