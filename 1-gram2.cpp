

 /***************************************


 To Do:

 1. Currently does not include numbers (e.g. 3001), monetary amounts (e.g. $19.99), since the number
    of entries then blows up. Nonetheless it does make sense for these to contribute to the total
    detropy.

 2. Does not include other UTF-8 characters outside of roman alphabet. 

 5. Make this Obj. Oriented 
 6. Write in Python?
 7. Make iPhone App



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

using namespace std;

   
    


    const int maxnum = 6445870;
    const int max_size = 10000;
    const float Pi = 3.14159265358;


//    const unsigned long int totalwords = 222724056;  // actually 0.001 times real total
//    const unsigned long int rare_word_val = 3.0-1.0*log10(1.0*39/totalwords);  // assume just below threshold
    

unsigned long
    hashval(const char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;
    }



float
    detropyval(unsigned long frq[][2], string userstring, unsigned long totalwords)
{
    
    
    int index =  totalwords/2;
        int index_lo = 0;
        int index_hi = totalwords; 
        const char *hashstring = userstring.c_str(); 
        
        unsigned long testkey = hashval(hashstring);
        if (userstring[0] == '\0') return 0;
        while (testkey != frq[index][0]){

            if(testkey < frq[index][0]){
                index_hi = index;                    
            }
            else {
                index_lo = index;
            }

            index = (index_hi + index_lo)/2;


            if (index == index_lo) {
       //         return rare_word_val;   // no match found, so must be rare
                 return 0;   // no match found, assume numerical or glitch
            }

        }

        return (-1.0*log10(1.0*frq[index][1]/totalwords));
   //     return (3.0-1.0*log10(1.0*frq[index][1]/totalwords));  // the '3' is to account for factor 1000 out of totalwords
   //     return 1.0*frq[index][1];
    
}


  void FixString(string mainstring)
  {
      int Len = strlen(mainstring.c_str()); 

     if( (int)mainstring[Len-1] < 65 || (int)mainstring[Len-1] > 122) {
         mainstring[Len-1] = '\0';           // remove final punctuation like ! ? etc.
     }


     if( (int)mainstring[0] < 65 || (int)mainstring[0] > 122) {
         int i = 0;                         // remove initial punctuation like " ( etc.
         while(i < Len - 1) {
             mainstring[i] = mainstring[i+1];
             i++;
         }
         mainstring[Len-1] = '\0';
     }


 //    if( (int)mainstring[0] >= 65 && (int)mainstring[0] <= 90) {
 //        mainstring[0] = (char)mainstring[0] + 32;             // lowercase first letter
 //    }                                                     //Google ngrams are case-sensitive
     return;
  }


    void google_parse_and_sum() {

    ifstream myfile;
    myfile.open ("googlebooks-eng-all-1gram-20090715-8.csv");  

    ofstream outfile;
    outfile.open("outdata.txt");

    string last_ngram=" ";
    string ngram;
    int year;
    int match_count;
    int page_count;
    int volume_count;


    if (myfile.is_open())
  {
    int count = 0;
    int wordcount = 0;
    while ( !myfile.eof())
    {
    
      myfile >> ngram >> year  >> match_count >> page_count >> volume_count;

      if ( ((int)ngram[0] < 123 && (int)ngram[0] > 96) ||
           ((int)ngram[0] < 91 && (int)ngram[0] > 64)) {
               
               
               if (ngram == last_ngram) {
                 wordcount+= match_count;            
               } 
               else {
                   outfile << last_ngram << " " << wordcount << endl;
                   wordcount = match_count;
                   last_ngram = ngram;
               }
               
      }
      
  //    myfile >> ngram >> year  >> match_count >> page_count >> volume_count;
 //     outfile  << ngram << year  << match_count << page_count << volume_count << endl;


      if (count%1000000 == 0) cout << count << endl;
      count++;
    }
    myfile.close();
    }

  else cout << "Unable to open file \n"; 

    return;
    }



    void google_write_keys() {

    string wrd;
    string rank;
    string val;

    ifstream myfile;
    myfile.open ("outdata-google5.txt");  
    
    ofstream outfile;
    outfile.open("outdata.txt");

    if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      myfile >> wrd >> val;
      outfile << hashval(wrd.c_str())  << " " << wrd << " "  << val << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file \n"; 


  
  outfile.close();



    }

  
unsigned long self_Lex() {

    string wrd;

    ifstream myfile;
    myfile.open ("sample.txt");  

    ofstream outfile;
    outfile.open("outdata.txt");


    vector<string> lex;
    vector<int> lex_freqs;
    
    int i = 0;
    int found = 0;
    unsigned long totalwords = 0;

    if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      found = 0;
      myfile >> wrd;
      totalwords++;
      
      i = 0;
      for ( vector<string>::iterator vItr = lex.begin() ; vItr != lex.end() ; vItr++ )
        {
                
                
                if ( *vItr == wrd ) {
                     lex_freqs.at(i)++; 
                     found = 1;                  
                }                         // Word found
                
                i++;
        }
        
      if (found == 0) {
          lex.push_back(wrd);
          lex_freqs.push_back(1);
   //       outfile << "captured " << wrd << endl;
      }

      
      
    }
    myfile.close();
  }

  else cout << "Unable to open file \n"; 

  i=0;
  string teststring;
  for ( vector<string>::iterator vItr = lex.begin() ; vItr != lex.end() ; vItr++ )
        {
            teststring = *vItr;
           outfile << hashval(teststring.c_str()) << " " << *vItr  << " " << lex_freqs.at(i) <<  endl;  
       
           i++;
         }

 
    outfile.close();
    system("sort -n outdata.txt > lexicon-sorted.txt");
  return totalwords;
}



int self_analyze(unsigned long totalwords) {



      ifstream keyrank_file;
    keyrank_file.open ("lexicon-sorted.txt");


    unsigned long key = 0;
    string wrd = " ";
    unsigned long freq = 0;
    int i = 1;
  

    typedef unsigned long (*ObjectArray)[maxnum][2];
    ObjectArray freqs = (ObjectArray) new unsigned long[maxnum][2];
  
    (*freqs)[0][0] = 0;
    (*freqs)[0][1] = 0;
  
    
    if (keyrank_file.is_open())
    {
       
    while ( i < maxnum && !keyrank_file.eof())
    {
     
    keyrank_file >> key >> wrd >> freq;
   
    (*freqs)[i][0] = key;
    (*freqs)[i][1] = freq;
      i++;      
    }
   
    keyrank_file.close();
    }

    else cout << "Unable to open file \n"; 

 
    // Now compute detropy

     ifstream sample_file;
    sample_file.open ("sample.txt");  

    ofstream outfile2;
    outfile2.open("outdata2.txt");

    ofstream outfile3;
    outfile3.open("outdata3.txt");

    string inwrd;
    float moments[max_size] = {0};
    float detropy = 0;
    float total_detropy = 0;
    int count = 0;
    if (sample_file.is_open())
    {
     while ( !sample_file.eof())
    {
      sample_file >> inwrd ;
      outfile2 << inwrd;
      FixString(&inwrd[0]);
      detropy = detropyval(*freqs, inwrd, totalwords);
      if (detropy != 0) {
      outfile2 << "       " << detropy  << endl;
      total_detropy += detropy;

      for (int j = 0; j < max_size; j++){
         moments[j]+=detropy*cos(Pi*j*count/(totalwords-1));
      }
     
      count++;
    
      }
    }
    sample_file.close();
    }

  else cout << "Unable to open file \n"; 
    
    outfile2 << endl << endl << "Total detropy is " << total_detropy << endl;
    outfile2 << "Average detropy is " << total_detropy/count << endl;
   
    outfile2.close();


    for (int k = 0; k < max_size; k++){
        outfile3 << k << " " << moments[k]/moments[0] << endl;
    }



    outfile3.close();

   delete [] freqs;

        return 0;




///////////////////////////////












}


int text_format() {


    ifstream sample_file;
    sample_file.open ("1.txt");  

    ofstream outfile;
    outfile.open("2.txt");

    string inwrd;
    unsigned long freq;
    if (sample_file.is_open())
    {
     while ( !sample_file.eof())
    {
      sample_file >> inwrd >> freq;
      outfile << inwrd << endl;
    }
    
    }
    sample_file.close();
    outfile.close();
    return 0;
}



int google_analyze(int maxnum) {

   
    
    ifstream keyrank_file;
    keyrank_file.open ("key-word-freq-sorted3.txt");
 //   keyrank_file.open ("test.txt");
 //   totalwords = 8242970000;
      

    

    //
    //  FIRST LOAD HASHTABLE INTO MEMORY
    //
    
    //  ofstream outfile;
    // outfile.open("outdata.txt");
           
    unsigned long key = 0;
    string wrd = " ";
    unsigned long freq = 0;
    unsigned long totalwords=0;
    int i = 1;
    int totalbills=0;
    int totalfreqs = 0;

    typedef unsigned long (*ObjectArray)[maxnum][2];
    ObjectArray freqs = (ObjectArray) new unsigned long[maxnum][2];
  
    (*freqs)[0][0] = 0;
    (*freqs)[0][1] = 0;
  
    
    if (keyrank_file.is_open())
    {
       
    while ( i < maxnum && !keyrank_file.eof())
    {
     
    keyrank_file >> key >> wrd >> freq;
   
    (*freqs)[i][0] = key;
    (*freqs)[i][1] = freq;
      i++;
      totalfreqs += freq;
      if(totalfreqs > 1000000000) {
          totalbills+= (totalfreqs/1000000000);
          totalfreqs = 0;
      }
    //  if (i < 100) {
   //       outfile <<  key << " " << wrd << " " << freq << endl;
   //        outfile <<  (*freqs)[i-1][0] << " " << (*freqs)[i-1][1] << endl;
    //  }

     if (i%100000 == 0) cout << i << endl;
      
    }

    
    keyrank_file.close();
    }

  else cout << "Unable to open file \n"; 

 


  // outfile << "total number is " << totalbills << " " << totalwords << endl;

  //
  //  
  //  Read in a text file and compute individual and total detropy.
  //  
  //  
  //  
  
    ifstream sample_file;
    sample_file.open ("sample.txt");  

    ofstream outfile;
    outfile.open("outdata.txt");

    string inwrd;
    float total_detropy = 0;
    float detropy = 0;
    float detropy_last = 0;
    int count = 0;
    if (sample_file.is_open())
    {
     while ( !sample_file.eof())
    {
      sample_file >> inwrd ;
      outfile << inwrd;
      FixString(&inwrd[0]);
      detropy = detropyval(*freqs, inwrd, maxnum);
      if (detropy != 0) {
      outfile << "           " << detropy  << " " << detropy - detropy_last << endl;
      total_detropy += detropy;
      detropy_last = detropy;
      count++;
      }
    }
    sample_file.close();
    }

  else cout << "Unable to open file \n"; 
    
    outfile << endl << endl << "Total detropy is " << total_detropy << endl;
    outfile << "Average detropy is " << total_detropy/count << endl;

    
   delete [] freqs;


  return 0;
}




////////////////////////////////////////////////
///////////////////////////////////////////////

int main() 
{
    
    unsigned long totalwords = 0;
    int reply;
    cout <<"\n 0=Self, 1=Google: ";
    cin >> reply;

    switch (reply)
    {
    case 2: cout << "text formatting";
        text_format();
        return 0;


    case 0: cout << "Computing self-lexicon";
        totalwords = self_Lex();    
        self_analyze(totalwords);
          return 0;

    case 1: cout << "Applying Google 1-grams";

        totalwords = maxnum;  // fix for now
        google_analyze(totalwords);                                                                   
        return 0;               


   
   
    }
}
