#include "device-table.h"

using namespace std;
using namespace sql;

static const std::string max_string{ "SELECT max(mdr_rkey) as max_mdr_rkey FROM medwatch_report"};

string device_table::EXCIMER_LASER_SYSTEM{"LZS"};
string device_table::KERATOME{"HNO"};
string device_table::ONE_DOT_0{"1.0"};

device_table::device_table(sql::Connection& in_conn) : conn{in_conn}
{
   // If the table is empty, then set device_max_mdr_rkey to -1.
   unique_ptr<Statement> stmt { conn.createStatement() };

   // Are there any medwatch_report records...
   unique_ptr<ResultSet> rs { stmt->executeQuery("SELECT count(*) as total FROM medwatch_report") };
   
   rs->first();

   if (auto count = (int) rs->getInt(1); count != 0) { //...if yes, get the max(mdr_rkey)

      rs.reset( move( stmt->executeQuery("SELECT max(mdr_rkey) as max_mdr_rkey FROM medwatch_report") ));

      rs->first();

      max_mdr_rkey = rs->getUInt64(1);

   } else { 

      max_mdr_rkey = -1;
   }

  // Create a prepared statement where... values (:mdr_rkey, :device_product_code )
  insertStmt.reset( conn.prepareStatement( "INSERT INTO devicefoi(mdr_rkey, device_product_code) values (?, ?)") );
}


bool device_table::is_new_record(const std::vector<std::string>& row) 
{
   // Is it a LASIK record?
   if (row[device_table::device_report_product_code_index] != device_table::EXCIMER_LASER_SYSTEM && row[device_table::device_report_product_code_index] != device_table::KERATOME) {
           
       return false;
   }

/* Seems unimportant

   // Is the sequence number 1.0?
   auto& seq_no = row[device_table::device_sequence_no_index];
    
   if (auto trimmed_str = seq_no.substr(seq_no.find_first_not_of(' '), seq_no.size() - 1); trimmed_str != device_table::ONE_DOT_0) { // is it equal to "1.0"?

       return false;
   }
*/
    
   // Is it a new mdr_rkey, greater than the prior max value in the table before we ran this code?
   auto mdr_rkey = stoi(row[device_table::mdr_rkey_index]);

// See: http://thispointer.com/unordered_map-usage-tutorial-and-example/

   auto iter = mdr_key_code_map.find(mdr_rkey);

   if (iter != mdr_key_code_map.cend()) { // If the mdr_rkey is already in the hash table...

      // ...is the new product_report_code, too?
      auto& vec = iter->second;
      
      if (find(vec.begin(), vec.end(), row[device_table::device_report_product_code_index]) == vec.end()) { // If not...
            
          vec.push_back(row[device_table::device_report_product_code_index]); // ... add it.

      } else {

        /* 
         Debug code:
  
         cout << "This is a duplicate mdr_rkey/product_code pair: " << "{ " << mdr_rkey << ", " << row[device_table::device_report_product_code_index] << " }" << endl;

         */  
         return false;
      }

   } else { // If mdr_rkey is not in hash table, add it

      auto& vec = mdr_key_code_map[mdr_rkey];
      vec.push_back( row[device_table::device_report_product_code_index]);         
   }   

   return true;
}

bool device_table::write(const std::vector<std::string>& row) 
{
    auto mdr_rkey = stoi(row[device_table::mdr_rkey_index]);
    
    insertStmt->setInt(1, mdr_rkey); 
    
    insertStmt->setString(2, row[device_table::device_report_product_code_index]);
   
    return insertStmt->executeUpdate() ? true : false; 
}
