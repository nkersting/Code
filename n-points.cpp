

 /***************************************
N points in the plane (M x M)

 


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
#include <time.h>


using namespace std;

   
    





////////////////////////////////////////////////
///////////////////////////////////////////////

int main() 
{
    

  int N = 20;      // number of objects
  int M = 100;      // grid side
  int Q = 25;     //Q bins per quadrant
  int numtries = 1000000;
  

  int positions[N][2];

  int minval = 100;
  int minpositions[N][2];
  int worldviews[N][4*Q];    
  int worldmap[M][M];
  for (int j = 0; j < M; j++)  
  {
    for (int k = 0; k < M; k++)
    {
       worldmap[j][k] = 0; 
    }
  }


  srand ( time(NULL) );
  for (int i = 0; i <  numtries; i++)
  {

    for (int j = 0; j < N; j++)   // choose N positions randomly
    {
      positions[j][0] = rand() % M ;  // x-coord
      positions[j][1] = rand() % M ;  // y-coord
    }

    for (int j = 0; j < N; j++)  
    {
      for (int k = 0; k < 4*Q; k++)
      {
        worldviews[j][k] = 0; 
      }
    }



    for (int j = 0; j < N; j++)   // compute N worldviews
    {
      for (int k = 0; k < N; k++)
      {
        if (j != k)
	{
	  if (positions[j][0] != positions[k][0])
	  {
	    if (positions[j][0] > positions[k][0]) 
               worldviews[k][abs(Q+Q*floor(atan((positions[j][1]-positions[k][1])/(positions[j][0]-positions[k][0]))/2.0/3.14159))] = 1;
	    if (positions[j][0] < positions[k][0]) 
               worldviews[k][abs(3*Q+Q*floor(atan((positions[j][1]-positions[k][1])/(positions[j][0]-positions[k][0]))/2.0/3.14159))] = 1;
	  }
	  else
	  {
	    if (positions[j][1] > positions[k][1]) worldviews[k][2*Q] = 1;
	    if (positions[j][0] <= positions[k][0]) worldviews[k][0] = 1;

	  }
	}
      }
    }
    

    int x = 0;
    for (int j = 0; j < 4*Q; j++)   // compute worldview overlap
    {
      int prod = 1;
      for (int k = 0; k < N; k++)
      {
	prod = prod * worldviews[k][j];
      }
      x += prod;
    }


    if ( x < minval )
    {
      minval = x;
      for (int j = 0; j < N; j++)   
      {
	minpositions[j][0] = positions[j][0];
        minpositions[j][1] = positions[j][1];
      }
    }



  }




    for (int j = 0; j < N; j++)   // populate the map
    {
      worldmap[minpositions[j][0]][minpositions[j][1]] = 1;  
    }
    
    for (int j = 0; j < M; j++)  
    {
      for (int k = 0; k < M; k++)
      {
	if (worldmap[j][k] == 1)
	{
           cout << "*";
	}
	else
	{
	   cout << " ";
        }
      }
      cout << endl;
    }
  

  
  return 1;    
}
