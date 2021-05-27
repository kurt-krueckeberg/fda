#ifndef token_iterator_h
#define token_iterator_h

#include <string>
#include <string_view>

template<char TOKEN='|'> class token_iterator {

    using iterator_category = std::input_iterator_tag;
    using value_type = std::pair<const char *, int>;
    using reference = value_type&; 
    
  bool ok;
  
  const std::string *const pline; 
    
  int  pos;
  int  prev_pos;

  const char token;

  std::string_view value; // The current field. Set by fetch_field

  std::string_view fetch_field(bool initial=false) noexcept 
  {
     ok = (pline && pos != pline->size()) ? true : false;

     if (!ok) prev_pos = pos; // This statement ensures *operator() always returns an empty string if the user
                              // calls operator++() once iteration is complete.

     if (ok) {

         if (!initial && pos != pline->size()) ++pos;  // skip over token or advance to start 

         prev_pos = pos;

         pos = pline->find(token, pos);

         if (pos == std::string::npos) {
             
             pos = pline->size();
         }
     } 
     
     const char *current_start = pline->c_str() + prev_pos; // current string_view start
     unsigned current_length = (pos == std::string::npos) ? 0 : pos - prev_pos; // current string_view length

     return {current_start, current_length}; 
  }

  public:

   token_iterator() : token{TOKEN}, ok{false}, pline{nullptr}
   {
       prev_pos = pos = 0;
   } 

   explicit token_iterator(const std::string& in_line) : pline{&in_line}, token{TOKEN}, ok{true}
   {
      prev_pos = pos = 0;
      value = fetch_field(true);  
   }

   token_iterator(const token_iterator& lhs) = default; 

  ~token_iterator() {}
  
   token_iterator& operator++() noexcept
   {
      value = fetch_field();
      return *this;
   }

   token_iterator operator++(int) noexcept
   {
      token_iterator tmp{*this};

      value = fetch_field();

      return tmp;
   }

   const std::string_view operator*() noexcept
   {
     return value; 
   } 

   const std::string_view *operator->() noexcept
   {
     return &value;
   }

   bool equal(const token_iterator& rhs) const noexcept
   {
     return (ok == rhs.ok) && (!ok || (pline == rhs.pline && pos == rhs.pos && prev_pos == rhs.prev_pos));
   }
};

template<char T> inline bool operator!=(const token_iterator<T>& lhs, const token_iterator<T>& rhs) noexcept
{
  return !(lhs.equal(rhs));
}

template<char T> inline bool operator==(const token_iterator<T>& lhs, const token_iterator<T>& rhs) noexcept
{
  return lhs.equal(rhs);
}
#endif
