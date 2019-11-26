#include "input_validator.h"
#include <iostream>

using namespace std;

regex valid_device::re_num{ R"d(^\d+$)d"};
regex valid_device::re_3char{ R"d(^[A-Z]{3}$)d"};

void valid_device::operator()(const std::vector<std::string>& v) const
{

  if (v.size() !=3 ) {

       cout << "Maude device row with MDR of " << v[0] << " does not have three fields\n";
       return;
  }

  if (!regex_match(v[0], re_num)) {

       cout << "Maude device row with MDR of " << v[0] << " has a device number that is not a number\n";
       return;
  }

  // Test last filed to make sure it is three characters.
  if (!regex_match(v[2], re_3char)) {

       cout << "Maude device row with MDR of " << v[0] <<" has a Device Product Code that is not three characters\n";
       return;
  }
}
