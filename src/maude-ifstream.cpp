#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "maude-ifstream.h"

bool maude_ifstream::b_initialized;
unsigned long maude_ifstream::max_mdr_rkey;

using namespace std;
using namespace sql;

unsigned int maude_ifstream::get_max_mdr_rkey(sql::Connection& conn) noexcept
{
   unsigned max_mdr_rkey = 0;

   unique_ptr<Statement> stmt { conn.createStatement() };

   // Are there any medwatch_report records? ...
   unique_ptr<ResultSet> rs { stmt->executeQuery("SELECT count(*) as total FROM medwatch_report") };

   rs->first();

   if (static_cast<int>( rs->getInt(1) ) != 0) { //...if yes, select max(mdr_rkey).

      rs.reset( std::move( stmt->executeQuery("SELECT max(mdr_rkey) as max_mdr_rkey FROM medwatch_report") ));

      rs->first();

      max_mdr_rkey = rs->getUInt64(1);
   }

   return max_mdr_rkey;
}
