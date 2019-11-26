#include "text-fields.h"
#include "token-iter.h"

using namespace std;

istream& text_fields::read(istream& istr) noexcept
{
  getline(istr, line);
  
  token_iterator<'|'> field_iter{line}, end{};
 
  auto indecies_iter = indecies.cbegin();

  auto vec_iter = vec.begin();
  
  for(auto cur_field_index = 0; field_iter != end; ++field_iter, ++cur_field_index) { // While still more fields... 
      
    if (cur_field_index == *indecies_iter) { // If the next field equals the current index, save the field

       *vec_iter = *field_iter; // *iter returns: std::string_view.
      ++vec_iter;

       if (++indecies_iter == indecies.cend()) break; // If we have all the fields, stop fetching.
    }
  }
  return istr;
}
