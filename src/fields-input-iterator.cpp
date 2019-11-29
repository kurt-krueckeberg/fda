#include "fields-input-iterator.h"
#include "token-iter.h"
#include "mdr-rkey.h"

#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>

bool fields_input_iterator::b_max_found = false;
unsigned long fields_input_iterator::max_mdr_rkey = 0;

using namespace std;
using namespace sql;

unsigned int fields_input_iterator::get_max_mdr_rkey(sql::Connection& conn) noexcept
{
   unsigned max_mdr_rkey = 0;

   unique_ptr<Statement> stmt { conn.createStatement() };

   // Are there any medwatch_report records? ...
   unique_ptr<ResultSet> rs { stmt->executeQuery("SELECT count(*) as total FROM medwatch_report") };

   rs->first();

   if (static_cast<int>( rs->getInt(1) ) != 0) { //...if yes, select max(mdr_rkey).

      rs.reset( std::move( stmt->executeQuery("SELECT max(mdr_rkey) as max_mdr_rkey FROM medwatch_report") ));

      rs->first();

      max_mdr_rkey = rs->getUInt64(1);
   }

   return max_mdr_rkey;
}

void fields_input_iterator::advance(sql::Connection& conn) 

{
   if (!fields_input_iterator::b_max_found) {

        fields_input_iterator::max_mdr_rkey = fields_input_iterator::get_max_mdr_rkey(conn); 
        fields_input_iterator::b_max_found = true;
   }

   // Advance until predicate is true.
   auto predicate = [] (unsigned input_mdr)
                    { 
                       return input_mdr > fields_input_iterator::max_mdr_rkey;
                    };

   find_if(istream_iterator<mdr_rkey>(*pistr), std::istream_iterator<mdr_rkey>{}, predicate);
}

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
  
         *vec_iter = *field_iter; // *iter returns: std::string_view.
        ++vec_iter;
  
         if (++indecies_iter == pindexes->cend()) break; // If we have all the fields, stop fetching.
      }
    }
}
