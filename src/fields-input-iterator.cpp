#include "fields-input-iterator.h"
#include "token-iter.h"

using namespace std;
/*
void fields_input_iterator::read(istream& istr, const vector<int>& indexes) noexcept
{
    auto& vec = *pvec;
  
    string line;
  
    getline(istr, line);
    
    token_iterator<'|'> field_iter{line}, end{};
   
    auto indecies_iter = indexes.cbegin();
  
    auto vec_iter = vec.begin();
    
    auto debug = vec.size();

    for(auto cur_field_index = 0; field_iter != end; ++field_iter, ++cur_field_index) { // While still more fields... 
        
      if (cur_field_index == *indecies_iter) { // If the next field equals the current index, save the field
  
         *vec_iter = *field_iter; // *iter returns: std::string_view.
        ++vec_iter;
  
         if (++indecies_iter == indexes.cend()) break; // If we have all the fields, stop fetching.
      }
    }
}
*/
void fields_input_iterator::read_() noexcept
{
    auto& vec = *pvec;
  
    string line;
  
    getline(*pistr, line);
    
    token_iterator<'|'> field_iter{line}, end{};
   
    auto indecies_iter = pindexes->cbegin();
  
    auto vec_iter = vec.begin();
    
    auto debug = vec.size();

    for(auto cur_field_index = 0; field_iter != end; ++field_iter, ++cur_field_index) { // While still more fields... 
        
      if (cur_field_index == *indecies_iter) { // If the next field equals the current index, save the field
  
         *vec_iter = *field_iter; // *iter returns: std::string_view.
        ++vec_iter;
  
         if (++indecies_iter == pindexes->cend()) break; // If we have all the fields, stop fetching.
      }
    }
}
