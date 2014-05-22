// parses strings like "23478" into a list of all possible sequences of single- and double-digit integers


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
void  ParseAll(string input, vector<vector<int> >& aPartitions, vector<int> aSinglePartition)  
{ 
   if (input == "")
   {
      aPartitions.push_back(aSinglePartition);
      return;
   }
   aSinglePartition.push_back(atoi(input.substr(0,1).c_str()));
   ParseAll(input.substr(1,input.length() - 1), aPartitions, aSinglePartition);
   aSinglePartition.pop_back();
   
   if (input.length() >= 2)
   {
      aSinglePartition.push_back(atoi(input.substr(0,2).c_str()));
      ParseAll(input.substr(2,input.length() - 2), aPartitions, aSinglePartition);
   }

   return;
}
///////////////////////////////////////////////
void PrintPartitions(vector<vector<int> > partitions)
{
   for (vector<vector<int> >::iterator it1 = partitions.begin(); it1 != partitions.end(); it1++)
   {
      for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }
   return;
}
////////////////////////////////////////////////
vector<vector<int> > Filter(vector<vector<int> > aPartitions)
{
   vector<vector<int> > FilteredPartitions;
   vector<int> partition;
   int isGood;
   int lastElement;
   
   FilteredPartitions.clear();

   for (vector<vector<int> >::iterator it = aPartitions.begin(); it != aPartitions.end(); it++)
   {
      lastElement = 0;  // rock bottom possible
      isGood = 1;
      partition.clear();
      for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
      {
         if (*it2 <= lastElement || (*it2 % 2) == 1)
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
////////////////////////////////////////////////

int main(int argc, char* argv[]) 
{

   string inputString = "2224";   // this will be the string to partition

   vector<vector<int> > partitions;
   vector<int> singlePartition;

   ParseAll(inputString, partitions, singlePartition);

   PrintPartitions(Filter(partitions));
   
 

  return 1;

   
    
}
