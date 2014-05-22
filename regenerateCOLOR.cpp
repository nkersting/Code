
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

const int FREQUENCY_BINS = 81;    // binning of the spectrum
const int KEY_RANGE = 32000000;   // maximum expected key value


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


const char* DATADIR = "/home/nkersting/website/public2/";
const char* DATADIR_SPECTRUM = "/home/nkersting/website/spectra.txt";

const char* RGBFILE = "/home/nkersting/website/rgb.json";

const int MAXSTRING = 200;

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
//////////////////////////////////////////////

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

/////////////////////////////////////////

/* A colour system is defined by the CIE x and y coordinates of
   its three primary illuminants and the x and y coordinates of
   the white point. */

struct colourSystem {
    char *name;     	    	    /* Colour system name */
    double xRed, yRed,	    	    /* Red x, y */
           xGreen, yGreen,  	    /* Green x, y */
           xBlue, yBlue,    	    /* Blue x, y */
           xWhite, yWhite,  	    /* White point x, y */
	   gamma;   	    	    /* Gamma correction for system */
};

/* White point chromaticities. */

#define IlluminantC     0.3101, 0.3162	    	/* For NTSC television */
#define IlluminantD65   0.3127, 0.3291	    	/* For EBU and SMPTE */
#define IlluminantE 	0.33333333, 0.33333333  /* CIE equal-energy illuminant */

/*  Gamma of nonlinear correction.

    See Charles Poynton's ColorFAQ Item 45 and GammaFAQ Item 6 at:
    
       http://www.poynton.com/ColorFAQ.html
       http://www.poynton.com/GammaFAQ.html
 
*/

#define GAMMA_REC709	0		/* Rec. 709 */

static struct colourSystem
                  /* Name                  xRed    yRed    xGreen  yGreen  xBlue  yBlue    White point        Gamma   */
    NTSCsystem  =  { "NTSC",               0.67,   0.33,   0.21,   0.71,   0.14,   0.08,   IlluminantC,    GAMMA_REC709 },
    EBUsystem   =  { "EBU (PAL/SECAM)",    0.64,   0.33,   0.29,   0.60,   0.15,   0.06,   IlluminantD65,  GAMMA_REC709 },
    SMPTEsystem =  { "SMPTE",              0.630,  0.340,  0.310,  0.595,  0.155,  0.070,  IlluminantD65,  GAMMA_REC709 },
    HDTVsystem  =  { "HDTV",               0.670,  0.330,  0.210,  0.710,  0.150,  0.060,  IlluminantD65,  GAMMA_REC709 },
    CIEsystem   =  { "CIE",                0.7355, 0.2645, 0.2658, 0.7243, 0.1669, 0.0085, IlluminantE,    GAMMA_REC709 },
    Rec709system = { "CIE REC 709",        0.64,   0.33,   0.30,   0.60,   0.15,   0.06,   IlluminantD65,  GAMMA_REC709 };


