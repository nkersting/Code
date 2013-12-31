// You are given two sorted arrays, A and B, and A has a large enough buffer at the end to hold B. Write a method to merge B into A in sorted order.


#include<iostream>

using namespace std;

void Combine(int A[], int B[], int a_size, int b_size)  // crude: insertion sort
{

   int new_end = a_size - b_size;
   for (int i = 0; i < b_size; ++i)
   {
      int j = new_end;
      A[new_end++] = B[i];
      while (A[j] < A[j-1])	
      {
         swap(A[j], A[j-1]);
         --j;
      }
   }
}


// faster: do a merge sort from the back of each list
void Merge(int A[], int B[], int a_size, int b_size)
{
   int i = a_size - 1;
   int j = b_size - 1;
   int k = a_size + b_size - 1;

   while (i >= 0 && j >= 0)
   {
      if (A[i] > B[j])
      {
         A[k--] = A[i--];
      }
      else
      {
         A[k--] = B[j--];
      }
   }

   while (j >= 0)
   {
      A[k--] = B[j--];
   }
}


int main()
{
   int A[15] = {1,3,5,7,8,10,11,34,36,99,0,0,0,0,0};
   int B[5] = {2, 77, 102, 110, 150};

//   Combine(A, B, 15, 5);

   Merge(A,B,10,5);

   for (int i = 0; i < 15; i++)
   {
      cout << A[i] << endl;
   }
   return 1;
}
