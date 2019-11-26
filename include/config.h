#ifndef confg_h_3482034802
#define confg_h_3482034802

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <list>

struct Config {

    struct Database {
    
      std::string host;
      std::string dbname;
      std::string user;
      std::string password;
    };

   struct file {
     
     std::string  filename;
     std::string  table;
     std::vector<int> indecies; 
     
     file() {}

     file(const char *lhs_filename, const char *lhs_table, std::vector<int>&& lhs_vec) :  filename{lhs_filename}, table{lhs_table}, indecies{std::move(lhs_vec)}
     {
     } 
   
     file(const file& lhs) = delete;
     
     file(Config::file&& lhs) : filename{ std::move(lhs.filename)}, table{std::move(lhs.table)}, indecies{std::move(lhs.indecies)} {}
     
     file& operator=(file&& lhs);
     
     file& operator=(std::vector<int>&& lhs)
     {
        indecies = std::move(lhs);
        return *this;
     }
   };
     
    Database db; 
    std::list<file> file_list;
};

const Config load_config(const std::string& file_name);
#endif
