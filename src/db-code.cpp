#include <cppconn/connection.h>
#include <cppconn/exception.h>

#include "config.h"
#include "utility.h"
#include "scoped-trans.h"
#include "fields-input-iterator.h"
#include "table-factory.h"
#include "table-write-iterator.h"
#include "medwatch-table.h"
#include "db-code.h"
//--#include "maude-ifstream.h"

#include <fstream>

using namespace sql;
using namespace std;

void mysql_dbcode(Connection &conn, const Config& config)
{
  try {

    table_factory tbl_factory{conn};

    auto file_entry_iter = config.file_list.begin();
    
    ScopedTransaction sql_transaction(conn);

    auto max_mdr_rkey = get_max_mdr_rkey(conn);

    for(; file_entry_iter != config.file_list.end(); ++file_entry_iter) {
 
        // create table object.
        auto tbl_ptr { tbl_factory.createTable(*file_entry_iter) };
 
        cout << "Processing " << file_entry_iter->filename << endl;

        // Open file.
        ifstream ifstr{file_entry_iter->filename};

        auto output_iter = copy_if( fields_input_iterator(ifstr, max_mdr_rkey, file_entry_iter->indecies), \
                                    fields_input_iterator(),\
                                    table_write_iterator{*tbl_ptr},\
                                    [&tbl_ptr](const vector<string>& row) 
                                              {
                                                return tbl_ptr->is_new_record(row); 
                                              }
                                   );

        /*
        Use this a alternate code to debug and print text_fields input to stdout:
        
        auto predicate = [&tbl_ptr](const vector<string>& row) { return true; };
        
        auto output_iter = copy( fields_input_iterator(ifstr, file_entry_iter->indecies), \
                                 fields_input_iterator(),\
                                 debug_write_iterator{cout} );
        
        if (output_iter.get_write_count() == 0) {
        
            cout << "Zero total records were written to database table '" << file_entry_iter->table << "' from file " << file_entry_iter->filename << ". Exiting." << endl; 
            return; 
        }
 
        cout << output_iter.get_write_count() << " total records slated to be committed to database table '" << file_entry_iter->table << "' from file " << file_entry_iter->filename << endl;
        */
    }
 
    sql_transaction.commit();
      
    cout << "ScopedTransaction to the three main temporary tables--devicefoi, mdrfoi, textfoi--commited" << endl;

    sql_transaction.start();

    cout << "medwatch_report table update transaction started." << endl;
 
    // Insert maude table data into medwatch_report table.
    medwatch_table medwatch_tbl{conn};
 
    medwatch_tbl.insertMaudeData();
 
    sql_transaction.commit(); // commit transaction
 
    cout << "ScopedTransaction commited: medwatch_report table updated. " << medwatch_tbl.get_insert_count() << " records were inserted in medwatch_report." << endl;
        
  } catch (const SQLException& sqle) {
 
     throw runtime_error{ (string{"SQLException: "} +  sqle.what() + "\nMySQL error code: " + to_string(sqle.getErrorCode()) +  "\nSQLState: " + sqle.getSQLState() + "\n").c_str() }; 

  } catch(exception& e) {

      cout << e.what() << "\n";
  }
}
