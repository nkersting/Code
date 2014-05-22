


#include "groups.h"

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


using namespace std;



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


const char* DATADIR = "/home/nkersting/website/public/";

const char* GROUPSFILE = "/home/nkersting/website/groups.json";

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


////////////////////////////////////////////////////////////////////////
// -- REPOIRE FUNCTIONS --


vector <int> hash_x(const char *str)
{
  vector <int> synsets;         // actually a vector of just one int
  unsigned long hash = 5381;
  int c;
  
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  
  synsets.push_back((int)hash);
  return synsets;
}


vector <int> findSynsets(std::string& word, std::map<int, vector <int> >& SynMap,
			 std::map<std::string, vector <int> >& WordMap)
{
  std::map<std::string, vector <int> >::iterator iter = WordMap.find(word);
  if (iter != WordMap.end()) 
    {
      vector <int> first_and_second_order_synsets;
      for (vector<int>::iterator iter2 = (iter->second).begin(); // loop over first order
	   iter2 != (iter->second).end(); iter2++)  
	{
	  first_and_second_order_synsets.push_back(*iter2);
	  if (SynMap.find(*iter2) != SynMap.end())
	    {
	      for (vector<int>::iterator iter3 = ((SynMap.find(*iter2))->second).begin();
		   iter3 != ((SynMap.find(*iter2))->second).end(); iter3++)  // loop over second order
		{
		  first_and_second_order_synsets.push_back(*iter3);
		}
	    }
	}
      return first_and_second_order_synsets;   // matching set of synsets returned
    }
  else                     // try looking up without last character
    {                        // takes care of most plurals and final punctuation
      std::string short_word = word.substr(0,word.size() - 1);
      std::map<std::string, vector <int> >::iterator iter = WordMap.find(short_word);
      if (iter != WordMap.end())
	{
	  vector <int> first_and_second_order_synsets;
	  for (vector<int>::iterator iter2 = (iter->second).begin(); // loop over first order
	       iter2 != (iter->second).end(); iter2++)
	    {
	      first_and_second_order_synsets.push_back(*iter2);
	      if (SynMap.find(*iter2) != SynMap.end())
		{    
		  for (vector<int>::iterator iter3 = (SynMap.find(*iter2)->second).begin();
		       iter3 != (SynMap.find(*iter2)->second).end(); iter3++)  // loop over second order
		    {
		      first_and_second_order_synsets.push_back(*iter3);
		    }
		}
	    }
	  return first_and_second_order_synsets;   // matching set of synsets returned
	}
      else
	{
	  return hash_x(word.c_str());     // if we get here then a hash is needed
	}                                  // e.g. some specialty words or proper nouns
    }
}


void  populateKeyMap(std::map<int, vector <std::string> > &KeyMap, 
		     std::map<int, vector <int> > &SynMap,
		     std::map<std::string, vector <int> > &WordMap, 
		     vector <std::string> &input_words)
{

  vector <int> keys1;
  vector <int> keys2;
  vector <int> keys3;

  for (int i = 0; i < input_words.size(); i++)
    {
      keys1 = findSynsets(input_words.at(i), SynMap, WordMap);
      for (int j = i+1; j < input_words.size(); j++)
	{
	  keys2 = findSynsets(input_words.at(j), SynMap, WordMap);
	  for (int k = j+1; k < input_words.size(); k++)
	    {
	      keys3 = findSynsets(input_words.at(k), SynMap, WordMap);

	      for (vector<int>::iterator it1 = keys1.begin(); it1 != keys1.end(); it1++)
		{
		  for (vector<int>::iterator it2 = keys2.begin(); it2 != keys2.end(); it2++)
		    {
		      for (vector<int>::iterator it3 = keys3.begin(); it3 != keys3.end(); it3++)
			{
			  KeyMap[(*it1 + *it2 + *it3)].push_back(input_words.at(i));
			  KeyMap[(*it1 + *it2 + *it3)].push_back(input_words.at(j));
			  KeyMap[(*it1 + *it2 + *it3)].push_back(input_words.at(k));
			}
		    }

		}
	      
	    }
	}
    }


  return;

}  




   

//////////////////////////////////////////
void RepoireGroup::ShowMembers()
{
  for (vector<string>::iterator it = mKeyfileList.begin(); it != mKeyfileList.end(); it++)
    {
      cout << "<p><a href=\"../match.html?matchfile="  << *it  << "\" title=\"Match Form\" target=\"_blank\">" << *it << "</a></p>" << endl;
    }
}
//////////////////////////////////////////
void RepoireGroup::AddMember(string newMember)
{
  mKeyfileList.push_back(newMember);
}
//////////////////////////////////////////////

