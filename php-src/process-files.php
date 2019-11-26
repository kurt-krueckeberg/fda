<?php
//--require_once "config.php"; 
require_once "utilities.php";

$config['files'] = array('foidev2018.zip', 'foidevadd.zip', 'foidev.zip', 'foitext2018.zip', 'foitextadd.zip', 'mdrfoiadd.zip', 'mdrfoi.zip');

$recurs_iter = new \RecursiveIteratorIterator(new \RecursiveArrayIterator($config['files']) );

//--download_files("https://www.accessdata.fda.gov/MAUDE/ftparea/", $download_dir, $recurs_iter);
 
unzip_files($config['download-dir'], $recurs_iter);

rename_lowercase($download_dir, "txt");
  
$recurs_iter = change_extension($config['files']); 
 
$tmp_ext = ".tmp"; // The working files will be new files ending in .tmp, and the original files will be untouched.
 
convert_files($download_dir, ".tmp", $recurs_iter); 

$output_files = concatenate($config['files'], "txt.tmp", $download_dir);

remove_duplicates($output_files);

echo "===> DONE: Now manually edit the xxx-all.txt files because the first several lines, if you are fetching new data, may be erroneously formatted. mdr-all.txt will certainly be!\n";
