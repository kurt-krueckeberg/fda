#include "medwatch-table.h"
#include "utility.h"

#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <memory>
#include <exception>

using namespace std;
using namespace sql;

// statics
string  medwatch_table::select_query {R"(SELECT textfoi.mdr_report_key, textfoi.text_report, mdrfoi.date_received, mdrfoi.report_source_code 
FROM textfoi INNER JOIN mdrfoi on textfoi.mdr_report_key=mdrfoi.mdr_report_key LEFT OUTER JOIN  medwatch_report  
  ON textfoi.mdr_report_key=medwatch_report.mdr_report_key 
 WHERE medwatch_report.mdr_report_key IS NULL ORDER BY textfoi.mdr_report_key)"};

string medwatch_table::insert_query { "INSERT INTO medwatch_report(mdr_report_key, text_report, date_received, report_source_code, word_cnt) values (?, ?, ?, ?, ?)" };

void medwatch_table::retrieve_and_bind(sql::ResultSet& res) noexcept
{
   // retrieve ResultSet values from LEFT OUTER JOIN...
   mdr_report_key = res.getUInt64(1); 
   
   text_report =  res.getString(2);
   
   date_received =  res.getString(3);
   
   report_source_code = res.getString(4);
       
   // bind them to insert statement
   insert_stmt->setUInt64(1, mdr_report_key); 

   insert_stmt->setString(2, text_report); 

   insert_stmt->setString(3, date_received);

   insert_stmt->setString(4, report_source_code);

   int cnt = word_cnt(text_report);

   insert_stmt->setUInt64(5, cnt); 
} 

void medwatch_table::insertMaudeData() noexcept
{
   insert_count = 0;

   // Run select query
   std::unique_ptr<Statement> select_stmt { conn.createStatement() };
   
   unique_ptr<sql::ResultSet> res { select_stmt->executeQuery(medwatch_table::select_query) };
   
   while (res->next()) {
   
       /* Access column data by numeric offset, 1 is the first column */
       retrieve_and_bind(*res);
 
       insert_stmt->execute();

       ++insert_count;
   }
} 
