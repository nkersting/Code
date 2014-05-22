// firstpass2.cpp : Defines the entry point for the console application.
//



#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <set>
#include <vector>
#include <sstream>
#include <memory>
#include <fstream>
#include <string.h>
#include <math.h>
#include <cstring>
#include <map>
#include <algorithm>
#include <ctime>
#include "dirent.h"


#include <stdio.h>
#include <stdlib.h>


using namespace std;

const char* MOMENTS_FILE = "/home/nkersting/quantumrepoire.com/moments.json";
const char* KEY_HASHES = "hash-wrd-freq.txt";
const char* DETROPY_DATA = "/home/nkersting/quantumrepoire.com/detropy.json";
const unsigned long TOTALGOOGLE = 250581; // in units 10^6, so actually 250581399213
// should be more like 248000 based on measurements
const int MAXNUM = 6445870;
const unsigned long MAXMOMS = 100;
const int MAXSTRING = 200;
const float Pi = 3.14159265358;


const string ENV[ 24 ] = {                 
        "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
        "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
        "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
        "HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
        "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
        "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
        "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
        "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
        "SERVER_SIGNATURE","SERVER_SOFTWARE" };   



const string c_ContentHeader = "Content-type: text/html\n\n";

    // ---- CONTENT LENGTH ----

    ///<Summary>
    /// The content length environment variable
    /// name
    ///</Summary>
    const string c_ContentLengthVariableName = "CONTENT_LENGTH";

    ///<Summary>
    /// Function to return the current requests
    /// content length
    ///</Summary>
    const int GetContentLength()
    {
        int l_result = 0;
        char* l_ContentLengthVariable = getenv(c_ContentLengthVariableName.c_str());
        if ( l_ContentLengthVariable != NULL )
        {
            l_result = atoi(l_ContentLengthVariable);
        }
        return l_result;

    }

    // ---- END CONTENT LENGTH ----


    // ---- GET CONTENT ----

    ///<Summary>
    /// Function to return the content
    ///</Summary>
    const list<string> GetContent()
    {
        list<string> l_result;

        // Now seek the content
        int l_ContentLength = GetContentLength();
        if ( l_ContentLength > 0 )
        {
            try
            {
                // Allocate a buffer for the information
                auto_ptr<char> l_Buffer (new char[l_ContentLength]);

                // Read the content sent into the buffer
                int l_bytesRead = fread (l_Buffer.get(), sizeof(char), l_ContentLength, stdin);

                // Check the data length
                if ( l_bytesRead == l_ContentLength )
                {                                        
                    // Convert the buffer to a string
                    stringstream l_stream (l_Buffer.get());

                    // Push the content as a string into the buffer
                    while ( !l_stream.eof() )
                    {
                        string l_item;
                        l_stream >> l_item;

                        l_result.push_back(l_item);
                    }
                }
            }
            catch (bad_alloc l_badAllocationException)
            {
                // TODO handle bad alloc
            }
        }

        return l_result;
    }

    // ---- END GET CONTENT ----

////////////////////////////
	//// Detropy functions
	////////////////////

	
unsigned long
    hashval(const char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;
    }



float detropyval(unsigned long frq[][2], string userstring, unsigned long totalwords, unsigned long totalfreq)
{
    
    
   int index =  totalwords/2;
   int index_lo = 0;
   int index_hi = totalwords; 
   const char *hashstring = userstring.c_str(); 
        
   unsigned long testkey = hashval(hashstring);
   if (userstring[0] == '\0') return 0;
   while (testkey != frq[index][0]){

      if(testkey < frq[index][0])
      {
         index_hi = index;                    
      }
      else {
         index_lo = index;
      }

      index = (index_hi + index_lo)/2;


      if (index == index_lo) 
      {
         //         return rare_word_val;   // no match found, so must be rare
         return 0;   // no match found, assume numerical or glitch
      }

   }

   return (6.0-1.0*log10(1.0*frq[index][1]/totalfreq));
   
    
}


  string FixString(string mainstring)
  {

	if (mainstring.length() < 3) return mainstring;

	char newstring[MAXSTRING];

	int pos = 0;
	if(mainstring.at(0)  < 65 || mainstring.at(0) > 122)
	{
		// ignore initial punctuation
	}
	else
	{
		newstring[pos] = mainstring.at(0);
		pos++;
	}


	for (int i = 1; i < mainstring.length() - 1; i++ )
	{
		newstring[pos] = mainstring.at(i);
		pos++;
		
	}

	if(mainstring.at(mainstring.length() - 1)  < 65 
		|| mainstring.at(mainstring.length() - 1) > 122)
	{
		
		// ignore final punctuation
	}
	else
	{
		newstring[pos] = mainstring.at(mainstring.length() - 1);
		pos++;
	}


	newstring[pos] = '\0';

	return newstring;


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
    outfile.open("lexicon-sorted.txt");


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
  std::map<unsigned long, std::pair<string, int> > freqMap;
  for ( vector<string>::iterator vItr = lex.begin() ; vItr != lex.end() ; vItr++ )
  {
        teststring = *vItr;
		std::pair<string, int> inputPair(*vItr, lex_freqs.at(i));
        freqMap[hashval(teststring.c_str())] = inputPair;
        i++;
  }

  for (std::map<unsigned long, std::pair<string, int> >::iterator it = freqMap.begin(); it != freqMap.end(); it++)
  {
		outfile << it->first << " " << it->second.first << " " << it->second.second << endl;
  }
   
  outfile.close();

  return totalwords;
}



