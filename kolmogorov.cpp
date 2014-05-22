

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

void AddToGeneratedPatterns(int maxBits, vector<int> templates, int startbitsMax, int repeatbitsMax, std::map < int, vector<vector<int> > >& generatedPatterns, int pattern,  vector<vector<int> > tripletCombo)
{
   int partialPattern = 0;
   int invertedPattern = 0;
   int goodPattern = 1;
   int input_pattern  = pattern;
   int templatebits =  0;
   vector<int> copied_templates;
   vector<int> thisTriplet;
   
   copied_templates = templates;   // needed because we change templates below



   // copied_templates.clear();
   // int total = 0;
   // for (vector<int>::iterator it = templates.begin(); it != templates.end(); it++)
   // {
   //    copied_templates.push_back(*it);
   //    //  cout << *it << " ";
   //    total += *it;
   // }

   // for (vector<vector<int> >::iterator it = tripletCombo.begin(); it != tripletCombo.end(); it++ )
   // {
   //    total += (*it).at(0) + (*it).at(2) + (*it).at(4);
   // }

   // if (total >= 13)
   // {
   //    //  cout << "too many bits error " << endl;          //FIXME: figure out why this ever happens
   //    return;
   // }


//   cout << "start  repeat size " << startbitsMax << " " << repeatbitsMax << " " << copied_templates.size() << endl;

//   cout << "total bits: " << total << " " << startbitsMax << " " << repeatbitsMax << " " << copied_templates.size() << endl;

   for (vector<int>::reverse_iterator it = copied_templates.rbegin(); it != copied_templates.rend(); ++it)
   {
      templatebits = *it;
      // loop over possible bitpatterns for this template
      for (int startbits = 1; startbits <= startbitsMax; startbits++)  
      {
       for (int repeatbits = 1; repeatbits <= repeatbitsMax ; repeatbits++) 
         {
            for (int startbitPattern = 0; startbitPattern < 1<<startbits; startbitPattern++)
            {
               for (int repeatbitPattern = 1; repeatbitPattern <= 1<<repeatbits; repeatbitPattern++)     // repeat of 0 excluded
               {
                  for (int templatebitPattern = 1; templatebitPattern <= (1<<templatebits); templatebitPattern++)  // template of 0 excluded  
                  {
                     // compute what this contributes to the pattern, e.g. 
                     // startbitPattern = 0, repeatbitPattern = 2, templatebitPattern = 2 ("10") gives  "0101"   template filled "from the back in"
                     // startbitPattern = 1, repeatbitPattern = 2, templatebitPattern = 2 gives  "01010"

                     goodPattern = 1;   

                     // construct the inverted templatepattern

                     invertedPattern = 0;
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
                        if (partialPattern > (1<<28) || partialPattern < 0)    // safeguard against overflows
                        {
                           goodPattern = 0;
                        }                     
                     }
                     // cout << "bits,template: " <<  templatebits << "," << templatebitPattern << " inverted: " << invertedPattern << " start: " << startbitPattern << " repeat: " << repeatbitPattern << " result: " << partialPattern << endl;
                     // cout << "start and repeat " << startbits << " " << repeatbits << endl;

                     // add to the pattern
                     pattern = pattern | partialPattern;  // the bitwise OR correctly 'adds' patterns
                     
                     if (pattern > (1<<28) || pattern < 0)    // safeguard against overflows
                     {
                        goodPattern = 0;
                     }

                     if (goodPattern == 1)
                     {
                        thisTriplet.clear();
                        thisTriplet.push_back(templatebits);
                        thisTriplet.push_back(templatebitPattern);
                        thisTriplet.push_back(startbits);
                        thisTriplet.push_back(startbitPattern);
                        thisTriplet.push_back(repeatbits);
                        thisTriplet.push_back(repeatbitPattern);
                        tripletCombo.push_back(thisTriplet);  // add the (pattern, start, repeat) triplet that contributed

                        int total = 0;
                        for (vector<vector<int> >::iterator it = tripletCombo.begin(); it != tripletCombo.end(); it++ )
                        {
                           total += (*it).at(0) + (*it).at(2) + (*it).at(4);
                        }
                        

                        templates.pop_back();
                        if (templates.size() == 0 and total < maxBits)    // i.e. this is the last template to consider
                           // FIXME: figure out why there should ever be more than maxBits here; isn't the recursion supposed to disallow?
                        {
                           //   cout << "template computed:" << pattern << endl;
                           std::pair <int, vector <vector<int> > > matchedPair(pattern, tripletCombo);
                           generatedPatterns.insert(matchedPair);
                        }
                        else
                        {
                           AddToGeneratedPatterns(maxBits, templates, startbitsMax - startbits, repeatbitsMax - repeatbits, generatedPatterns, pattern, tripletCombo);
                        }
                        //    cout << "template: " << templatebitPattern << " start:" << startbitPattern << " repeat:" << repeatbitPattern << " pattern:" << pattern << endl;

                        templates.push_back(templatebits);
                        tripletCombo.pop_back();
                     }         
                     pattern = input_pattern;
                  }
               }
            }
         }
      }      
   }
}
//////////////////////////////
int match(int maxBits, int bitpattern, int bitsToUse, std::map < int, vector<vector<int> > >& generatedPatterns)
{
  // returns whether the bitpattern can be compressed into sums of triplets,
  // with exactly bitsToUse bits.

  int templatebits = 0;


  vector<vector<int> > Partitions;
  vector<int> singlePartition;
  vector<vector<int> > tripletCombo;


    for (int startbits = 1; startbits <= bitsToUse - 2; startbits++)   // need to save at least one bit for repeat, one bit for template
    {
       for (int repeatbits = 1; repeatbits <= bitsToUse - 1 - startbits; repeatbits++) // need to save at least one bit for template
       {
         // now we have a fixed number of bits to use for templates:
          templatebits = bitsToUse - startbits - repeatbits;
	// how many different ways to use these bits for templates, equivalent to partion function p(totalbits), e.g. p(4) = 5, p(10) = 42
        // for each partition, distribute the startbits and repeatbits, at least one each per template
        // then flesh out the bits and add all generated patterns to generatedPatterns
          Partitions.clear();
          singlePartition.clear();	

          Partition(templatebits, templatebits, Partitions, singlePartition);
          Partitions = RemoveExcessivePartitions(Partitions);

          // cout << "PARTITION: " << templatebits << " out of " << bitsToUse << " bits to use total " << endl;

          // for (vector<vector<int> >::iterator it = Partitions.begin(); it != Partitions.end(); it++)
          // {

          //    for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
          //    {
          //       cout << *it2 << " ";
          //    }
          //    cout << endl;
          // }


          for (vector<vector<int> >::iterator it = Partitions.begin(); it != Partitions.end(); it++)
          {

             // for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
             // {
             //    cout << *it2 << " ";

             // }
             // cout << "CHECK:" << startbits << " " << repeatbits << "  total should be " << bitsToUse << endl;
             // cout << endl;

             tripletCombo.clear();
             AddToGeneratedPatterns(maxBits, *it, startbits, repeatbits, generatedPatterns, 0, tripletCombo);

             for (std::map < int, vector<vector<int> > >::iterator it2 = generatedPatterns.begin(); 
                  it2 != generatedPatterns.end(); it2++)
             { 

                int upper = ((it2->first)>>maxBits)<<maxBits;    
                if (it2->first - upper - bitpattern ==  0)   // only the lower bits need to match
                {
                   cout << endl;
                   cout << "matching " << it2->first << " and " << bitpattern << endl;
                   return it2->first;    // if any of the patterns match, then we have already successfully encoded the bitpattern
                }
             }
             generatedPatterns.clear();

          }
       }           
    }

   
    return 0;
}
///////////////////////////////



