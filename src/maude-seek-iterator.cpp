#include "maude-seek-iterator.h"
#include "mdr-report-key.h"
#include <cppconn/statement.h>
#include <memory>
#include <iterator>
#include <algorithm>

using namespace sql;
using namespace std;
/* 
 * 
 * Advance the file stream to the first line of the file where its mdr_report_key exceeds the maximum mdr_report_key from the medwatch_report table.
 * If the medwatch_report table is empty, this will be the first line of the file (there will be no advancement).
 * 
 */

void maude_seek_iterator::seekto_new_records(Connection& conn) noexcept
{
   unsigned max_mdr_report_key = 0;
   
   unique_ptr<Statement> stmt { conn.createStatement() };

   // Are there any medwatch_report records? ...
   unique_ptr<ResultSet> rs { stmt->executeQuery("SELECT count(*) as total FROM medwatch_report") };
   
   rs->first();

   if (static_cast<int>( rs->getInt(1) ) != 0) { //...if yes, select max(mdr_report_key).

      rs.reset( std::move( stmt->executeQuery("SELECT max(mdr_report_key) as max_mdr_report_key FROM medwatch_report") ));

      rs->first();

      max_mdr_report_key = rs->getUInt64(1);
   } 
   // Advance until predicate is true (and return iterator at that point) or advance to the last record (and return end iterator, 2nd parameter).
   auto predicate = [max_mdr_report_key] (unsigned input_mdr) 
                    { 
                      return input_mdr > max_mdr_report_key;
                    };

   find_if(istream_iterator<mdr_report_key>{*this}, istream_iterator<mdr_report_key>{}, predicate); 
 }
