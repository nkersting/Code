

 /***************************************
Scale a list of volume record counts to a
particular total count.
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

using namespace std;

   
    





////////////////////////////////////////////////
///////////////////////////////////////////////

int main() 
{
    
  int totalCount = 300000;


 
  ifstream volume_file;
  // volume_file.open ("1800_PickupOriginVolumeProfileTEST");  //scale example #1
  //  volume_file.open ("1800_PickupOriginVolumeProfileTEST2");  //scale example #2
   volume_file.open ("1800_PickupOriginVolumeProfileTEST3");  //scale example #3

  vector <int> volnums;
  vector <int> unscaled;
  vector <int> scaled;
  string line;
  string read_s;
  string word;
  int fieldCount;
  int header = 1;

  while (getline(volume_file, line))
  {
    istringstream read_ss(line);
    fieldCount = 1;
    read_s = "";
    if (header == 1)
    {
      header = 0;
      continue;
    }
    while (getline(read_ss, read_s, ','))
    {
      if (fieldCount == 2 )
      {
	volnums.push_back(atoi(read_s.c_str()));
      }
      if (fieldCount == 3 )
      {
	unscaled.push_back(atoi(read_s.c_str()));
      }
      fieldCount++;
    }
  }


  int totalUnscaledSum = 0;
  for (vector<int>::iterator it = unscaled.begin();
       it != unscaled.end(); it++)
  {
    totalUnscaledSum += *it;
  }


  float projectionFactor = 1.0*totalCount/totalUnscaledSum;
  float carryOver = 0;
  float scalePrelim = 0;
  int checksum = 0;
  int scaleFinal = 0;
  int count = 0;

  for (vector<int>::iterator it = unscaled.begin();
       it != unscaled.end(); it++)
  {
    scalePrelim = (*it)*projectionFactor + carryOver;
    scaleFinal = floor(scalePrelim);
    scaled.push_back(scaleFinal);
    checksum += scaleFinal;
    carryOver = scalePrelim - scaleFinal;
    cout << volnums.at(count) << "," << scaleFinal << endl;
    count++;
  }


  // cout << "Total count was computed as " << checksum;
  
  return 1;

   
    
}
