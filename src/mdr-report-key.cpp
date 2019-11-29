#include <istream>
#include <string>

#include "../include/mdr-rkey.h"

using namespace std;

std::istream& mdr_rkey::read(std::istream& istr) noexcept
{
   string line;
   
   getline(istr, line);
 
   // -1 means skip over the actual regular expression found, just return the tokens, the character strings between re. 
   mdr_rkey_ = ::stoi( line.substr(0, line.find("|")) ); 
 
   return istr;
}