int ComputeMinBits(int bitpattern, int n)
{
  int worst = n;  // the worst one could do is use n bits to compress n bits
  int matchedPattern = 0;
  std::map<int, vector<vector<int> > > generatedPatterns;
 
  for (int totalbits = 1; totalbits < n; totalbits++)    
  {
     generatedPatterns.clear();

     // determine whether some triplet exactly matches the bitpattern with totalbits, if so it must be using the minimum number of bits
     matchedPattern = match(n, bitpattern, totalbits, generatedPatterns);
     std::map<int, vector<vector<int> > >::iterator it = generatedPatterns.find(matchedPattern);
     if (it != generatedPatterns.end())
     {
        // print the combination of triplets that matched

        for (std::vector<vector<int> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
           cout << "(" << (*it2).at(0) << ":"  << (*it2).at(1) << ", " 
                       << (*it2).at(2) << ":"  << (*it2).at(3) << ", " 
                << (*it2).at(4) << ":"  << (*it2).at(5) << ")  "; 
        }
        cout << endl;
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
//     for (int i = 5957 ; i < 1<<n ; i = i+2)                    // 1011101000101
     for (int i = 5213 ; i < 1<<n ; i = i+2)                    // 1010001011101

  {
  
    for (int j = 0; j < n; j++ )
    {
       bitpattern[n-j-1] = (i & (1 << j)) >> j;
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
