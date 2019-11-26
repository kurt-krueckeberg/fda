#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <ostream>
#include <algorithm>
#include <regex>
#include "utility.h"

using namespace std;
using namespace sql;

void delete_maude_table_rows(const std::list<Config::file>& file_list, sql::Connection& conn) noexcept
{
   unique_ptr<Statement> stmt { conn.createStatement() };

   for(const auto& file : file_list) {
       
      stmt->execute("delete from " + file.table + " where 1");
   }
}

vector<int> fetch_all_DeviceMdrReportKeys(sql::Connection& conn) noexcept 
{ 
  unique_ptr<Statement> cnt_stmt{ conn.createStatement() };

  unique_ptr<ResultSet> rs{ cnt_stmt->executeQuery("SELECT count(*) FROM devicefoi") };

  rs->first();

  int count = rs->getInt(1);

  if (count == 0) {

     return vector<int>(0); 
  }

  vector<int> mdr_report_keys(count);

  unique_ptr<PreparedStatement> pstmt{ conn.prepareStatement("SELECT mdr_report_key from devicefoi ORDER BY mdr_report_key ASC") };

  unique_ptr<ResultSet> res{ pstmt->executeQuery() };

  auto index = 0;

  while (res->next()) {

     mdr_report_keys[index++] = res->getInt(1);
  }

  return mdr_report_keys;
}

/*
 input: maude .txt date in mm/dd/yyyy format
 output: mysql date
 */
std::string buildMySQLDate(const std::string& in) noexcept
{
   std::istringstream iss(in); 

   array<string, 3> date_parts;

   string token;

   auto i = 0;

   while (std::getline(iss, token, '/')) {

       date_parts[i++] = move(token);
   }
  
   return date_parts[2] + '-' + date_parts[0] + '-' + date_parts[1];
}

std::ostream& display_exception(std::ostream& ostr, const sql::SQLException& e) noexcept
{        
    ostr << "SQLException: " <<  e.what() << endl;
    ostr << " (MySQL error code: " << e.getErrorCode();
    ostr << ", SQLState: " << e.getSQLState() << " )" << endl;
    return ostr;
}

std::ostream& display_exception(std::ostream& ostr, const std::exception& e) noexcept
{        
    ostr << "ERROR: exception thrown \n";
    ostr << e.what() << endl;
    return ostr;
}

void fixText(string& s) noexcept
{
  // Initially ensure all text is all lowercase.
  for_each(s.begin(), s.end(), [&](char& c) { \
                                   c = tolower(c, locale()); }\
  ); 

  // Capitalize personal titles--dr, mr, mrs, ms--and the personal pronoun i
  regex re_titles{ R"(\b(?:dr)|(?:mr)|(?:ms)|(?:mrs)|(?:i)\b)" };

  sregex_iterator titles_iter(s.begin(), s.end(), re_titles);

  sregex_iterator titles_end;

  int index = 0;

  auto lambda_toupper = [&](const smatch& sm) {

       auto pos = sm.position(index);
       
       s[pos] = toupper(s[pos], std::locale());
  };

  for_each(titles_iter, titles_end, lambda_toupper);
  
  // Capitalize first word of sentences...

  // ...Do the very first character manually
  s[0] = toupper(s[0], locale());

  regex re_ucfirst{R"((?:\.|\?|!)\s+([a-z]))"};

  sregex_iterator ucfirst_iter(s.begin(), s.end(), re_ucfirst);
  
  sregex_iterator ucfirst_end;
  
  index = 1;

  // Do remaining sentences using regex and lambda_toupper function 
  for_each(ucfirst_iter, ucfirst_end, lambda_toupper);

  return;
}
