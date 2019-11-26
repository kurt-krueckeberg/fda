#ifndef  maude_seek_iterator_h
#define  maude_seek_iterator_h

#include <cppconn/connection.h>
#include <string>
#include <fstream>

class maude_seek_iterator : public std::ifstream {

    void seekto_new_records(sql::Connection&) noexcept;

    bool b_initialized = false;
    long int max_mdr_report_key = 0;

 public:
      maude_seek_iterator(const std::string& file_name, sql::Connection& conn) : std::ifstream{file_name}
      {
         seekto_new_records(conn);
      } 
      // Has the same ctors as ifstream and the same operator=() as ifstream
};
#endif
