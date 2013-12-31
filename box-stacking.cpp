/* Dynamic Programming implementation of Box Stacking problem */
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
 
using namespace std;

/* Representation of a box */
struct Box
{
  // h –> height, w –> width, d –> depth
  int h, w, d;  // for simplicity of solution, always keep w <= d
};
 

bool BoxCompare(const Box& b1, const Box& b2)
{
   return (b1.d * b1.w) > (b2.d * b2.w);
}


/* Returns the height of the tallest stack that can be formed with give type of boxes */
int maxStackHeight( Box arr[], int n )
{
   /* Create an array of all rotations of given boxes
      For example, for a box {1, 2, 3}, we consider three
      instances{{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */
   Box rot[3*n];
   int index = 0;
   for (int i = 0; i < n; i++)
   {
      // Copy the original box
      rot[index] = arr[i];
      index++;
 
      // First rotation of box
      rot[index].h = arr[i].w;
      rot[index].d = max(arr[i].h, arr[i].d);
      rot[index].w = min(arr[i].h, arr[i].d);
      index++;
 
      // Second rotation of box
      rot[index].h = arr[i].d;
      rot[index].d = max(arr[i].h, arr[i].w);
      rot[index].w = min(arr[i].h, arr[i].w);
      index++;
   }
 
   // Now the number of boxes is 3n
   n = 3*n;
 
   /* Sort the array ‘rot[]‘ in decreasing order, using library
      function for quick sort */
   sort(rot, rot + n, BoxCompare);
   for (int i = 0; i < n; i++ )
   {
      printf("%d x %d x %d\n", rot[i].h, rot[i].w, rot[i].d);
   }
 
   /* Initialize msh values for all indexes 
      msh[i] –> Maximum possible Stack Height with box i on top */
   int msh[n];
   for (int i = 0; i < n; i++ )
   {
      msh[i] = rot[i].h;
   }


   /* Compute optimized msh values in bottom up manner */
   for (int i = 1; i < n; i++ )
      for (int j = 0; j < i; j++ )
         if ( rot[i].w < rot[j].w &&
              rot[i].d < rot[j].d &&
              msh[i] < msh[j] + rot[i].h
            )
         {
              msh[i] = msh[j] + rot[i].h;
         }
 
 
   /* Pick maximum of all msh values */
   int max = -1;
   for ( int i = 0; i < n; i++ )
      if ( max < msh[i] )
         max = msh[i];
 
   return max;
}


int main()
{
  Box arr[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
  int n = sizeof(arr)/sizeof(arr[0]);
 
  printf("The maximum possible height of stack is %d\n",
         maxStackHeight (arr, n) );
 
  return 0;
}
