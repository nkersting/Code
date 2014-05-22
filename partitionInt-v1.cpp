// This code solves the famous "Partition Problem", i.e. find all the ways of writing a positive integer N as a sum of
// two smaller positive integers.
// Usage: "partitionInt.exe [v] N "
// Returns: number of partitions and (optionally) what they are, if -v verbose flag set.


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
void  Partition(int n, vector<vector<int> >& aPartitions, vector<int> aSinglePartition)   // solves the partition problem for n
{ 
   if (n >= 0)
  {

  aSinglePartition.push_back(n);
  aPartitions.push_back(aSinglePartition);
  aSinglePartition.pop_back();

  for (int i = n-1; i > 0; i--)
    {
      aSinglePartition.push_back(i);
      Partition(n-i, aPartitions, aSinglePartition);
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



///////////////////////////////////////////////

int main(int argc, char* argv[]) 
{

   int n = 0;   // this will be the integer to partition
   bool verbose = false;

   if (argc < 2 || argc > 3) 
   { 
      std::cout << "Usage is partitionInt.exe [-v] N\n"; 
      std::cin.get();
      exit(0);
   }
   else
   {
      switch (argc)
      {
      case 2:
         n = atoi(argv[1]);
         break;
      case 3:
         verbose = true;
         n = atoi(argv[2]);
         break;
      }
   }


  vector<vector<int> > Partitions;
  vector<int> singlePartition;

  Partition(n, Partitions, singlePartition);
  Partitions = RemoveExcessivePartitions(Partitions);

  cout << "Number of solutions = " << Partitions.size() << endl;  
  if (verbose == true)
  {
     for (vector<vector<int> >::iterator it1 = Partitions.begin(); it1 != Partitions.end(); it1++)
     {
        for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
           cout << *it2 << " ";
        }
        cout << endl;
     }
  }


  return 1;

   
    
}
