#ifndef fields_input_iterator_h
#define fields_input_iterator_h

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

#include <cppconn/connection.h>

#include "mdr-rkey.h"

// Input iterator that extracts an exported maude table's columns/fields into a vector, row-by-row
// as the exported table is read line-by-line.
class fields_input_iterator  {
        
  std::istream *pistr;

  const std::vector<int> *pindexes;

  std::shared_ptr< std::vector<std::string> > pvec;

  bool ok;

  void read_() noexcept;

  void read() noexcept
  {
      // If pistr or *pistr are nullptr, we are done iterating. 
      ok = (pistr && *pistr) ? true : false;

      if (ok) {
    	  read_();
	  ok = *pistr ? true : false;
      }
  }

  void advance(unsigned int max_mdr_rkey); 

  public:

  using iterator_category = std::input_iterator_tag;
  using value_type        = std::vector<std::string>;
  using difference_type   = int;
  using reference         = std::vector<std::string>&;
  using pointer           = std::vector<std::string> *;


/*;
Properties of an  Input Iterator                          Valid Expressions Required of an Input Iterator
--------------------------------------------------------+-----------------------------------------------

Is copy-constructible, copy-assignable and destructible	            X b(a);
                                                                    b = a;
Can be compared for equivalence using the 
equality/inequality operators (meaningful if both
iterators are be in domain).	                                    a == b
                                                                    a != b

Can be dereferenced as an rvalue (if in a
dereferenceable state).	                                           *a
                                                                    a->m

Can be incremented (if in a dereferenceable state).
The result is either also dereferenceable or a past-the-end
iterator. The previous iterator value is not required to be
dereferenceable after the increase.	                           ++a
                                                                   (void)a++
                                                                   *a++

Its value type does not need to be assignable        	           t = u NOT required operaton

Lvalues are swappable.	                                           swap(a,b)

*/

    fields_input_iterator() : pistr{nullptr}, pindexes{nullptr}, ok{false}
    {
    }

    fields_input_iterator(std::istream& istr, unsigned int max_mdr_rkey, const std::vector<int>& indecies) noexcept : pistr(&istr), pindexes{&indecies}, ok{true}
    {
        advance(max_mdr_rkey);

    	auto size = pindexes->size();

        pvec =  std::make_shared<std::vector<std::string>>(size);

        read();  
    }

   ~fields_input_iterator() = default;

    fields_input_iterator& operator=(const fields_input_iterator& lhs) = default;
        
    const reference operator*() const noexcept
    {
       return *pvec;
    }

    const std::vector<std::string> *operator->() const noexcept
    {
        return &operator*();
    }

    fields_input_iterator& operator++() noexcept 
    {
        read(); 
        return *this; 
    }

    fields_input_iterator operator++(int) noexcept 
    {
        fields_input_iterator tmp{*this};
        operator++();   
        return tmp; 
    }

    bool
    equal(const fields_input_iterator& rhs) const
    { 
    	return (ok == rhs.ok) && (!ok || pistr == rhs.pistr);
    }

};

//  Return true if x and y are both end or not end, or x and y are the same.
inline bool operator==(const fields_input_iterator& lhs, const fields_input_iterator& rhs)
{
   return lhs.equal(rhs);
}

//  Return false if x and y are both end or not end, or x and y are the same.
inline bool operator!=(const fields_input_iterator& lhs, const fields_input_iterator& rhs)
{
   return !lhs.equal(rhs);
}
inline void fields_input_iterator::advance(unsigned int max_mdr_rkey) 

{
   // Advance until predicate is true.
   auto predicate = [=] (unsigned input_mdr)
                    { 
                       return input_mdr > max_mdr_rkey;
                    };

   find_if(std::istream_iterator<mdr_rkey>(*pistr), std::istream_iterator<mdr_rkey>{}, predicate);
}
#endif 
