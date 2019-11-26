#ifndef maude_table_h
#define maude_table_h

#include <string>
#include <vector>

class maude_table { // abstract interfae class

  public:

     virtual bool is_new_record(const std::vector<std::string>& row) = 0;
     virtual bool write(const std::vector<std::string>& row) = 0;
     virtual ~maude_table() noexcept {}
};

#endif
