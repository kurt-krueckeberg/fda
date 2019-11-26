#ifndef input_validate_h	
#define input_validate_h	
	
#include <regex>
#include <vector>
#include <string>

class valid_device {

    static std::regex re_num;
    static std::regex re_3char;

 public:

    void operator()(const std::vector<std::string>& v) const;
};    
#endif
