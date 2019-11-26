#ifndef text_table_h
#define text_table_h

#include "maude-table.h"
#include "utility.h"
#include <memory>

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>

class text_table : public maude_table { 

  sql::Connection&  conn;
  std::unique_ptr<sql::PreparedStatement>  insertStmt;

  static const int mdr_report_key_index = 0;
  static const int text_type_code_index = 2;
  static const int patient_sequence_no_index = 3;
  static const int text_report_index = 4;
 
  enum class Fields { mdr_report_key_index = 0, text_type_code_index = 2, patient_sequence_no_index = 3, text_report_index = 4};


  static const char TEXT_TYPE_CODE_REQD = 'D';
  static const char PATIENT_SEQ_NO_REQD = '1';

  int prior_mdr_report_key;  // from PHP code
  std::vector<int> mdr_report_keys; // sorted vector for binary_search() lookup
 
  std::string fixText(const std::string& str);

  void load_mdr_report_keys();

 public:

  explicit text_table(sql::Connection& conn); // <-- new TODO: text_table(..., unsigned max_mdr_report_key);
 
  bool write(const std::vector<std::string>& mf) override;
  
  bool is_new_record(const std::vector<std::string>& r) override;
  
};

inline text_table::text_table(sql::Connection& in_conn) : conn{in_conn}
{
  // create prepared statement
  insertStmt.reset( conn.prepareStatement( "INSERT INTO textfoi(mdr_report_key, text_report) values (?, ?)") ); // values (mdr_report_key, text_report)

  // Build vector<int> of sorted device.mdr_report_key's.
  mdr_report_keys = fetch_all_DeviceMdrReportKeys(conn);
}
#endif
