#ifndef regex_callback_h
#define regex_callback_h

#include <regex>
#include <string>
#include <memory>
 
template<class Functor> std::string regex_replace_callback(std::string& text, const std::regex& regexpr, Functor user_callback) noexcept
{
  std::sregex_iterator iter(text.begin(), text.end(), regexpr); 

  std::sregex_iterator end;

  std::string output;
  
  while(iter != end) {
 
     output += iter->prefix();
     
     output += user_callback(*iter); 
     
     std::string final_str { std::move(iter->suffix()) };  

     if (++iter == end) {
             
         output += move(final_str); // get any final terminating text after the last match. 
         break;
     }
  }

  return output;
} 
#endif
