#ifndef show_regex_h
#define show_regex_h

#include <string>
#include <regex>

void show_regex(std::sregex_token_iterator iter, std::sregex_token_iterator rend, const std::string& msg);

#endif 