//////////////////////////////////
void spectrum_to_xyz(int spectrum[],
                     double& x, double& y, double& z)
{
    int i;
    double lambda, X = 0, Y = 0, Z = 0, XYZ;

    /* CIE colour matching functions xBar, yBar, and zBar for
       wavelengths from 380 through 780 nanometers, every 5
       nanometers.  For a wavelength lambda in this range:

            cie_colour_match[(lambda - 380) / 5][0] = xBar
            cie_colour_match[(lambda - 380) / 5][1] = yBar
            cie_colour_match[(lambda - 380) / 5][2] = zBar

	To save memory, this table can be declared as floats
	rather than doubles; (IEEE) float has enough 
	significant bits to represent the values. It's declared
	as a double here to avoid warnings about "conversion
	between floating-point types" from certain persnickety
	compilers. */

    static double cie_colour_match[81][3] = {
        {0.0014,0.0000,0.0065}, {0.0022,0.0001,0.0105}, {0.0042,0.0001,0.0201},
        {0.0076,0.0002,0.0362}, {0.0143,0.0004,0.0679}, {0.0232,0.0006,0.1102},
        {0.0435,0.0012,0.2074}, {0.0776,0.0022,0.3713}, {0.1344,0.0040,0.6456},
        {0.2148,0.0073,1.0391}, {0.2839,0.0116,1.3856}, {0.3285,0.0168,1.6230},
        {0.3483,0.0230,1.7471}, {0.3481,0.0298,1.7826}, {0.3362,0.0380,1.7721},
        {0.3187,0.0480,1.7441}, {0.2908,0.0600,1.6692}, {0.2511,0.0739,1.5281},
        {0.1954,0.0910,1.2876}, {0.1421,0.1126,1.0419}, {0.0956,0.1390,0.8130},
        {0.0580,0.1693,0.6162}, {0.0320,0.2080,0.4652}, {0.0147,0.2586,0.3533},
        {0.0049,0.3230,0.2720}, {0.0024,0.4073,0.2123}, {0.0093,0.5030,0.1582},
        {0.0291,0.6082,0.1117}, {0.0633,0.7100,0.0782}, {0.1096,0.7932,0.0573},
        {0.1655,0.8620,0.0422}, {0.2257,0.9149,0.0298}, {0.2904,0.9540,0.0203},
        {0.3597,0.9803,0.0134}, {0.4334,0.9950,0.0087}, {0.5121,1.0000,0.0057},
        {0.5945,0.9950,0.0039}, {0.6784,0.9786,0.0027}, {0.7621,0.9520,0.0021},
        {0.8425,0.9154,0.0018}, {0.9163,0.8700,0.0017}, {0.9786,0.8163,0.0014},
        {1.0263,0.7570,0.0011}, {1.0567,0.6949,0.0010}, {1.0622,0.6310,0.0008},
        {1.0456,0.5668,0.0006}, {1.0026,0.5030,0.0003}, {0.9384,0.4412,0.0002},
        {0.8544,0.3810,0.0002}, {0.7514,0.3210,0.0001}, {0.6424,0.2650,0.0000},
        {0.5419,0.2170,0.0000}, {0.4479,0.1750,0.0000}, {0.3608,0.1382,0.0000},
        {0.2835,0.1070,0.0000}, {0.2187,0.0816,0.0000}, {0.1649,0.0610,0.0000},
        {0.1212,0.0446,0.0000}, {0.0874,0.0320,0.0000}, {0.0636,0.0232,0.0000},
        {0.0468,0.0170,0.0000}, {0.0329,0.0119,0.0000}, {0.0227,0.0082,0.0000},
        {0.0158,0.0057,0.0000}, {0.0114,0.0041,0.0000}, {0.0081,0.0029,0.0000},
        {0.0058,0.0021,0.0000}, {0.0041,0.0015,0.0000}, {0.0029,0.0010,0.0000},
        {0.0020,0.0007,0.0000}, {0.0014,0.0005,0.0000}, {0.0010,0.0004,0.0000},
        {0.0007,0.0002,0.0000}, {0.0005,0.0002,0.0000}, {0.0003,0.0001,0.0000},
        {0.0002,0.0001,0.0000}, {0.0002,0.0001,0.0000}, {0.0001,0.0000,0.0000},
        {0.0001,0.0000,0.0000}, {0.0001,0.0000,0.0000}, {0.0000,0.0000,0.0000}
    };

    for (i = 0, lambda = 380; lambda < 780.1; i++, lambda += 5)
    {
        X += spectrum[i] * cie_colour_match[i][0];
        Y += spectrum[i] * cie_colour_match[i][1];
        Z += spectrum[i] * cie_colour_match[i][2];
    }
    XYZ = (X + Y + Z);
    x = X / XYZ;
    y = Y / XYZ;
    z = Z / XYZ;
}

///////////////////////////////////////////

/*                             XYZ_TO_RGB

    Given an additive tricolour system CS, defined by the CIE x
    and y chromaticities of its three primaries (z is derived
    trivially as 1-(x+y)), and a desired chromaticity (XC, YC,
    ZC) in CIE space, determine the contribution of each
    primary in a linear combination which sums to the desired
    chromaticity.  If the  requested chromaticity falls outside
    the Maxwell  triangle (colour gamut) formed by the three
    primaries, one of the r, g, or b weights will be negative. 

    Caller can use constrain_rgb() to desaturate an
    outside-gamut colour to the closest representation within
    the available gamut and/or norm_rgb to normalise the RGB
    components so the largest nonzero component has value 1.
    
*/

