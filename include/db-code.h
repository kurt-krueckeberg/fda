#ifndef db_code_h
#define db_code_h

#include "config.h"
#include <cppconn/connection.h>

void mysql_dbcode(sql::Connection& conn, const Config& config);

#endif
