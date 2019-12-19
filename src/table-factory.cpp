#include "table-factory.h"
#include "mdr-table.h"
#include "device-table.h"
#include "text-table.h"
#include "config.h"

#include <memory>
#include <exception>

using namespace std;
using namespace sql;

shared_ptr<maude_table>  table_factory::createTable(const Config::file& file) const 
{
  char c = static_cast<int>(file.table[0]); // just use first character's decimal value.

  switch(c) {

     case 'd':
       return { make_shared<device_table>(conn) };
       break;

     case 'm':
       return {make_shared<mdr_table>(conn)};
       break;

     case 't':
       return {make_shared<text_table>(conn)};
       break;

     default:
         throw logic_error("In table_factory::createTable(const Config::file&). Unknown case ile::table[0] ");
           break;

  }

  return 
}
