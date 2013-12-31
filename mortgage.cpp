//Your task is, given the annual interest rate in tenths of a percent, the original amount of the loan, and the period over which the loan is to be repaid, calculate the minimum integral monthly payment so that the loan is repaid in term years or less. All monetary units are in dollars. 


#include <iostream>
#include <math.h> 

using namespace std;

//////////////////////////
int AggregateLoan(int loan, int num_terms, double interest_rate, int low, int high){
   

   if (high - low <= 1){
      return high;
   }

   long burden = loan;
   int payment = (low + (high - low) / 2);
   for (int i = 1; i < num_terms*12; ++i){
      burden -= payment;
         if (burden >= 4000000000.0/(1.0 + interest_rate/100/12)){
             return AggregateLoan(loan, num_terms, interest_rate, payment + 1, high);   //avoid overflow
         }
      burden = ceil((1.0 + interest_rate/100/12)*burden);
   }
   if (burden < payment){
      return AggregateLoan(loan, num_terms, interest_rate, low, payment);
   }
   else{
      return AggregateLoan(loan, num_terms, interest_rate, payment + 1, high);
   }


}
/////////////////////////

int main()
{

    int loan = 1000;    // dollars
    double interest_rate = 5;   // percent
    int num_terms = 1;       // months

    cout << "Please enter loan amount: " ;
    cin >> loan;
    cout << "Interest Rate: " ;
    cin >> interest_rate;
    cout << "Years: " ;
    cin >> num_terms;


    cout << loan << " " << interest_rate << " " << num_terms << endl;
   cout << "Minimum Payment is " << AggregateLoan(loan, num_terms, interest_rate, 0, loan) << endl;
      



   return 1;
}
