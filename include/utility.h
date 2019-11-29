#ifndef utility_h_294723974
#define utility_h_294723974

#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <ostream>
#include "config.h"
#include "mdr-rkey.h"

using namespace sql;
using namespace std;


void delete_maude_table_rows(const std::list<Config::file>& file_list, sql::Connection& conn) noexcept;

/*
 Fetch all sorted mdr_rkeys in devicefoi
 */
vector<int> fetch_all_DeviceMdrReportKeys(sql::Connection& conn) noexcept;

unsigned int get_max_mdr_rkey(sql::Connection& conn) noexcept;

/*
 input: maude .txt date in mm/dd/yyyy format
 output: mysql date
 */
std::string buildMySQLDate(const std::string& in) noexcept;

// Generic database exception display for use with any database. Create DBException, which 
std::ostream& display_exception(std::ostream& ostr, const sql::SQLException& e) noexcept;
std::ostream& display_exception(std::ostream&, const std::exception& e) noexcept;

void fixText(string& in) noexcept;

inline int word_cnt(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

#endif
