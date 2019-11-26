#ifndef medwatch_table_h
#define medwatch_table_h

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>

#include <string>
#include <memory>

/*
 * Inserts the results of join of the three Maude tables into the medwatch_report table.
 */

class medwatch_table {

   sql::Connection& conn; //  private conn;

   static std::string select_query;
   static std::string insert_query;

   std::unique_ptr<sql::PreparedStatement>  insert_stmt;

   // bound parameters for prepared insert PDOStatement
   int  mdr_report_key;

   std::string  text_report;
   std::string  date_received;
   std::string  report_source_code;

   int insert_count; 

 public:

   medwatch_table(sql::Connection& conn_in);
   medwatch_table(const medwatch_table&) = delete;
   medwatch_table(medwatch_table&&) = delete;
   
   void insertMaudeData() noexcept;
   
   int get_insert_count() const noexcept;
    
 private:

    void retrieve_and_bind(sql::ResultSet& res) noexcept;
    
    void insert();
};

inline medwatch_table::medwatch_table(sql::Connection& conn_in) : conn{conn_in}, insert_count{0} 
{
   insert_stmt.reset ( conn.prepareStatement(insert_query) );
}

inline int medwatch_table::get_insert_count() const noexcept
{
   return insert_count; 
}
#endif
