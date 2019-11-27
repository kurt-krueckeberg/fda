#ifndef table_write_iterator_h
#define table_write_iterator_h

#include "maude-table.h"
#include <vector>
#include <string>
#include <iterator>
#include <memory>

class table_write_iterator { 
    
  maude_table *tbl_ptr; // base table class pointer
  int count;
  
  public:
    // An output iterator requires these methods:
    using iterator_category = std::output_iterator_tag;
    using difference_type   = std::ptrdiff_t; 
    using value_type = const std::vector<std::string>;
    using reference  = value_type&;
    using pointer   = value_type*;
      
    table_write_iterator(maude_table& lhs) : tbl_ptr{&lhs}, count(0) {}
    
    table_write_iterator(const table_write_iterator& lhs) : tbl_ptr{lhs.tbl_ptr}, count{lhs.count} {}  

    table_write_iterator() : tbl_ptr{nullptr} {}

    virtual ~table_write_iterator() {}

    table_write_iterator& operator=(const table_write_iterator& lhs) = default;
        
    table_write_iterator& operator=(reference row) // Note: reference <--> 'std::vector<std::string>&'
    {
       ++count; 
       
       tbl_ptr->write(row);

       if ((count % 100) == 0) {
          std::cout << count << " lines have been written." << std::endl;
       }
       return *this;
    }
    
    table_write_iterator& operator*() noexcept { return *this; }
    table_write_iterator& operator++() noexcept { return *this; }
    table_write_iterator& operator++(int) noexcept { return *this; }

    int get_write_count() const noexcept { return count; }
};
#endif 
