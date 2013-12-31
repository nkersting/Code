/*
* DJBX33A (Daniel J. Bernstein, Times 33 with Addition)
*
* This is Daniel J. Bernstein's popular `times 33' hash function as
* posted by him years ago on comp.lang.c. It basically uses a function
* like ``hash(i) = hash(i-1) * 33 + str[i]''. This is one of the best
* known hash functions for strings. Because it is both computed very
* fast and distributes very well.
*
* The magic of number 33, i.e. why it works better than many other
* constants, prime or not, has never been adequately explained by
* anyone. So I try an explanation: if one experimentally tests all
* multipliers between 1 and 256 (as RSE did now) one detects that even
* numbers are not useable at all. The remaining 128 odd numbers
* (except for the number 1) work more or less all equally well. They
* all distribute in an acceptable way and this way fill a hash table
* with an average percent of approx. 86%.
*
* If one compares the Chi^2 values of the variants, the number 33 not
* even has the best value. But the number 33 and a few other equally
* good numbers like 17, 31, 63, 127 and 129 have nevertheless a great
* advantage to the remaining numbers in the large set of possible
* multipliers: their multiply operation can be replaced by a faster
* operation based on just one shift plus either a single addition
* or subtraction operation. And because a hash function has to both
* distribute good _and_ has to be very fast to compute, those few
* numbers should be preferred and seems to be the reason why Daniel J.
* Bernstein also preferred it.
*
*
* -- Ralf S. Engelschall <rse@engelschall.com>
*/



#include <iostream>
#include <map>
#include <vector>
#include<fstream>

using namespace std;


int DJBHash(string input)
{
   int hash = 5381;
   
   for (int i = 0; i < input.length(); ++i)
   {
      hash = ((hash<<5) + hash) + input[i];
   }

   return hash;
}


int main()
{

   int N = 0;
   ifstream dictionary_file;
   dictionary_file.open("dictionary.txt");
   string word;
   map<int, vector<string> > djbHash;
   while(dictionary_file.good())
   {
      dictionary_file >> word;
      djbHash[DJBHash(word)].push_back(word);
   }


   int sum = 0;
   for (map<int, vector<string> >::iterator it = djbHash.begin(); it != djbHash.end(); ++it)
   {
      sum += it->second.size();
      if (it->second.size() >= 2)
      {
         cout << it->first << " ";
         for (vector<string>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
         {
            cout << *it2 << " ";
         }
         cout << endl;
      }
   } 

   cout << "Average collision rate is " << sum/djbHash.size() << endl;

}


// Errata:
/* see https://groups.google.com/forum/#!topic/comp.lang.c/lSKWXiuNOAk