void readFilesIntoMap(std::map<string, set<int> >& keyLists)
{
  DIR *pDIR;
  struct dirent *entry;
  if( pDIR=opendir(DATADIR) )
    {
      while(entry = readdir(pDIR))
	{
	  if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
	    {
	      //     cout << "reading " << entry->d_name << " ... \n";

	      ifstream keyfile;
	      string filepath = DATADIR;
	      filepath.append(entry->d_name);
	      keyfile.open(filepath.c_str());
	      set <int> keylist;
	      int keyvalue;
	      while (!keyfile.eof())
		{
		  keyfile >> keyvalue;
		  keylist.insert(keyvalue);
		}
	      keyfile.close();
	      std::pair <string, set<int> > newPair (entry->d_name, keylist);
	  keyLists.insert(newPair);
	}
    }
}
closedir(pDIR);
}
///////////////////////////////////
bool CompareToAddToGroup(string key, std::map<string, set<int> >& keyListsCopy, vector <RepoireGroup>& Groups, float threshold)
{
  
  float firstPercent = 0;
  float secondPercent = 0;
  set<int> commonKeys;
  bool addedToGroup = false;
   
   
  for (vector <RepoireGroup>::iterator group = Groups.begin(); group != Groups.end(); group++)
    {
      commonKeys.clear();
      for (set<int>::const_iterator it = keyListsCopy[key].begin(); it!= keyListsCopy[key].end(); it++)
	{
	  if ((group->mCommonKeys).find(*it) !=  (group->mCommonKeys).end()) commonKeys.insert(*it);
	}

      firstPercent = 100.0*commonKeys.size()/keyListsCopy[key].size();
      secondPercent = (group->mIntegrity)*commonKeys.size()/(group->mCommonKeys).size(); 

      if (firstPercent >= threshold  && secondPercent >= threshold) 
	{
	  group->mCommonKeys = commonKeys;
	  group->AddMember(key);
	  group->mIntegrity = min(firstPercent, secondPercent);
	  addedToGroup = true;
	}
 
    }  
  return addedToGroup;
}
////////////////////////////////////

void SeedNewGroup(std::string key, std::set<int> list, vector <RepoireGroup>& Groups)
{
  set<int> commonKeys;
  vector<string> memberKeys;
  memberKeys.push_back(key);
  RepoireGroup rg(list, memberKeys, 100, Groups.size() + 1);   // new group has 100% integrity
  Groups.push_back(rg);
}
/////////////////////////////////////////////



void WritePage(vector <RepoireGroup> Groups, float threshold)
{
  cout << "Content-type:text/html\r\n\r\n";
  cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n";
  cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n";
  cout << "<head>\r\n";
  cout << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n";
  cout << "<title>PCI Groups</title>\r\n";
  cout << "<script type=\"text/javascript\" src=\"../d3.v2.js\"></script>\r\n";
  cout << "<link type=\"text/css\" rel=\"stylesheet\" href=\"../bubble.css\"/>\r\n";
  cout << "</head>\r\n";
  cout << "<body>\r\n";
cout << "<p>All contributions are accessible in the " <<
    "<a href=\"../public\">public/ directory</a>, which are available" <<
    " for personal download to try individual matches with suitable matching code (please contact nkersting@princeton.com for source)" <<
    " together with the <a href=\"../wordsets.txt\">thesaurus</a>." <<
    " You may also click on the filenames below to try a (confidential) match on the server which will quantify the closeness of match.</p>\r\n";
  cout << "<p>&nbsp;</p>\r\n";

  cout << "<form action=\"/cgi-bin/group.cgi\" method=\"post\" name=\"GroupForm\" >\r\n";
  cout << "<p>Contributions currently belong to the following groups, based on a threshold commonality percentage of \r\n";
  cout << "<input name=\"TextField1\" type=\"text\" value=\"" << threshold << "\" size=\"5\" maxlength=\"5\" />\r\n";
  cout << "%.</p>\r\n";
  cout << "<td width=\"93\"><input type=\"submit\" name=\"recalc\" value=\"Click to Refresh\" /></td>\r\n";
  cout << "</form>\r\n";


  // now write the Groups table
  cout << "<table width=\"1100\" border=\"1\">\r\n";
  cout << "<tr>\r\n";
  cout << "<td width=\"500\" valign=\"top\">\r\n";

  cout << "<table width=\"500\" border=\"1\">\r\n";
  cout << "<tr>\r\n";
  cout << "<td width=\"70\" align=\"center\">Group #</td>\r\n";
  cout << "<td width=\"70\" align=\"center\">% Integrity</td>\r\n";
  cout << "<td width=\"360\" align=\"center\">Contributions</td>\r\n";
  cout << "</tr>\r\n";

  for (vector <RepoireGroup>::iterator it = Groups.begin(); it != Groups.end(); it++)
    {
      cout << "<tr>\r\n";
      cout << "<td align=\"center\">" << (*it).GetID()  <<  "</td>\r\n";
      cout << "<td align=\"center\">" << (*it).mIntegrity  <<  "%</td>\r\n";
      cout << "<td align=\"center\" >\r\n";
      (*it).ShowMembers();
      cout << "</td>\r\n";
      cout << "</tr>\r\n";
    }
 
  cout << "</table>\r\n"; 
  cout << "</td>\r\n";
  cout << "<td width=\"600\" align=\"center\" valign=\"top\">\r\n";
  cout << "<div id=\"chart\"></div>\r\n";
  cout << "<script src=\"../groups.json\" type=\"text/javascript\"></script>\r\n";
  cout << "<script type=\"text/javascript\" src=\"../goodbubble.js\"></script>\r\n";
  cout << "</td>\r\n";
  cout << "</tr>\r\n";
  cout << "</table>\r\n"; 

  cout << "<p>&nbsp;</p>\r\n";
  cout << "<p align=\"center\"><span class=\"style1 style5 style4\"><a href=\"../index.html\" target=\"_self\">back</a></span></p>\r\n";
  cout << "</body>\r\n";
  cout << "</html>\r\n";

}


