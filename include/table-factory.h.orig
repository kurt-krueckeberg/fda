#ifndef table_factory_h
#define table_factory_h

#include <cppconn/connection.h>
#include <memory>
#include "maude-table.h"
#include "config.h"


class table_factory {

   sql::Connection& conn;

 public:
  table_factory(sql::Connection& conn_in) : conn{conn_in} {}

  std::shared_ptr<maude_table> createTable(const Config::file&) const; 
};
#endif
