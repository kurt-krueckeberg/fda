#include <iostream>
#include <cppconn/driver.h>

#include "mysql_driver.h"

#include "config.h"
#include "utility.h"
#include "db-code.h"

using namespace std;
using namespace sql;

int main(int argc, char** argv)
{
  if (argc == 1) {
 
      cout << "The the name of the configuration xml file is missing.\n";
      return 0;
  } 
 
  const Config config = load_config(argv[1]);
 
  try {  

    unique_ptr<Connection> conn_ptr{ get_driver_instance()->connect(config.db.host, config.db.user, config.db.password) };
     
    conn_ptr->setSchema(config.db.dbname);  // select database
 
    mysql_dbcode(*conn_ptr, config);
 
  }  catch(const std::exception& e) { // note: We convert SQLExceptions to td::runtime_error whose base is std::exception
           
     display_exception(cout, e); 
  }
  return 0;
}
