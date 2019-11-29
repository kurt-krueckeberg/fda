#include "mdr-table.h"
#include "utility.h"

#include <sstream>
#include <algorithm>

using namespace std;
using namespace sql;

mdr_table::mdr_table(sql::Connection& in_conn) : conn{in_conn}
{
  // create prepared statement
  // values (:mdr_rkey, :report_source_code, :date_received)");
  insertStmt.reset( conn.prepareStatement("INSERT INTO mdrfoi(mdr_rkey, report_source_code, date_received) values (?, ?, ?)") );

  mdr_rkeys = fetch_all_DeviceMdrReportKeys(conn); 
} 
/*
 insertStmt == "INSERT INTO mdrfoi(mdr_rkey, report_source_code, date_received) values (?, ?, ?)") );
 */

bool mdr_table::is_new_record(const std::vector<std::string>& row) 
{
  auto mdr_rkey = stoi(row[mdr_table::mdr_rkey_index]);
  
  if (mdr_rkey == prior_mdr_rkey) return false;
  
  /*
  if (mdr_rkey == prior_mdr_rkey)  { // debug-only code
      
      cout << " prior mdr report key found by mdr_table::is_new_record\n";
  }
  */
  bool rc = binary_search(mdr_rkeys.begin(), mdr_rkeys.end(), mdr_rkey);
  
  prior_mdr_rkey = mdr_rkey;  
  
  return rc;
}

bool mdr_table::write(const std::vector<std::string>& row) 
{
   int mdr_rkey = stoi(row[mdr_table::mdr_rkey_index]);

   insertStmt->setInt(1, mdr_rkey); 

   insertStmt->setString(2, row[mdr_table::report_source_code_index]); // report_source_code == row[1]
    
   string dateReceived = buildMySQLDate(row[mdr_table::date_received_index]); 

   insertStmt->setDateTime(3, dateReceived); 

   return insertStmt->executeUpdate() ? true : false;
}
