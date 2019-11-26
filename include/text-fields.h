#ifndef text_fields_h
#define text_fields_h

#include "config.h"
#include <list>
#include <functional>
#include <iostream>

class text_fields {

  public:
             
   using indexes_retrieval_callback = std::function< const std::vector<int>& () >; 
  
   static void configure_streaming(std::list<Config::file>::const_iterator& citer) noexcept
   {
      text_fields::indexes_retriever = [&] () -> const std::vector<int>& { return citer->indecies; };
   }  

   text_fields() : text_fields(  (text_fields::indexes_retriever)() ) {}   // Delegating constructor. 

   std::istream& read(std::istream& istr) noexcept;

   // Conversion operators.    
   operator std::vector<std::string>&&()// For use with std::move() algorithm.
   { 
     return std::move(vec); 
   }

   operator const std::vector<std::string>&() const // For use with std::copy, etc.
   {
       return vec;
   }

   std::vector<std::string>::const_iterator begin() const noexcept
   {
      return vec.begin();
   }

   std::vector<std::string>::const_iterator end() const noexcept
   {
      return vec.end();
   }

   virtual std::ostream& write(std::ostream& ostr) const noexcept
   {
       for(auto& str : vec) {
      
             ostr << str << ", ";
       }

       return ostr << std::endl; 
   }

   friend std::istream& operator>>(std::istream& istr, text_fields& flds) noexcept
   {
     return flds.read(istr);
   }
     
   friend std::ostream& operator<<(std::ostream& ostr, const text_fields& flds) noexcept
   {
     return flds.write(ostr);
   }

 private:
  
   inline static indexes_retrieval_callback indexes_retriever = nullptr; 

   const std::vector<int>& indecies;
    
   std::vector<std::string> vec; 

   std::string line;
 
  explicit text_fields(const std::vector<int>& indexes) : indecies{indexes}, vec{indexes.size(), ""} // reserve indexes.size() elements
  {
  }
 
};
#endif
