#include "mdr-table.h"
#include "utility.h"

#include <sstream>
#include <algorithm>

using namespace std;
using namespace sql;

mdr_table::mdr_table(sql::Connection& in_conn) : conn{in_conn}
{
  // create prepared statement
  // values (:mdr_report_key, :report_source_code, :date_received)");
  insertStmt.reset( conn.prepareStatement("INSERT INTO mdrfoi(mdr_report_key, report_source_code, date_received) values (?, ?, ?)") );

  mdr_report_keys = fetch_all_DeviceMdrReportKeys(conn); 
} 
/*
 insertStmt == "INSERT INTO mdrfoi(mdr_report_key, report_source_code, date_received) values (?, ?, ?)") );
 */

bool mdr_table::write(const std::vector<std::string>& row) 
{
   int mdr_report_key = stoi(row[mdr_table::mdr_report_key_index]);

   insertStmt->setInt(1, mdr_report_key); 

   insertStmt->setString(2, row[mdr_table::report_source_code_index]); // report_source_code == row[1]
    
   string dateReceived = buildMySQLDate(row[mdr_table::date_received_index]); 

   insertStmt->setDateTime(3, dateReceived); 

   return insertStmt->executeUpdate() ? true : false;
}

bool mdr_table::is_new_record(const std::vector<std::string>& row) 
{
  auto mdr_report_key = stoi(row[mdr_table::mdr_report_key_index]);
  
  if (mdr_report_key == prior_mdr_report_key) return false;
  
  /*
  if (mdr_report_key == prior_mdr_report_key)  { // debug-only code
      
      cout << " prior mdr report key found by mdr_table::is_new_record\n";
  }
  */
  bool rc = binary_search(mdr_report_keys.begin(), mdr_report_keys.end(), mdr_report_key);
  
  prior_mdr_report_key = mdr_report_key;  
  
  return rc;
}
