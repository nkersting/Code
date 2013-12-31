
// Imagine a robot sitting on the upper left hand corner of an NxN grid. The robot can only move in two directions: right and down. How many possible paths are there for the robot?


#include<iostream>

using namespace std;

void AllPaths(int i, int j, int& count, int N)
{
  if (i == N && j == N) { return;}
  count++;
 
  if (i < N) { AllPaths(i+1, j, count, N);}
  if (j < N) { AllPaths(i, j+1, count, N);}

}


int main()
{
  int N = 10;
  int count = 0;
  AllPaths(1,1,count,N);

  cout << count << endl;
 return 1;
}