void xyz_to_rgb(struct colourSystem *cs,
                double xc, double yc, double zc,
                double *r, double *g, double *b)
{
    double xr, yr, zr, xg, yg, zg, xb, yb, zb;
    double xw, yw, zw;
    double rx, ry, rz, gx, gy, gz, bx, by, bz;
    double rw, gw, bw;

    xr = cs->xRed;    yr = cs->yRed;    zr = 1 - (xr + yr);
    xg = cs->xGreen;  yg = cs->yGreen;  zg = 1 - (xg + yg);
    xb = cs->xBlue;   yb = cs->yBlue;   zb = 1 - (xb + yb);

    xw = cs->xWhite;  yw = cs->yWhite;  zw = 1 - (xw + yw);

    /* xyz -> rgb matrix, before scaling to white. */
    
    rx = (yg * zb) - (yb * zg);  ry = (xb * zg) - (xg * zb);  rz = (xg * yb) - (xb * yg);
    gx = (yb * zr) - (yr * zb);  gy = (xr * zb) - (xb * zr);  gz = (xb * yr) - (xr * yb);
    bx = (yr * zg) - (yg * zr);  by = (xg * zr) - (xr * zg);  bz = (xr * yg) - (xg * yr);

    /* White scaling factors.
       Dividing by yw scales the white luminance to unity, as conventional. */
       
    rw = ((rx * xw) + (ry * yw) + (rz * zw)) / yw;
    gw = ((gx * xw) + (gy * yw) + (gz * zw)) / yw;
    bw = ((bx * xw) + (by * yw) + (bz * zw)) / yw;

    /* xyz -> rgb matrix, correctly scaled to white. */
    
    rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
    gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
    bx = bx / bw;  by = by / bw;  bz = bz / bw;

    /* rgb of the desired point */
    
    *r = (rx * xc) + (ry * yc) + (rz * zc);
    *g = (gx * xc) + (gy * yc) + (gz * zc);
    *b = (bx * xc) + (by * yc) + (bz * zc);
}
////////////////////////////////////////
/*  	    	    	    NORM_RGB

    Normalise RGB components so the most intense (unless all
    are zero) has a value of 1.
    
*/

void norm_rgb(double *r, double *g, double *b)
{
#define Max(a, b)   (((a) > (b)) ? (a) : (b))
    double greatest = Max(*r, Max(*g, *b));
    
    if (greatest > 0) {
    	*r /= greatest;
	*g /= greatest;
	*b /= greatest;
    }
#undef Max
}
////////////////////////////////////

/*                          CONSTRAIN_RGB

    If the requested RGB shade contains a negative weight for
    one of the primaries, it lies outside the colour gamut 
    accessible from the given triple of primaries.  Desaturate
    it by adding white, equal quantities of R, G, and B, enough
    to make RGB all positive.  The function returns 1 if the
    components were modified, zero otherwise.
    
*/

int constrain_rgb(double *r, double *g, double *b)
{
    double w;

    /* Amount of white needed is w = - min(0, *r, *g, *b) */
    
    w = (0 < *r) ? 0 : *r;
    w = (w < *g) ? w : *g;
    w = (w < *b) ? w : *b;
    w = -w;

    /* Add just enough white to make r, g, b all positive. */
    
    if (w > 0) {
        *r += w;  *g += w; *b += w;
        return 1;                     /* Colour modified to fit RGB gamut */
    }

    return 0;                         /* Colour within RGB gamut */
}



//////////////////////
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


