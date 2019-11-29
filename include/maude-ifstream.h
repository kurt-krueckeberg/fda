#ifndef  maude_ifstream_h
#define  maude_ifstream_h

#include <cppconn/connection.h>
#include <string>
#include <fstream>
#include <iterator>

#include "mdr-rkey.h"

class maude_ifstream : public std::ifstream {

    //--void seekto_new_records(sql::Connection&) noexcept;

    sql::Connection& conn;

    static unsigned int get_max_mdr_rkey(sql::Connection& conn) noexcept;

    static bool b_initialized;
    static unsigned long max_mdr_rkey;

 public:

      maude_ifstream(const std::string& file_name, sql::Connection& in_conn) : std::ifstream{file_name}, conn{in_conn}
      {
         if (!maude_ifstream::b_initialized) {

              maude_ifstream::max_mdr_rkey = maude_ifstream::get_max_mdr_rkey(conn); 
              b_initialized = true;
         }
 
         // Advance until predicate is true.
         auto predicate = [] (unsigned input_mdr)
                          { 
                             return input_mdr > maude_ifstream::max_mdr_rkey;
                          };

         find_if(std::istream_iterator<mdr_rkey>{*this}, std::istream_iterator<mdr_rkey>{}, predicate);
     } 

      maude_ifstream(const maude_ifstream&) = delete; 
      // Has the same ctors as ifstream and the same operator=() as ifstream
};
#endif
