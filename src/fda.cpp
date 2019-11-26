#include <cstdlib>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include "mysql_driver.h"

#include "config.h"
#include "utility.h"
//++#include "db-code.h"
#include "new-db-code.h" // TOD: remove

using namespace std;
using namespace sql;

int main(int argc, char** argv)
{
   // Check that config.xml was specified in argv[]
  string config_file;

  if (argc == 1) {
 
      cout << "The the name of the configuration xml file is missing.\n";
      return 0;
  } 
 
  const Config config = load_config(argv[1]);
  
  shared_ptr<Connection> conn_ptr{nullptr};
 
  try {  
      
    conn_ptr = move(shared_ptr<Connection>{ get_driver_instance()->connect(config.db.host, config.db.user, config.db.password) } ); 
     
    conn_ptr->setSchema(config.db.dbname);  // select database
 
    validate_mysql_dbcode(*conn_ptr, config);
 
 }  catch(const std::exception& e) { // note: We convert SQLExceptions to td::runtime_error whose base is std::exception
           
     display_exception(cout, e); 
  }
  return 0;
}

