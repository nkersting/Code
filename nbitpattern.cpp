

 /***************************************

To search over all n-bit combinations, just 
loop over the integers from 0 to 2^n - 1.

Each such integer will have a "variety" :

V = Sum_i (uniqueness of bit i)

where "uniqueness of bit i" is Sum_(j != i) ( = number of bits difference between L_i and L_j 
+ number difference between R_i and R_j)  
where L_i is the bit pattern to the left of bit i, and R_i is similarly to the right.
This is something like (L_i XOR L_j) + (R_i XOR R_j), trimming off the extra bits on each longer pattern
and counting those as adding +1 each to the sum. We can use >> and << to accomplish that comparison.
Thus if the bit is uniquely distinguishable from every other bit, its contribution to the 
total variety is maximal.
 
The question is: for a given value of n, which bit pattern exhibits the most variety?
How does "Shave and a haircut, two bits" (1011101000101) rank in the space of 13-bit patterns?


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


///////////////////////////////
int ComputeVariety3(int bitpattern[], int n)
{
  int variety = 0;
  int Ldiff = 0;
  int Rdiff = 0;
  for (int i = 0; i < n; i++ )
  {
    for (int j = 0; j < n; j++ )
    {
 
      if (i == j) continue;      // i-th position must not be compared to itself
      
      if (i > j)
      {
	Ldiff = j+1;
	for (int bitpos = 1; bitpos <= j; bitpos++)
	{
	  if (bitpattern[j - bitpos] != bitpattern[i - bitpos])
	  {
	    Ldiff = bitpos;
	    continue;
	  }
	}

	Rdiff = n-i;
	for (int bitpos = 1; bitpos <= n-i-1; bitpos++)
	{
	  if (bitpattern[j + bitpos] != bitpattern[i + bitpos])
	  {
	    Rdiff = bitpos;
	    continue;
	  }
	}

        variety += -min(Ldiff, Rdiff);
      }


      if (i < j)
      {

	Ldiff = i+1;
	for (int bitpos = 1; bitpos <= i; bitpos++)
	{
	  if (bitpattern[i - bitpos] != bitpattern[j - bitpos])
	  {
	    Ldiff = bitpos;
	    continue;
	  }
	}

	Rdiff = n-j;
	for (int bitpos = 1; bitpos <= n-j-1; bitpos++)
	{
	  if (bitpattern[j + bitpos] != bitpattern[i + bitpos])
	  {
	    Rdiff = bitpos;
	    continue;
	  }
	}

	variety += -min(Ldiff, Rdiff);
      }

    }
  
  }

  return variety;

}
    



///////////////////////////////
int ComputeVariety2(int bitpattern[], int n)
{
  int variety = 0;
  int maxbitsneeded = 0;
  int bitsneeded = 0;
  int Ldiff = 0;
  int Rdiff = 0;
  for (int i = 0; i < n; i++ )
  {
    maxbitsneeded = 0;        // the most number of bits needed to distinguish this position from the others
    for (int j = 0; j < n; j++ )
    {
 
      if (i == j) continue;      // i-th position must not be compared to itself
      
      if (i > j)
      {
	Ldiff = j+1;
	for (int bitpos = 1; bitpos <= j; bitpos++)
	{
	  if (bitpattern[j - bitpos] != bitpattern[i - bitpos])
	  {
	    Ldiff = bitpos;
	    continue;
	  }
	}

	Rdiff = n-i;
	for (int bitpos = 1; bitpos <= n-i-1; bitpos++)
	{
	  if (bitpattern[j + bitpos] != bitpattern[i + bitpos])
	  {
	    Rdiff = bitpos;
	    continue;
	  }
	}

        bitsneeded = min(Ldiff, Rdiff);
      }


      if (i < j)
      {

	Ldiff = i+1;
	for (int bitpos = 1; bitpos <= i; bitpos++)
	{
	  if (bitpattern[i - bitpos] != bitpattern[j - bitpos])
	  {
	    Ldiff = bitpos;
	    continue;
	  }
	}

	Rdiff = n-j;
	for (int bitpos = 1; bitpos <= n-j-1; bitpos++)
	{
	  if (bitpattern[j + bitpos] != bitpattern[i + bitpos])
	  {
	    Rdiff = bitpos;
	    continue;
	  }
	}
	bitsneeded = min(Ldiff, Rdiff);
      }
        if ( maxbitsneeded < bitsneeded) maxbitsneeded = bitsneeded;

    }
    variety += -maxbitsneeded;
  }

  return variety;

}
    
///////////////////////////////

int ComputeVariety(int bitpattern[], int n)
{
  int variety = 0;
  
  for (int i = 0; i < n; i++ )
  {
    for (int j = 0; j < n; j++ )
    {
      if (i == j) continue;      // i-th position must not be compared to itself
      if (i > j)
      {
	variety += (i-j); // j has j positions to the left, and i likewise has i positions to the left
	for (int bitpos = 1; bitpos <= j; bitpos++)
	{
	  variety += (bitpattern[j - bitpos] + bitpattern[i - bitpos])%2;  // any difference in position adds to variety
	}

	variety += (i-j); // j has n-j-1 positions to the right, which is (i-j) more than i has
	for (int bitpos = 1; bitpos <= n-i-1; bitpos++)
	{
	  variety += (bitpattern[j + bitpos] + bitpattern[i + bitpos])%2;
	}
      }


      if (i < j)           // might combine this with above, but we're verbose for symmetry's sake
      {
	variety += (j-i); // j has j positions to the left, and i likewise has i positions to the left
	for (int bitpos = 1; bitpos <= i; bitpos++)
	{
	  variety += (bitpattern[i - bitpos] + bitpattern[j - bitpos])%2;  // any difference in position adds to variety
	}

	variety += (j-i); // i has n-i-1 positions to the right, which is (j-i) more than j has
	for (int bitpos = 1; bitpos <= n-j-1; bitpos++)
	{
	  variety += (bitpattern[i + bitpos] + bitpattern[j + bitpos])%2;
	}
      }
    }
  }
  
  return variety;
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
  for (int i = (1<<(n-1)) + 1 ; i < 1<<n ; i = i+2)          // 100...0001 to 111...1111
  {
  
    for (int j = 0; j < n; j++ )
    {
      bitpattern[j] = (i & (1 << j)) >> j;
    }

    variety = ComputeVariety3(bitpattern, n);
    if (variety > maxvariety) 
    {
      maxvariety = variety;
      //       cout << i << " " <<  variety << "        ";
      for (int j = 0; j < n; j++ )
      {
	bestbitpattern[j] = bitpattern[j];
	//		cout << bestbitpattern[j] << " ";
      }
      //     cout << endl;
    }

    /*    
cout << i << " " <<  variety << "        ";
 for (int j = 0; j < n; j++ )
      {
	cout << bitpattern[j] << " ";
      }
      cout << endl;
    */


  }
 
  cout << "The highest variety found was " << maxvariety << endl;

  for (int j = 0; j < n; j++ )
  {
    cout << bestbitpattern[j] << " ";
  }
 
  
  return 1;

   
    
}
