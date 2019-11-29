#ifndef mdr_rkey_h_23797
#define mdr_rkey_h_23797

#include <iostream>

class mdr_rkey {

  private:

     int mdr_rkey_;

 public:

    explicit mdr_rkey() {}

    std::istream& read(std::istream& istr) noexcept;
        
    friend std::istream& operator>>(std::istream& istr, mdr_rkey& mdr) 
    {
       return mdr.read(istr);
    }
        
    friend std::ostream& operator<<(std::ostream& ostr, mdr_rkey& mdr)
    {
       ostr << mdr.mdr_rkey_;
       return ostr;
    }
        
    operator int() const noexcept { return mdr_rkey_; }
}; 
#endif