void WriteJSON(vector <RepoireGroup> Groups)
{
  
  // open output file
  ofstream outfile;
  outfile.open(GROUPSFILE);   

  outfile << "var  json = {" <<
    "\"name\": \"groups\"," <<
    "\"children\": [" <<
    "{" <<
    " \"name\": \"analytics\"," <<
    " \"children\": [        " << 
    "{" <<
    "\"name\": \"graphs\"," <<
    " \"children\": [" << endl;
              

  int count = 0;
  for (vector <RepoireGroup>::iterator it = Groups.begin(); it != Groups.end(); it++)
    {
      count++;
      outfile << "{" <<
	"\"name\": \"" << (*it).GetID()  << "\"," << endl <<
	"\"size\":" << (*it).GetUsers() << "," << endl << 
	"\"integrity\":" << floor((*it).mIntegrity) << "}" << endl ; 

      if (count < Groups.size())
	{
	  outfile << "," << endl;
	}

    }

  outfile << "]} ]} ] }";


}

////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{


  float thresholdPercent = 30.0;     // percent agreement needed to be included in a group
 

  list<string> theContent = GetContent();
  for (list<string>::const_iterator itr = theContent.begin();
       itr != theContent.end();
       itr++)
    {

      istringstream read_ss(*itr);
      string read_s;
      int count = 0;
      while (getline(read_ss, read_s, '&'))
	{
	  count++;
	  if (count == 1)   // this is for the % line
	    {
	      istringstream read_ss2(read_s);
	      string read_s2;
	      getline(read_ss2, read_s2, '+');
	      thresholdPercent = atof((read_s2.substr(11,read_s2.size() - 11)).c_str());  // chop off the "TextField1="
	    }
	}

    }






  //////////////////////////
  // Below we compute groups for a default threshold
  //////////////////////////////////////////



  std::map<string, set<int> > keyLists;      // key is the filename, set is all the keys
  vector <RepoireGroup> Groups;
  vector <string> deleteList;
  

  
  keyLists.clear();
  Groups.clear();
    
  // read keylists from directory, and
  // for each keylist, fill a vector

  
  readFilesIntoMap(keyLists);
   

  for (std::map<string, set<int> >::iterator key_it = keyLists.begin(); 
       key_it != keyLists.end(); key_it++)
    {
 
      //first check whether keylist can belong to an already existing group
      if (CompareToAddToGroup(key_it->first, keyLists, Groups, thresholdPercent))
	{
	  continue;
	}
      else
	{
	  // make a new group consisting of just this keylist
	  SeedNewGroup(key_it->first, key_it->second, Groups);
	}

    }





  WriteJSON(Groups);    // Write the JSON file used to make D3.js Bubble Chart

   
  WritePage(Groups, thresholdPercent);     // Write all the text of the page, including the list of groups








  return 0;







}
