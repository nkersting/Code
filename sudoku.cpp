// Solve Sudoku with backtracking and pruning


#include <stdio.h>


#define N 9

bool FindUnassignedLocation(int grid[][N], int& row, int& col)
{
   for (row = 0; row < N; ++row)
   {
      for (col = 0; col < N; ++col)
      {
         if (grid[row][col] == 0)
         {
            return true;
         }
      }
   }
   return false;
}


bool UsedInRow(int grid[][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}


bool UsedInCol(int grid[][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(int grid[][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool IsSafe(int grid[][N], int row, int col, int num)
{
   return !UsedInRow(grid, row, num) &&
      !UsedInCol(grid, col, num) &&
      !UsedInBox(grid, row - row % 3, col - col % 3, num);
}


bool SolveSudoku(int grid[][N])
{
   int row, col;

   if (!FindUnassignedLocation(grid, row, col))
   {
      return true;   // solved it
   }

   for (int num = 1; num <= 9; ++num)
   {
      if (IsSafe(grid, row, col, num))
      {
         grid[row][col] = num;

         if (SolveSudoku(grid))
         { 
            return true;
         }
         else
         {
            grid[row][col] = 0;
         }         
      }
   }
   return false;
}






void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
             printf("%2d", grid[row][col]);
        printf("\n");
    }
}


int main()
{
    // 0 means unassigned cells
    // int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
    //                   {5, 2, 0, 0, 0, 0, 0, 0, 0},
    //                   {0, 8, 7, 0, 0, 0, 0, 3, 1},
    //                   {0, 0, 3, 0, 1, 0, 0, 8, 0},
    //                   {9, 0, 0, 8, 6, 3, 0, 0, 5},
    //                   {0, 5, 0, 0, 9, 0, 6, 0, 0},
    //                   {1, 3, 0, 0, 0, 0, 2, 5, 0},
    //                   {0, 0, 0, 0, 0, 0, 0, 7, 4},
    //                   {0, 0, 5, 2, 0, 6, 3, 0, 0}};

   // int grid[N][N] =   {{0, 0, 0, 0, 0, 0, 0, 1, 2},     // Skeina Fig7.2
   //                    {0, 0, 0, 0, 3, 5, 0, 0, 0},
   //                    {0, 0, 0, 6, 0, 0, 0, 7, 0},
   //                    {7, 0, 0, 0, 0, 0, 3, 0, 0},
   //                    {0, 0, 0, 4, 0, 0, 8, 0, 0},
   //                    {1, 0, 0, 0, 0, 0, 0, 0, 0},
   //                    {0, 0, 0, 1, 2, 0, 0, 0, 0},
   //                    {0, 8, 0, 0, 0, 0, 0, 4, 0},
   //                    {0, 5, 0, 0, 0, 0, 6, 0, 0}};



   int grid[N][N] =  {{6, 0, 0, 0, 0, 0, 0, 4, 0},   // http://www.sudoku.ws/extreme-20.htm
                      {0, 0, 5, 0, 0, 2, 0, 0, 7},
                      {7, 2, 9, 0, 0, 0, 0, 0, 3},
                      {0, 9, 0, 0, 4, 0, 0, 0, 1},
                      {0, 0, 0, 0, 6, 0, 0, 0, 0},
                      {4, 0, 0, 0, 8, 0, 0, 7, 0},
                      {3, 0, 0, 0, 0, 0, 1, 6, 5},
                      {2, 0, 0, 4, 0, 0, 8, 0, 0},
                      {0, 5, 0, 0, 0, 0, 0, 0, 4}};

    if (SolveSudoku(grid) == true)
          printGrid(grid);
    else
         printf("No solution exists");
 
    return 0;
}
