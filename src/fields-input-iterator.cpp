#include "fields-input-iterator.h"
#include "token-iter.h"
#include "mdr-rkey.h"

#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>

using namespace std;
using namespace sql;

void fields_input_iterator::read_() noexcept
{
    auto& vec = *pvec;
  
    string line;
  
    getline(*pistr, line);
    
    token_iterator<'|'> field_iter{line}, end{};
   
    auto indecies_iter = pindexes->cbegin();
  
    auto vec_iter = vec.begin();
    
    for(auto cur_field_index = 0; field_iter != end; ++field_iter, ++cur_field_index) { // While still more fields... 
        
      if (cur_field_index == *indecies_iter) { // If the next field equals the current index, save the field
  
         *vec_iter = *field_iter; // Insert next string in vector. *iter returns: std::string_view. 
        ++vec_iter;
  
         if (++indecies_iter == pindexes->cend()) break; // If we have all the fields, stop fetching.
      }
    }
}
