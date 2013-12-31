// Implement an algorithm to print all valid (e.g., properly opened and closed) combinations of n-pairs of parentheses.
// EXAMPLE:
// input: 3 (e.g., 3 pairs of parentheses)
// output: ()()(), ()(()), (())(), ((())), (()())


#include<iostream>
#include<vector>

using namespace std;

void RecurseParenth(vector<string>& results, int left_count, int right_count, string curr)
{
   if (left_count == 0 && right_count == 0)
   {
      results.push_back(curr);
      return;
   }
   if (left_count > 0)
   {
      curr += "(";
      RecurseParenth(results, left_count - 1, right_count, curr);
      curr = curr.substr(0, curr.length() - 1);
   }

   if (right_count > left_count && right_count > 0)
   {
      curr += ")";
      RecurseParenth(results, left_count, right_count - 1, curr);
      curr = curr.substr(0, curr.length() - 1);
   }
}


vector<string> IterativeParenth(int N)       // much uglier than the recursive solution!
{
   vector<string> temp;  
   temp.push_back("(");
   // first make all possible strings with N of each   
   for (int i = 1; i < 2*N; ++i)
   {
      
      int currsize = temp.size();
      for (int j = 0; j < currsize; ++j)
      {
         temp.push_back(temp.at(j) + ")");
         temp.at(j) += "(";
      }

   } 


   // now filter the list 
   vector<string> results;

   for (int k = 0; k < temp.size(); ++k)
   {
      int left_count = 0;
      int right_count = 0;
      bool legal = true;
      for (int j = 0; j < temp.at(k).size(); ++j)
      {
         if ((temp.at(k))[j] == '(') { left_count++;}
         else (right_count++);

         if (right_count > left_count ||
             left_count > N || right_count > N) {legal = false; break;}
		   
      }

      if (legal == true)
      {
         results.push_back(temp.at(k));
      }
   }
   return results;
}


int main()
{
  vector<string> results;
  int N = 3;
  RecurseParenth(results, N, N, "");

  cout << results.size() << " possible:" << endl;

  for (vector<string>::iterator it = results.begin(); it != results.end(); ++it)
  {
	cout << *it << endl;
  }


  cout << endl << endl;
  vector<string> results2 = IterativeParenth(N);
  for (vector<string>::iterator it = results2.begin(); it != results2.end(); ++it)
  {
	cout << *it << endl;
  }

  return 1;
}
