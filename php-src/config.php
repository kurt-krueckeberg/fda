<?php
// This file is included by prep-files.php.  It has the thee categories of input files to the downloaded, catenated, sorted, and scrubbed
// to make them ready for the ~/fda code to read, extract new records and insert them into maude_medwatch.medwatch_report table.
// Note: These are only the files to add the latest records to the medwatch_report table. To build the maude tables and the medwatch_report
// table from scratch, all the necessary files starting from ~1998 would also have to be added to these three arrays.
$device = array("foidev.zip", "foidevadd.zip");
$mdr   =  array("mdrfoi.zip", "mdrfoiadd.zip" );
$text  =  array("foitext.zip", "foitextadd.zip");

$config['files_map'] = array('device' => $device, 'mdr' => $mdr, 'text' => $text);

$config['download-dir'] = "../data";
?>
