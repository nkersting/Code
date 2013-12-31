
// a b c d e 
// f g h i j 
// k l m n o 
// p q r s t 
// u v w x y 
// z 
// the movie "up" would be "dddd!u!"


#include<iostream>

using namespace std;


bool TestMove(int n, char source, int column_inc, int row_inc)
{
   if ((int)(source - 'a') + column_inc > 25) {return false;}
   return true;
}


void ProcessCol(string& output, int column_inc)
{
   if (column_inc > 0)
   {
      for (int i = 0; i < column_inc; ++i)
      {
         output += 'r';
      }
   }
   else
   {
      for (int i =  0; i < -column_inc; ++i)
      {
         output += 'l';
      }
   }
}

void ProcessRow(string& output, int row_inc)
{
   if (row_inc > 0)
   {
      for (int i = 0; i < row_inc; ++i)
      {
         output += 'd';
      }
   }
   else
   {
      for (int i = 0; i < -row_inc; ++i)
      {
         output += 'u';
      }
   }
}


string MoveSequence(string input, int n)
{
   string output = "";
   char source = 'a';
   while (input.length() > 0)
   {
      char target = input[0];
      input = input.substr(1, input.length() - 1);    

      int ordinal = target - source;
      int column_inc = ordinal % n;
      int row_inc = ordinal / n;
      bool colfirst = TestMove(n, source, column_inc, row_inc);

      if (colfirst)
      {    
         ProcessCol(output, column_inc);
         ProcessRow(output, row_inc);      
      }
      else
      {
         ProcessRow(output, row_inc);
         ProcessCol(output, column_inc);
      } 
      output += '!';
      source = target;
   }

   return output;
}


int main()
{
   int n = 5;

   string input;
   cout << "Enter name: ";
   cin >> input;

   cout << MoveSequence(input, n);
   return 0;
}
