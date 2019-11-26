#ifndef debug_write_iterator_h
#define debug_write_iterator_h

#include "text-fields.h"
#include <string>
#include <iostream>
#include <memory>

class debug_write_iterator {
        
  int count;
  std::ostream *postr;

  public:
    // An output iterator requires these methods:
    /*
      copy constructor.
      assignment copy operator
      destructable
      It can be deferenced as an lvalue:  *iter = t
      Increment
      lvalues are swappable   
     */
    using iterator_category = std::output_iterator_tag;
    using value_type        = std::vector<std::string>;
    using difference_type   = int;
    using reference         = std::vector<std::string>&;
    using pointer           = std::vector<std::string> *;
      
    debug_write_iterator(std::ostream& lhs_ostr) : postr{&lhs_ostr}, count(0) {}
    
    debug_write_iterator(const debug_write_iterator& lhs) : postr{lhs.postr}, count{lhs.count} {}

    ~debug_write_iterator() = default;

    debug_write_iterator& operator=(const debug_write_iterator& lhs) = default;
        
    debug_write_iterator& operator=(const value_type& vec)
    {
       ++count;
       *postr << "line no: " << count << ' ';

       for(auto& str : vec) {

          *postr << str << '|';
       }

       *postr << '\n';

       if ((count % 100) == 0) {

          *postr << "==>\t\t " << count << " lines have been written." << std::endl;

       } else if (count == 1455) {

    	   auto debug = 10;
    	   ++debug;
       }

       return *this;
    }
    
    debug_write_iterator& operator*() noexcept 
    { 
        return *this; 
    }
    debug_write_iterator& operator++() noexcept 
    { 
        return *this; 
    }
    debug_write_iterator& operator++(int) noexcept 
    { 
        return *this; 
    }
    
    int get_write_count() const noexcept { return count; }
};
#endif 
