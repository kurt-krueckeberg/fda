#include <string>
#include <iostream>
#include <iterator>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>

#include "config.h"
#include "utility.h"
#include "scoped-trans.h"
#include "fields-input-iterator.h"
#include "maude-table.h"
#include "table-factory.h"
#include "table-write-iterator.h"
#include "medwatch-table.h"
#include "maude-seek-iterator.h"
#include "debug-write-iterator.h"
#include "validate.h"

#include "input_validator.h" //TODO: Remove later

using namespace sql;
using namespace std;

void validate(const Config& config)
{
  try {

    auto file_entry_iter = config.file_list.begin();
    
//++    for(; file_entry_iter != config.file_list.end(); ++file_entry_iter) {

        // Use this alternate code to debug and print text_fields input to stdout:
        ifstream ifstr{file_entry_iter->filename};

        copy( fields_input_iterator(ifstr, file_entry_iter->indecies), \
                fields_input_iterator(),\
                debug_write_iterator{cout} );

//++     }
    return;

  } catch(exception& e) {

      cout << e.what() << "\n";
  }
}
