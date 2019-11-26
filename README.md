# FDA Maude Lasik Data Extraction code

## Required Packages

1.  librapidxml-dev -- rapidxml library
2.  libmysqlcppconn-dev -- MySQL Connector for C++ (development files)  

## Compile and Linker Settings

1. **-std=c++2a** implementation to create maude and medwatch databases and update them. 
2. **include** path should have "include" subdirectory.
3. link library for working with MySQL: **libmysqlcppconn.so**, which is in **/usr/lib/x86\_64-linux-gnu**.

## Comments

The **medwatch** database contains all the lasik adverse event reports since 1998. Its single medwatch\_report table was built from joining data
from the three tables in the Maude database.  To extract the LASIK data from the Maude foi .txt files and insert it into the medwatch database, run 

    php -f fetch-files.php 

The code is driven by the **config.xml file**, which is self explanatory.

## Overview

1. The common field link between the device file, the mdrfoi file, and text file is Mdr Report Key

2. From the Device File you need fields
    1 - MDR Report Key
   26 - Device Report Product Codes for codes of "HNO" or "LZS" (those are the laser product codes)

3. From the MDRFOI File, you need fields:
    1 MDR Report Key,
    4 - Report Source Code (i.e. patient reports are typically "P"-voluntary reports) and
   12 - Date of Event (from the date of event, you'll ultimately get the file year)

4. From the Text File, you need field # 1 MDR Report Key and field # 6 Text

The steps I've used in the past are as follows:

1. Relate the tables on the common field Mdr Report Key to bring in the required fields from the 3 tables.
2. Remove all device report product codes not equal to HNO or LZS
3. Create a File Year based on the # 12-Date of Event
4. The  3 AE notes from the output file above is a manual process after export of the FDA MAUDE files and reading the text to categorize whether each filing
   is for dry eyes, NVD, ectasia, etc.

Programmatic Perspective
------------------------

 From foidev file we extract these fields:

    1. MDR report key
   26. Device Report Product Code equal to "HNO" or "LZS". These are the laser product codes.

I just take the first HNO or LZS record found. Save this in foi\_device.

 From the mdrfoi file take these fields

    1. MDR report key
    4. Report Source Code
   12. Date of Event

 save this in mdr\_foi. Eliminate duplicate rows from it.
 
 From the foitext file take

    1. MDR Report Key
    6. Text

save this in foi\_text.

Steps I Use
-----------

1. The maude\_medwatch database contains devicefoi, mdrfoi, textfoi and medwatch\_report tables. The SQL for creating these is below. All these tables--EXCEPT medwatch\_report--
should be empty. The code will delete the rows before running.  

2. Use maude.sql to create temporary tables to hold the new lasik records that we find in maude .txt files

    - foidevice
    - foimdr
    - foitext

```sql

    SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
    SET time_zone = "+00:00";

    --
    -- Database: `maude`
    --
    
    -- --------------------------------------------------------
    
    -- 
    -- Table structure for table `foi_device`
    
    CREATE TABLE IF NOT EXISTS `devicefoi` (
      `mdr_report_key` int(11) unsigned NOT NULL,
      `device_product_code` char(3) NOT NULL,
      PRIMARY KEY(mdr_report_key, device_product_code) 
    ) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
    
    CREATE TABLE IF NOT EXISTS `mdrfoi` (
      `mdr_report_key` int(11) unsigned NOT NULL,
      `report_source_code` CHAR(1) NOT NULL,
      `date_received` DATE NOT NULL,
      FOREIGN KEY (mdr_report_key) REFERENCES devicefoi (mdr_report_key),
      PRIMARY KEY (mdr_report_key)
    ) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;
    
    CREATE TABLE IF NOT EXISTS `textfoi` (
      mdr_report_key int(11) unsigned NOT NULL,
      text_report TEXT,
      FOREIGN KEY (mdr_report_key) REFERENCES devicefoi (mdr_report_key),
      PRIMARY KEY (mdr_report_key)
    ) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;
    
    
    CREATE TABLE IF NOT EXISTS medwatch_report (
      `id` int(11) NOT NULL AUTO_INCREMENT,
      `mdr_report_key` int(11) unsigned NOT NULL,
      `text_report` longtext NOT NULL,
      `date_received` date NOT NULL,
      `report_source_code` char(1) NOT NULL,
      `word_cnt` INT NOT NULL,
       UNIQUE(mdr_report_key),
       PRIMARY KEY(id)
    ) ENGINE=MyIsam DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;

    /* 1. MDR Report Key */
    /* 2. MDR Text Key */
    /* 3. Text Type Code (D=B5, E=H3, N=H10 from mdr_text table) */
    /* 4. Patient Sequence Number (from mdr_text table) */
    /* 5. Date Report (from mdr_text table) */
    /* 6. Text (B5, or H3 or H10 from mdr_text table) */


3. To prepare the maude .txt files
    
    Edit php-src/config.php. Then run php-src/prep-file.php.
       
       cd php-src
       php -f  prep-files.php

   See prep-files.php for an explanation of what it does.
    
4. If the above .txt files contain a lot of old data that already exists in the medwatch table, we can be be manually remove this redundant data by
    
        1. First determing the max(medwatch.mdr_report_key) in the current medwatch table.
    
          $ mysql -u root -p -D maude_whatever
          $ select max(mdr_report_key) as max from medwatch_report;
    
        2. Then delete those row whose MDR REPORT KEY is less than this max value by running ./rewrite.php, after first setting the $max_mdr_report_key 
           variable in rewrite.php.

        3. Copy the newly written .new files over the existing *-all.txt files.
       
5. Change the xml-config.xml so that it contains the correctly named files in ./data
  
6. Run php -f fetch.php  

7. Views ...of count(device_product_code) GROUP BY Year:

    select count(`dev`.`device_product_code`) AS `count(device_product_code)`,year(`mdr`.`date_received`) AS `YEAR(date_received)` from
     (`maude_permanent`.`devicefoi` `dev` join `maude_permanent`.`mdrfoi` `mdr` on((`dev`.`mdr_report_key` = `mdr`.`mdr_report_key`))) 
    where (`dev`.`device_product_code` = 'HNO') 
    group by year(`mdr`.`date_received`)

 select count(`dev`.`device_product_code`) AS `count(device_product_code)`,year(`mdr`.`date_received`) AS `YEAR(date_received)` from
     (`maude_permanent`.`devicefoi` `dev` join `maude_permanent`.`mdrfoi` `mdr` on((`dev`.`mdr_report_key` = `mdr`.`mdr_report_key`))) 
    where (`dev`.`device_product_code` = 'LZS') 
    group by year(`mdr`.`date_received`)

Inset on Parsing
~~~~~~~~~~~~~~~~
    
The parsing of each file works like this:

1. Parses foidev.txt looking for Device Product Codes equal to "HNO" or "LSZ", excimer lasik or microkeratome records. Compares the MDR Report Key's of this row
   with the max(mdr\_report\_key) from the medwatch\_report table. Writes the MDR Report Key and Device Product Code to the foidevice table if its MDR Report Key
   is greater than the max found above. 

2. Parses mdrfoi.txt file extracting the fields

   1.) MDR Report Key
   2.) Report Source Code (i.e. patient reports are typically "P"-voluntary reports)
   3.) Date of Event. 

   If the MDR Report Key was inserted in step #1 and therefore exists in the foidevice.txt table, save these three fields to the mdrfoi table.

3. Parse the foitext.txt file and extract the MDR Report Key and Text Report fields. Again, if the MDR Report Key is in the foidevice table (as well as the mdrfoi
   table), write these two fields to the foitext table, checking first that they have not already been inserted.

5. Join the results of these three tables and insert the result into the medwatch\_report table.

6. The records in devicefoi, mdrfoi and textfoi tables can now be deleted (but the tables retained).
