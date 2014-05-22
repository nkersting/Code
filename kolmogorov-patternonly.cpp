

 /***************************************

First specify what length of bit-string one is interested in, n.
This code evaluates all the possible bitstrings of that length.

Each such integer will have a "variety" , proportional to the number of bits needed in the compression of the string.
Compression is taken to be a sum over triplets (template, number of repetitions, offset), which is a model assumption.
 
The question is: for a given value of n, which bit pattern exhibits the most variety?
How does "Shave and a haircut, two bits" (1011101000101 = 5957) rank in the space of 13-bit patterns? ANS: 11 bits needed



 ****************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <algorithm>


using namespace std;


///////////////////////////////
void  Partition(int M, int n, vector<vector<int> >& aPartitions, vector<int> aSinglePartition)   // solves the partition problem for M
{
  
  int sum = 0;        

  if (n >= 0)
  {

  aSinglePartition.push_back(n);
  aPartitions.push_back(aSinglePartition);
  aSinglePartition.pop_back();

 
    for (int i = n-1; i > 0; i--)
    {
      aSinglePartition.push_back(i);

      // compute residual sum to partition = M - sum of all entries in the partition thus far
      sum = 0;
      for (vector<int>::iterator it = aSinglePartition.begin(); it != aSinglePartition.end(); it++)
      {
        sum += *it;
      }

      
      if (M - sum > 0)
	{
	  Partition(M, M - sum, aPartitions, aSinglePartition);
	}



      aSinglePartition.pop_back();
    }
  }

  return;

}

////////////////////////////////
vector<vector<int> > RemoveExcessivePartitions(vector<vector<int> > aPartitions)
{

   vector<vector<int> > FilteredPartitions;
   vector<int> partition;
   int isGood = 1;
   int lastElement = 1000;
   
   FilteredPartitions.clear();

   for (vector<vector<int> >::iterator it = aPartitions.begin(); it != aPartitions.end(); it++)
   {
      lastElement = 1000;  // arbitarily high value
      isGood = 1;
      partition.clear();
      for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
      {
         if (*it2 > lastElement)
         {
            isGood = 0;
            break;
         }
         else
         {
            partition.push_back(*it2);
            lastElement = *it2;
         }
      }
      if (isGood == 1) FilteredPartitions.push_back(partition);
   }

   return FilteredPartitions;


}
////////////////////////////////

void AddToGeneratedPatterns(vector<int> templates, int startbitsMax, int repeatbitsMax, vector<int>& generatedPatterns, int pattern)
{
   int partialPattern = 0;
   for (vector<int>::reverse_iterator it = templates.rbegin(); it != templates.rend(); ++it)
   {
      int templatebits = *it;
      // loop over possible bitpatterns for this template
      for (int startbits = 1; startbits <= startbitsMax; startbits++)
      {
         for (int repeatbits = 1; repeatbits <= repeatbitsMax; repeatbits++)
         {
            for (int startbitPattern = 0; startbitPattern < 1<<startbits; startbitPattern++)
            {
               for (int repeatbitPattern = 1; repeatbitPattern <= 1<<repeatbits; repeatbitPattern++)     // repeat of 0 excluded
               {
                  for (int templatebitPattern = 0; templatebitPattern <= (1<<templatebits)-1; templatebitPattern++)  
                  {
                     // compute what this contributes to the pattern, e.g. 
                     // startbitPattern = 0, repeatbitPattern = 2, templatebitPattern = 2 ("10") gives  "0101"   template filled "from the back in"
                     // startbitPattern = 1, repeatbitPattern = 2, templatebitPattern = 2 gives  "01010"



                     // construct the inverted templatepattern
                     int invertedPattern = 0;
                     for (int i = 0; i < templatebits; i++)
                     {


                        invertedPattern += (((templatebitPattern)&(1<<i))>>i)<<(templatebits - i - 1);

                        // int bitmatch = ((templatebitPattern)&(1<<i));
                        // int shift = templatebits - i - 1;
                        // cout  << bitmatch << " " << templatebits - i - 1 << " " << invertedPattern << endl;
                     }
                     //            cout << "templatebits " << templatebits << " pattern: " << templatebitPattern << "         inverted: " << invertedPattern << endl;

                     partialPattern = 0;
                     for (int i = 1; i <= repeatbitPattern; i++)
                     {
                        partialPattern += ((invertedPattern)<<(startbitPattern))<<(templatebits*(i-1));
                     }
                     //                           cout << "bits,template: " <<  templatebits << "," << templatebitPattern << " inverted: " << invertedPattern << " start: " << startbitPattern << " repeat: " << repeatbitPattern << " result: " << partialPattern << endl;

                     // add to the pattern
                     pattern = pattern | partialPattern;  // the bitwise OR correctly adds patterns
                     templates.pop_back();
                     if (templates.size() == 0)
                     {
                        //         cout << "template computed:" << pattern << endl;
                        generatedPatterns.push_back(pattern);
                     }
                     else
                     {
                        AddToGeneratedPatterns(templates, startbitsMax - startbits, repeatbitsMax - repeatbits, generatedPatterns, pattern);
                     }
                     //   cout << "template: " << templatebitPattern << " start:" << startbitPattern << " repeat:" << repeatbitPattern << " pattern:" << pattern << endl;

                     templates.push_back(templatebits);
                     pattern -= partialPattern;
                  }
               }
            }
         }
      }      
   }
}
//////////////////////////////
bool match(int maxBits, int bitpattern, int bitsToUse)
{
  // returns whether the bitpattern can be compressed into sums of triplets,
  // with exactly bitsToUse bits.

  vector<int> generatedPatterns;
  int templatebits = 0;
  generatedPatterns.clear();

  vector<vector<int> > Partitions;
  vector<int> singlePartition;


    for (int startbits = 1; startbits < bitsToUse - 2; startbits++)   // need to save at least one bit for repeat, one bit for template
    {
       for (int repeatbits = 1; repeatbits < bitsToUse - 1 - startbits; repeatbits++) // need to save at least one bit for template
       {
         // now we have a fixed number of bits to use for templates:
          templatebits = bitsToUse - startbits - repeatbits;
	// how many different ways to use these bits for templates, equivalent to partion function p(totalbits), e.g. p(4) = 5, p(10) = 42
        // for each partition, distribute the startbits and repeatbits, at least one each per template
        // then flesh out the bits and add all generated patterns to the vector generatedPatterns
          Partitions.clear();
          singlePartition.clear();	

          Partition(templatebits, templatebits, Partitions, singlePartition);
          Partitions = RemoveExcessivePartitions(Partitions);

          //       cout << "PARTITION: " << templatebits << endl;
          for (vector<vector<int> >::iterator it = Partitions.begin(); it != Partitions.end(); it++)
          {

             // for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
             // {
             //    cout << *it2 << " ";
             // }
             // cout << endl;

             // if ((*it).size() == 1 && (*it).at(0) == 2)
             // {
             //    cout << "template: " << (*it).at(0) << " start:" << startbits << " repeat:" << repeatbits << endl;
             // }

             AddToGeneratedPatterns(*it, startbits, repeatbits, generatedPatterns, 0);

             for (vector<int>::iterator it2 = generatedPatterns.begin(); 
                  it2 != generatedPatterns.end(); it2++)
             { 

                int upper = (*it2>>maxBits)<<maxBits;    
                if (*it2 - upper - bitpattern ==  0)   // only the lower bits need to match
                {
                   return true;    // if any of the patterns match, then we have already successfully encoded the bitpattern
                }
             }
             generatedPatterns.clear();

          }
       }           
    }

   
    return false;
}
///////////////////////////////



int ComputeMinBits(int bitpattern, int n)
{
  int worst = n;  // the worst one could do is use n bits to compress n bits
 
  for (int totalbits = 1; totalbits < n; totalbits++)     
    {
       // determine whether some triplet exactly matches the bitpattern with totalbits, if so it must be using the minimum number of bits
       if (match(n, bitpattern, totalbits))
       {
	  return totalbits;
       }  
    }
  
  return worst;
}
////////////////////////////////////////////////
///////////////////////////////////////////////

int main() 
{
    
  int n = 13;


  int bitpattern[n];
  int bestbitpattern[n];
  int maxvariety = -10000;
  int variety = 0;
//  for (int i = (1<<(n-1)) + 1 ; i < 1<<n ; i = i+2)          // 100...0001 to 111...1111
//     for (int i = 5461 ; i < 1<<n ; i = i+2)                    // 1010101010101
     for (int i = 5957 ; i < 1<<n ; i = i+2)                    // 1011101000101

  {
  
    for (int j = 0; j < n; j++ )
    {
       bitpattern[j] = (i & (1 << j)) >> j;
    }

    variety = ComputeMinBits(i, n);        // the fewer bits needed to encode the bitpattern, the lower the variety
    if (variety > maxvariety) 
    {
      maxvariety = variety;
      //   cout << i << " " <<  variety << "        ";
      for (int j = 0; j < n; j++ )
      {
	bestbitpattern[j] = bitpattern[j];
        //    cout << bestbitpattern[j] << " ";
      }
      //   cout << endl;
    }

        
    cout << i << " " <<  variety << "        ";
    for (int j = 0; j < n; j++ )
    {
       cout << bitpattern[j] << " ";
    }
    cout << endl;
    
  }

  
 
  cout << "The highest variety found was " << maxvariety << endl;

  for (int j = 0; j < n; j++ )
  {
    cout << bestbitpattern[j] << " ";
  }
 
  
  return 1;

   
    
}