int self_analyze(unsigned long totalwords)
{



    ifstream keyrank_file;
    keyrank_file.open ("lexicon-sorted.txt");


    unsigned long key = 0;
    string wrd = " ";
    unsigned long freq = 0;
    int i = 1;
  

    typedef unsigned long (*ObjectArray)[MAXNUM][2];
    ObjectArray freqs = (ObjectArray) new unsigned long[MAXNUM][2];
  
    (*freqs)[0][0] = 0;
    (*freqs)[0][1] = 0;
  
    
    if (keyrank_file.is_open())
    {
       
    while ( i < MAXNUM && !keyrank_file.eof())
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

    ofstream outfile;
    outfile.open("word-detropy.txt");

    ofstream outfile3;
    outfile3.open("moments.txt");

    string inwrd;
    float moments[MAXMOMS] = {0};
    float detropy = 0;
	float detropy_last = 0;
    float total_detropy = 0;
    int count = 0;
    if (sample_file.is_open())
    {
	 outfile <<	 "var data = " << endl << "[" << endl;
     while ( !sample_file.eof())
     {
		  count++;

		  sample_file >> inwrd ;
		  inwrd = FixString(inwrd);
		  detropy = detropyval(*freqs, inwrd, totalwords, totalwords);
		  if (detropy != 0)
		  {  
			  outfile << "{\'sequence\': " << count << ", \'detropy\': " << detropy <<
				  ", \'detropyChange\': " << detropy - detropy_last <<  ", \'word\': \"" << inwrd << "\"}";
			  total_detropy += detropy;
			  detropy_last = detropy;
		  }
		  else
		  {
			   outfile << "{\'sequence\': " << count << ", \'detropy\': " << detropy_last <<
				  ", \'detropyChange\': " << detropy - detropy_last <<  ", \'word\': \"" << inwrd << "\"}";
		  }

		  if (!sample_file.eof())
		  {
			  outfile << "," << endl;
		  }
		  else
		  {
			  outfile << endl << "];" << endl;
		  }
    

		  for (int j = 0; j < MAXMOMS; j++)
		  {
			 moments[j]+=detropy*cos(Pi*j*(count-1)/(totalwords-1));
		  }    
	 }
	 sample_file.close();
	}
    else
	{
		cout << "Unable to open file \n"; 
	}
    
 //   outfile2 << endl << endl << "Total detropy is " << total_detropy << endl;
 //   outfile2 << "Average detropy is " << total_detropy/count << endl;
   
    outfile.close();


    for (int k = 0; k < MAXMOMS; k++){
        outfile3 << k << " " << moments[k]/moments[0] << endl;
    }



    outfile3.close();

   delete [] freqs;

        return 0;

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



void google_analyze(std::vector<string> wordlist)
{

   
    
    ifstream keyrank_file;
    keyrank_file.open (KEY_HASHES);
 
    //
    //  FIRST LOAD HASHTABLE INTO MEMORY
    //
 
           
    unsigned long key = 0;
    string wrd = " ";
    unsigned long freq = 0;
    int i = 1;
    int totalbills=0;
    int totalfreqs = 0;

    typedef unsigned long (*ObjectArray)[MAXNUM][2];
    ObjectArray freqs = (ObjectArray) new unsigned long[MAXNUM][2];
  

    (*freqs)[0][0] = 0;
    (*freqs)[0][1] = 0;
    
    if (keyrank_file.is_open())
    {
       
       while ( i < MAXNUM && !keyrank_file.eof())
       {
     
          keyrank_file >> key >> wrd >> freq;
   
          (*freqs)[i][0] = key;
          (*freqs)[i][1] = freq;

          i++;
          totalfreqs += freq;
          if(totalfreqs > 1000000000)
          {
             totalbills+= (totalfreqs/1000000000);
             totalfreqs = 0;
          }        
       }

    
       keyrank_file.close();
    }

  //  
  //  Read in a text file and compute individual and total detropy.
  //  
  //  
  //  
  
    
    ofstream outfile;
    outfile.open(DETROPY_DATA);


    string inwrd;
    float total_detropy = 0;
    float detropy = 0;
    float detropy_last = 0;
    int count = 0;
	unsigned long totalwords = wordlist.size();
	float moments[MAXMOMS] = {0};
	



	outfile <<	 "var data = " << endl << "[" << endl;


     count = 0; 
     for (vector<string>::iterator it = wordlist.begin(); it != wordlist.end(); it++)
     {
		  count++;
		  inwrd = *it;
		  inwrd = FixString(inwrd);
		  detropy = detropyval(*freqs, inwrd, MAXNUM, TOTALGOOGLE);
		  if (detropy != 0) {
	  
			  outfile << "{\'sequence\': " << count << ", \'detropy\': " << detropy <<
				  ", \'detropyChange\': " << detropy - detropy_last <<  ", \'word\': \"" << inwrd << "\"}";
			  total_detropy += detropy;
			  detropy_last = detropy;
		  }
		  else
		  {
				outfile << "{\'sequence\': " << count << ", \'detropy\': " << detropy_last <<
					  ", \'detropyChange\': " << 0 <<  ", \'word\': \"" << inwrd << "\"}";
		  }
		  if (count < totalwords)
		  {
			  outfile << "," << endl;
		  }
		  else
		  {
			  outfile << endl << "];" << endl;
		  }

		  for (int j = 0; j < min(totalwords/2, MAXMOMS); j++)
		  {
			 moments[j]+=detropy*cos(Pi*j*(count-1)/(totalwords-1));
		  }    
	 }

	outfile << endl << "var avgdetropy = " << total_detropy/totalwords << ";" << endl;

    outfile.close();

  //// below we compute moments

	  ofstream outfile2;
      outfile2.open(MOMENTS_FILE);

	  float amplitude = 0;
	  float totalamplitudeSquared = 0;

	  outfile2 <<	 "var data2 = " << endl << "[" << endl;

	  for (int k = 1; k < min(totalwords/2, MAXMOMS); k++)
	  {
			amplitude = moments[k]/moments[0];
			totalamplitudeSquared += amplitude*amplitude;
		    outfile2 << "{\'moment\': " << k << ", \'amplitude\': " << amplitude << "}";
			if (k < min(totalwords/2, MAXMOMS) - 1)
		    {
			  outfile2 << "," << endl;
		    }
		    else
		    {
			  outfile2 << endl << "];" << endl;
		    }     
      }

	  outfile2 << endl << "var avgamp = " << sqrt(totalamplitudeSquared/(min(totalwords/2, MAXMOMS))) 
		  << ";" << endl;

      outfile2.close();


   delete [] freqs;


}



void WritePage()
{
	
   cout << "Content-type:text/html\r\n\r\n";	
   cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n";
   cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n";
   cout << "<head>\r\n";
   cout << "<style type=\"text/css\">\r\n";
   cout << ".style6 {font-family: Arial, Helvetica, sans-serif; font-size: 18px; }\r\n";
   cout << "</style>\r\n";
   cout << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n";
   cout << "<title>Detropy Results</title>\r\n";
   cout << "<link rel=\"stylesheet\" type=\"text/css\" href=\"../d3LineChart.css\">\r\n";
   cout << "<script src=\"../d3.v2.js\" type=\"text/javascript\"></script>\r\n";
   cout << "<script src=\"../jquery.min.js\" type=\"text/javascript\"></script>\r\n";
   cout << "<script type=\"text/javascript\" src=\"../jquery.tipsy.js\"></script>\r\n";
   cout << "<link href=\"../tipsy.css\" rel=\"stylesheet\" type=\"text/css\" />\r\n";
   cout << "</head>\r\n";
   cout << "<body>\r\n";
   cout << "<p class=\"style6\">Submission processed! If you wish to retrieve the numerical results of the computation,"
        << " click <a href=\"../detropy.json\">here</a> and <a href=\"../moments.json\">here</a>. For your"
        << " convenience I've plotted these below, i.e. the \"Detropy Plot\" and its Fourier spectrum. "
        << "Detropy is a measure of the rareness of a word: common words like \"when\" have low detropy (high frequency of occurrence)"
        << ", whereas rarer words like "
        << " \"quantumchromodynamics\" have higher detropy (low frequency)."
        << " You might recognize detropy as being opposite to entropy, and indeed detropy is the negative entropy of a word, i.e. negative "
        << "logarithm of the"
        << " relative frequency of this word as it appears in literary usage. "
        << " For the purpose of the present application, that is determined by the"
        << " <a href=\"http://storage.googleapis.com/books/ngrams/books/datasetsv2.html\">"
        << "Google 1-gram database </a>"
        << ", a frequency list of English words compiled from roughly 25 billion words logged in over 1 million"
        << " volumes of various English literature"
        << " over the last 500 years).  Note the plots below are SVG plots which can be zoomed in/out (e.g. Ctrl+<mouse wheel>).\r\n";  
   cout << "<div id=\"chart\"></div>\r\n";
   cout << "<script src=\"../detropy.json\" type=\"text/javascript\"></script>\r\n";
   cout << "<script src=\"../d3LineChart.js\" type=\"text/javascript\"></script>\r\n";
   cout << "<p class=\"style6\"> The plot below shows moments describing symmetry of the words in the above Detropy plot, "
        << "i.e. A_N = (2/L)*\\Sum_j {D_j * cos(N Pi j/L)}, 1 <= j <= L (D_j is detropy of the j-th word) which are"
        << " convolutions of the above plot with discrete Fourier factors.\r\n";
   cout << " In other words, the Detropy Plot can be expressed as a sum of cosine functions of the form"
        << " A_N * cos(N Pi x/L),\r\n";
   cout << " where A_N is the amplitude, L is the total number of words in the sample, and x is the ordinal"
        << " position of a word. A_1 is thus a \"dipole moment\", A_2 a \"quadrupole moment\","
        << " and so on. The hypothesis here is that good speech displays at least a few conspicuous moments. </p>\r\n";
   cout << "<div id=\"chart2\"></div>\r\n";
   cout << "<script src=\"../moments.json\" type=\"text/javascript\"></script>\r\n";
   cout << "<script src=\"../d3LineChart2.js\" type=\"text/javascript\"></script>\r\n";
   cout << "<p>&nbsp;</p>\r\n";
   cout << "<p>&nbsp;</p>\r\n";
   cout << "<p align=\"center\" ><a href=\"../detropy.html\" target=\"_self\">Back</a></p>\r\n";
   cout << "</body></html>\r\n";
	
  

}


unsigned int intConvert(string aInput, int i)
{
  char val1 = aInput.at(i+1);
  unsigned int myval1;
  std::stringstream ss1;
  ss1 << val1;
  ss1 >> std::hex >> myval1;

  char val2 = aInput.at(i+2);
  unsigned int myval2;
  std::stringstream ss2;
  ss2 << val2;
  ss2 >> std::hex >> myval2;

  return (16*myval1 + myval2);
  
}

string cleanString(string aInput)
{
	char newstring[MAXSTRING];

	int pos = 0;
	for (int i = 0; i < aInput.length(); i++ )
	{
		if (aInput.at(i) == 37)    // %
		{
			newstring[pos] = intConvert(aInput, i);
			if (newstring[pos] == 10 || newstring[pos] == 13)
			{
	             // treat newline as end of word
				 newstring[pos] = '\0';
				 return newstring;
			}
			else
			{
				pos++;
			}		
			i += 2;
		}
		else
		{
			newstring[pos] = aInput.at(i);
			pos++;
		}
	}
	newstring[pos] = '\0';

	return newstring;
}

	////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) 
{
	


   vector<string> input_words;

 
 
   list<string> theContent = GetContent();
   for (list<string>::const_iterator itr = theContent.begin();
        itr != theContent.end();
        itr++)
   {
      
      istringstream read_ss(*itr);
      string read_s;
      bool firstword;
      int count = 0;
      while (getline(read_ss, read_s, '&'))
      {
         count++;
         if (count == 1)   // this is for the text box
         {
            istringstream read_ss2(read_s);
            string read_s2;
            firstword = true;
            while (getline(read_ss2, read_s2, '+'))
            {
               if (firstword)
               {
                  input_words.push_back(read_s2.substr(11,read_s2.size() - 11));  // chop off the "TextField1="
                  firstword = false;
               }
               else
               {
                  input_words.push_back(read_s2);
               }
            }
         }
      }
   }
 

   
 // here we translate any unicode hex values to ordinary text
   
   vector<string> new_input_words;
   for (vector<string>::iterator it = input_words.begin(); it != input_words.end(); it++)
   {
      new_input_words.push_back(cleanString(*it));   
   }
 


   // write the data files
   google_analyze(new_input_words); 

   // write the output page
   WritePage();



   return 0;


}



