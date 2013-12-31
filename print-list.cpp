// Use this to print simple data files for the other programs to use


#include <iostream>


using namespace std;


///////////////////////////
void PrintListWithOneDuplicate()
{
  for (int i = 0; i <= 1<<20; ++i){
      cout << i << endl;
      if (i == 1000) { cout << i << endl;}   // the duplicate entry
   }
}
/////////////////////////

int main()
{
  


   PrintListWithOneDuplicate();

 

   return 1;
}