vector <int> findSynsets(std::string& word, std::map<std::string, vector <int> >& WordMap)
{
  std::map<std::string, vector <int> >::iterator iter = WordMap.find(word);
  if (iter != WordMap.end()) 
    { 
      return iter->second;  // matching set of synsets returned
    }
  else                     // try looking up without last character
    {                        // takes care of most plurals and final punctuation
      std::string short_word = word.substr(0,word.size() - 1);
      std::map<std::string, vector <int> >::iterator iter = WordMap.find(short_word);
      if (iter != WordMap.end())
	{
	  return iter->second;  // matching set of synsets returned
	}
      else
	{

	  // more plural handling:
	  // if last two letters are "es" try looking up without last two characters
	  if (word[word.size()-2] == 'e' && word[word.size()-1] == 's')
	    {
	      std::map<std::string, vector <int> >::iterator iter = WordMap.find(word.substr(0,word.size()-2));
	      if (iter != WordMap.end())
		{
		  return iter->second;  // matching set of synsets returned
		}
	      else
		{
		  // if last three letters are "ies" try replacing these with "y"
		  if (word[word.size()-3] == 'i')
		    {
		      string new_word = word.substr(0,word.size()-3);
		      new_word.append("y");
		      std::map<std::string, vector <int> >::iterator iter = WordMap.find(new_word);
		      if (iter != WordMap.end())
			{
			  return iter->second;  // matching set of synsets returned
			}
		    }
		}
	    }


	  return hash_x(word.c_str());     // if we get here then a hash is needed
	}                                  // e.g. some specialty words or proper nouns
    }
}



