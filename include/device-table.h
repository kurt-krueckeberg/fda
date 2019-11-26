#ifndef device_table_h
#define device_table_h

#include "maude-table.h"
#include <string>
//#include <iostream> // For debug only
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include "text-fields.h"
#include <vector>
#include <unordered_map>


class device_table : public maude_table {

  sql::Connection&  conn;

  std::unique_ptr<sql::PreparedStatement>  insertStmt;

  int max_mdr_report_key;

  std::unordered_map<unsigned, std::vector<std::string>> mdr_key_code_map; 

  static const int mdr_report_key_index = 0;
  static const int device_report_product_code_index = 2;
  static const int device_sequence_no_index = 1;
  static const std::string max_string; 
   
  static std::string EXCIMER_LASER_SYSTEM; // LZS
  static std::string KERATOME; // HNO
  static std::string ONE_DOT_0; // "1.0"

  bool is_lasik_record(const std::vector<std::string>& row) const;

 public:

  explicit device_table(sql::Connection& conn); 
 
  bool write(const std::vector<std::string>& mf) override;
  
  bool is_new_record(const std::vector<std::string>& row) override;

};
   
#endif
