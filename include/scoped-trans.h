#ifndef scoped_tranacstion_h
#define scoped_tranacstion_h

#include "cppconn/connection.h"
#include <cppconn/statement.h>

namespace sql {


class ScopedTransaction {

   public:
      ScopedTransaction(sql::Connection& conn_in);

      ScopedTransaction(const ScopedTransaction&) = delete; 
      
      ScopedTransaction(ScopedTransaction&&) = delete; 
      ScopedTransaction& operator=(const ScopedTransaction&) = delete; 
      ScopedTransaction& operator=(ScopedTransaction&&) = delete; 

      void start();
      void commit(); 
      ~ScopedTransaction();
      
   private:
     sql::Connection& conn;     
     bool engaged;
};

inline ScopedTransaction::ScopedTransaction(sql::Connection& conn_in) : conn(conn_in)
{
  start();
}

inline void ScopedTransaction::start() 
{ 
  engaged = true;
  std::unique_ptr<Statement> statement {conn.createStatement()};
  
  statement->execute("START TRANSACTION");
}

inline void ScopedTransaction::commit() 
{ 
  conn.commit(); 
  engaged = false;
};

inline ScopedTransaction::~ScopedTransaction()
{
   if (engaged) {
       conn.rollback();
   } 
};


}// end sql namespace
#endif