void  populateKeyMap(std::map<int, vector <std::string> > &KeyMap, 
		     std::map<std::string, vector <int> > &WordMap, 
		     vector <std::string> &input_words)
{

  vector <int> keys1;
  vector <int> keys2;

  for (int i = 0; i < input_words.size(); i++)
    {
      keys1 = findSynsets(input_words.at(i), WordMap);
      for (int j = i+1; j < input_words.size(); j++)
	{
	  keys2 = findSynsets(input_words.at(j), WordMap);
	  for (vector<int>::iterator it1 = keys1.begin(); it1 != keys1.end(); it1++)
	    {
	      for (vector<int>::iterator it2 = keys2.begin(); it2 != keys2.end(); it2++)
		{
		  KeyMap[(*it1 + *it2)].push_back(input_words.at(i));
		  KeyMap[(*it1 + *it2)].push_back(input_words.at(j));
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


void WritePage()
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
    "<a href=\"../public\">public2/ directory</a>." <<
    "Click on the filenames below to try a (confidential) match on the server.</p>\r\n";
  cout << "<p>&nbsp;</p>\r\n";

  // now write the table

  
  cout << "<table width=\"1100\" border=\"1\">\r\n";
  cout << "<tr>\r\n";
  cout << "<td width=\"500\" valign=\"top\">\r\n";

  cout << "<table width=\"500\" border=\"1\">\r\n";
  cout << "<tr>\r\n";
  cout << "<td width=\"70\" align=\"center\">#</td>\r\n";
  cout << "<td width=\"70\" align=\"center\">X,Y</td>\r\n";
  cout << "<td width=\"360\" align=\"center\">Contribution</td>\r\n";
  cout << "</tr>\r\n";

  ifstream specfile;
  specfile.open(DATADIR_SPECTRUM);
  if (specfile.is_open()) 
  {
     int count = 0;
     double x,y;
     int r,g,b;
     int numkeys;
     string contribution;
     while ( !specfile.eof())
     {
        count++;
        specfile >> contribution >> numkeys >> x >> y >> r >> g >> b;
        cout << "<tr>\r\n";
        cout << "<td align=\"center\">" << count  <<  "</td>\r\n";
        cout << "<td align=\"center\">" << x << ", " << y  <<  "</td>\r\n";
        cout << "<td align=\"center\" >\r\n";
        cout << "<p><a href=\"../match2.html?matchfile="  << contribution  << "\" title=\"Match Form\" target=\"_blank\">" 
             << contribution << "</a></p>" << endl; 
        cout << "</td>\r\n";
        cout << "</tr>\r\n";
     }
    }
 
  cout << "</table>\r\n"; 
  cout << "</td>\r\n";
  cout << "<td width=\"600\" align=\"center\" valign=\"top\">\r\n";
  cout << "<div id=\"chart\"></div>\r\n";
  cout << "<script src=\"../rgb.json\" type=\"text/javascript\"></script>\r\n";
  cout << "<script type=\"text/javascript\" src=\"../rgb.js\"></script>\r\n";
  cout << "</td>\r\n";
  cout << "</tr>\r\n";
  cout << "</table>\r\n"; 

  cout << "<p>&nbsp;</p>\r\n";
  cout << "<p align=\"center\"><span class=\"style1 style5 style4\"><a href=\"../index3.html\" target=\"_self\">back</a></span></p>\r\n";
  cout << "</body>\r\n";
  cout << "</html>\r\n";

}

//////////////////////////////
void WriteErrorPage()
{
  cout << "Content-type:text/html\r\n\r\n";
  cout << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n";
  cout << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n";
  cout << "<head>\r\n";
  cout << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n";
  cout << "<title>Error</title>\r\n";
  cout << "</head>\r\n";
  cout << "<body>\r\n";
  cout << "<p>Submission Error: Sentence too short (please re-enter with 2 or more words)</p>\r\n";
  
  cout << "<p>&nbsp;</p>\r\n";
  cout << "<p align=\"center\"><span class=\"style1 style5 style4\"><a href=\"../index3.html\" target=\"_self\">back</a></span></p>\r\n";
  cout << "</body>\r\n";
  cout << "</html>\r\n";

}

void WriteJSON()
{
  
  // open output file
  ofstream outfile;
  outfile.open(RGBFILE);   

  outfile << "var  json = {" <<
    "\"name\": \"groups\"," <<
    "\"children\": [" <<
    "{" <<
    " \"name\": \"analytics\"," <<
    " \"children\": [        " << 
    "{" <<
    "\"name\": \"graphs\"," <<
    " \"children\": [" << endl;
              


  ifstream specfile;
  specfile.open(DATADIR_SPECTRUM);
  if (specfile.is_open()) 
  {
     int count = 0;
     double x,y;
     int r,g,b;
     int numkeys;
     string contribution;
     while ( !specfile.eof())
     {
        count++;
        specfile >> contribution >> numkeys >> x >> y >> r >> g >> b;
        outfile << "{" <<
	"\"name\": \"" << count  << "\"," << endl <<
	"\"filename\": \"" << contribution  << "\"," << endl <<
	"\"NumKeys\":" << numkeys << "," << endl << 
	"\"CIEx\":" << x << "," << endl << 
	"\"CIEy\":" << y << "," << endl << 
	"\"red\":" << r << "," << endl << 
	"\"blue\":" << g << "," << endl << 
	"\"green\":" << b <<  "}" << endl ; 
        if (!specfile.eof()) outfile << "," << endl;
     }
/*     outfile << "{" <<
	"\"name\": \"" << "x"  << "\"," << endl <<
	"\"filename\": \"" << "base"  << "\"," << endl <<
	"\"NumKeys\":" << 0 << "," << endl << 
	"\"CIEx\":" << 0 << "," << endl << 
	"\"CIEy\":" << 0 << "," << endl << 
	"\"red\":" << 0 << "," << endl << 
	"\"blue\":" << 0 << "," << endl << 
	"\"green\":" << 0 <<  "}" << endl ; 
*/
     outfile << "]} ]} ] }";
  }

  specfile.close();
  outfile.close();

}



////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
   /*  

  //cout << c_ContentHeader;
  //cout << "<html><body>" << endl;
  //cout << "The content Length is: " << GetContentLength() << "<br>" << endl;

  //cout << "The Content is: <br><pre>" << endl;

  vector<string> input_words;
  string userID("");


  list<string> theContent = GetContent();
  for (list<string>::const_iterator itr = theContent.begin();
       itr != theContent.end();
       itr++)
    {
      // cout << (*itr) << endl;


      istringstream read_ss(*itr);
      string read_s;
      bool firstword;
      int count = 0;
      while (getline(read_ss, read_s, '&'))
	{
	  count++;
	  if (count == 1)   // this is for the sentence line
	    {
	      istringstream read_ss2(read_s);
	      string read_s2;
	      firstword = true;
	      while (getline(read_ss2, read_s2, '+'))
		{
		  if (firstword)
		    {
		      std::transform(read_s2.begin(), read_s2.end(), read_s2.begin(), ::tolower);  //convert to lowercase
		      input_words.push_back(read_s2.substr(11,read_s2.size() - 11));  // chop off the "TextField1="
		      firstword = false;
		    }
		  else
		    {
		      std::transform(read_s2.begin(), read_s2.end(), read_s2.begin(), ::tolower);  //convert to lowercase
		      input_words.push_back(read_s2);
		    }
		}
	    }
	  else if (count == 2)         // this is for the ID line
	    {
	      istringstream read_ss2(read_s);
	      string read_s2;
	      firstword = true;
	      while (getline(read_ss2, read_s2, '+'))
		{
		  if (firstword)
		    {
		      userID.append(read_s2.substr(11,read_s2.size() - 11));  // chop off the "TextField1="
		      firstword = false;
		    }
		  else
		    {
		      userID.append("_");
		      userID.append(read_s2);
		    }
		}
	    }
	}




    }




  vector<string> new_input_words;
  for (vector<string>::iterator it = input_words.begin(); it != input_words.end(); it++)
  {
    new_input_words.push_back(cleanString(*it));   
  }

  string newUserID = cleanString(userID);

  /////////////////////////////////////
  /// Below we compute the key file
  ////////////////////////////////////


  // read in the  "wordsets.txt"
  ifstream word_synset_file;
  word_synset_file.open ("wordsets.txt");


  // fill in the word-synset map
  // cout << "This is the encryption code." << endl;
  // cout << "Loading dictionary, please wait ..." << endl;
  std::map<std::string, vector <int> > WordMap;
  string line;
  while (getline(word_synset_file, line))
    {
      istringstream read_ss(line);
      string read_s;
      int firstread = 1;
      string word = "";
      while (getline(read_ss, read_s, ' '))    // FIXME: whitespace, not just one space
	{
	  if (firstread == 1 )
	    {
	      word = read_s;
	      firstread = 0;
	    }
	  else
	    {
	      WordMap[word].push_back(atoi(read_s.c_str()));
	    }
	}

    }

   */    


// read in all the files in directory

   std::map<string, set<int> > keyLists;
   readFilesIntoMap(keyLists);   

   int spectrum[FREQUENCY_BINS];           

   for (map<string, set<int> >::iterator it = keyLists.begin();
        it != keyLists.end(); ++it)
   {

      for (int i = 0; i < FREQUENCY_BINS; i++)
      {
         spectrum[i] = 0;
      }

      for (set<int>::iterator it2 = (it->second).begin();
	   it2 != (it->second).end(); ++it2) 
      {
         int Key = *it2;
         if (Key > 0 && Key < KEY_RANGE)
         {
            spectrum[(Key*FREQUENCY_BINS)/KEY_RANGE]++;
         }
         else
         {
            spectrum[(int)(log(abs(Key)))]++;    // keys from non-dict words are collected in the lowest bins
         }
      }
   
      // write the spectrum info to file

      struct colourSystem *cs = &SMPTEsystem;
      double x,y,z,r,g,b;

      spectrum_to_xyz(spectrum, x, y, z);
      xyz_to_rgb(cs, x, y, z, &r, &g, &b);
                     
      constrain_rgb(&r, &g, &b);
      norm_rgb(&r, &g, &b);      


      string spectrumFilename(DATADIR_SPECTRUM);
      fstream filestr;

      filestr.open (spectrumFilename.c_str(), fstream::out | fstream::app);

      filestr << std::endl << 
         it->first << " " << (it->second).size() << " " << x << " " << y << " " 
              << (int)(255*r) << " " << (int)(255*g) << " " << (int)(255*b);

      filestr.close();


   }

        


//    WriteJSON();    // Write the JSON file used to make D3.js Bubble Chart


//    WritePage(); 



  return 0;






}


