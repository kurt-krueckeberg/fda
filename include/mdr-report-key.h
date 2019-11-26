#ifndef mdr_report_key_h_23797
#define mdr_report_key_h_23797

#include <iostream>

class mdr_report_key {

  private:

     int mdr_report_key_;

 public:

    explicit mdr_report_key() {}

    std::istream& read(std::istream& istr) noexcept;
        
    friend std::istream& operator>>(std::istream& istr, mdr_report_key& mdr) 
    {
       return mdr.read(istr);
    }
        
    friend std::ostream& operator<<(std::ostream& ostr, mdr_report_key& mdr)
    {
       ostr << mdr.mdr_report_key_;
       return ostr;
    }
        
    operator int() const noexcept { return mdr_report_key_; }
}; 
#endif
