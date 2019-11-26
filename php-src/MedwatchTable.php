<?php
namespace Maude;

/*
 * Inserts the results of join of the three Maude tables into the medwatch_report table.
 */

class MedwatchTable {

   private $pdo;
   private $select_query;
   private $insert_query;
   private $insert_stmt;

   // bound parameters for prepared insert PDOStatement
   private  $mdr_report_key;
   private  $text_report;
   private  $date_received;
   private  $report_source_code;

   private  $insert_count; 

   public function __construct(\PDO $pdo_in)
   {
           $this->pdo = $pdo_in;
           $this->select_query = <<<SELECT_QUERY
SELECT textfoi.mdr_report_key, textfoi.text_report, mdrfoi.date_received, mdrfoi.report_source_code 
FROM textfoi 
     INNER JOIN
   mdrfoi on textfoi.mdr_report_key=mdrfoi.mdr_report_key
     LEFT OUTER JOIN
   medwatch_report 
     ON textfoi.mdr_report_key=medwatch_report.mdr_report_key
WHERE medwatch_report.mdr_report_key IS NULL ORDER BY textfoi.mdr_report_key
SELECT_QUERY;

         $this->insert_query = <<<INSERT_QUERY
INSERT INTO medwatch_report(mdr_report_key, text_report, date_received, report_source_code) values (:mdr_report_key, :text_report, :date_received,
:report_source_code )
INSERT_QUERY;

         $this->insert_count = 0;
    }
 
    public function insertMaudeData()
    {
       $this->insert_stmt = $this->pdo->prepare($this->insert_query);

       $this->bindInsertParameters($this->insert_stmt); 
       
       $this->insert();  
    }  

    public function getInsertCnt() : int
    {
       return $this->insert_count;
    }

    protected function bindInsertParameters(\PDOStatement $insert_stmt)
    {
       // bind the parameters in each statement
       $insert_stmt->bindParam(':mdr_report_key', $this->mdr_report_key, \PDO::PARAM_INT);
            
       $insert_stmt->bindParam(':text_report', $this->text_report, \PDO::PARAM_STR);
    
       $insert_stmt->bindParam(':date_received', $this->date_received, \PDO::PARAM_STR);
    
       $insert_stmt->bindParam(':report_source_code', $this->report_source_code, \PDO::PARAM_STR);
    } 
    
    protected function insert()
    {
       $this->insert_count = 0;

       $this->pdo->beginTransaction(); 

       try { 

          foreach ($this->pdo->query($this->select_query) as $row) {
       
              $this->mdr_report_key = intval($row['mdr_report_key']);
       
              $this->text_report =  $row['text_report'];
       
              $this->date_received =  $row['date_received'];
       
              $this->report_source_code =  $row['report_source_code'];
       
              $this->insert_stmt->execute();
    
              ++$this->insert_count;
          }

          $this->pdo->commit();

       } catch (\PDOException $e) {
      
           $errors = "\nException Thrown in " . $e->getFile() . " at line " . $e->getLine() . "\n";
              
           $errors .= "Stack Trace as string:\n" . $e->getTraceAsString() . "\n";
                  
           $errors .= "Error message is: " .   $e->getMessage() . "\n";
              
           echo $errors;
       } 
      } 
}
