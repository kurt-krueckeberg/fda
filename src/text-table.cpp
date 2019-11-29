#include "text-table.h"
#include "utility.h"
#include <algorithm>

using namespace std;
using namespace sql;

bool text_table::is_new_record(const std::vector<std::string>& row) 
{
   /* 
     We only want rows where text_type_code == 'D' and the sequence number is empty or 1. NOTE: This does guarantee that the mdr_rkey will only occur
     once. 
    
     There can be instances where the mdr_rkey occurs more than once when the text_type is 'D' and the sequence number is 1( but we only save the 
     first instance)
    * 
    * TODO: BUG
    *  
    * However, I discovered this is not the whole story. There can be multiple instances of an mdr report key where the Text Type Code is D (or N) and the
    * sequence number is 1. So the tuple (mdr_rkey, D, 1) and (mdr_rkey, N, 1) is not a key. It can occur more than once.
    * 
    * In these instances, the 2nd column, MDR Text Key, appears to be different, however. 
    * Determine if the mdr text key is unique per row, or if the mdr report key is also need, so that pair (mdr report key, mdr text report) is a key.
    
     The third colum is the Text Type Code. It indicates the section that contains the text.

         Text Type Code  | Section | Description
       -----------------------------------------
      1.       D         |  B5     |
      2.       E         |  H3     | Manufacturer's section?
      3.       N         |  H10    | Additional Manufacturer's narrative
    */

   //--string text_type_code {row[text_table::text_type_code_index]} TODO: Did this cause one row to be ommitted?
;
   const string& text_type_code = row[text_table::text_type_code_index];

   auto mdr_rkey = stoi(row[text_table::mdr_rkey_index]);

   if (mdr_rkey == prior_mdr_rkey) {

       return false;
   }

   // TODO: Is this of the form "1" or "1.0"?
   //--string patient_seq_no {row[text_table::patient_sequence_no_index]};
   const string& patient_seq_no = row[text_table::patient_sequence_no_index];

   if (  !( text_type_code[0] == text_table::TEXT_TYPE_CODE_REQD && (patient_seq_no[0] == text_table::PATIENT_SEQ_NO_REQD || patient_seq_no.empty()) ) ) return false;

   if (!binary_search(mdr_rkeys.begin(), mdr_rkeys.end(), mdr_rkey)) {

       return false;
   }

   prior_mdr_rkey = mdr_rkey;
 
   return true;
}

bool text_table::write(const std::vector<std::string>& row) 
{
    auto mdr_rkey = stoi(row[text_table::mdr_rkey_index]);

    // Use the fixText() utility to correct the case.
    string& text_report = const_cast<string&>( row[text_table::text_report_index] );

    ::fixText(text_report);

    insertStmt->setInt(1, mdr_rkey); // double check 1
    insertStmt->setString(2, text_report); // double check 2

    return insertStmt->executeUpdate() ? true : false;
}


