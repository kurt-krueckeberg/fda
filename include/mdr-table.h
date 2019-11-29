#ifndef mdr_table_h_23480832
#define mdr_table_h_23480832

#include "maude-table.h"
#include <memory>
#include <vector>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>


class mdr_table : public maude_table {

  sql::Connection&  conn;
  std::unique_ptr<sql::PreparedStatement>  insertStmt;

  static const int mdr_rkey_index = 0;
  static const int report_source_code_index = 1;
  static const int date_received_index = 2;

  int prior_mdr_rkey; // for debugging, methinks.
  std::vector<int> mdr_rkeys; // sorted vector

 public:

  explicit mdr_table(sql::Connection& lhs_conn);
 
  bool write(const std::vector<std::string>& mf) override;
  bool is_new_record(const std::vector<std::string>& r) override;
 
};
#endif
