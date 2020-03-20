<?php
require_once "config.php"; 
require_once "utilities.php";

function make_recursive_iteriter($dir)
{
  return new \RecursiveIteratorIterator(new \RecursiveArrayIterator($dir));
}

  $files_map = $config['files_map']; // <-- confirm this is a map TODO
 
  $recurs_iter = make_recursive_iteriter($files_map); // What does this type of iterative do
 
  $download_dir = $config['download-dir'];

  // Download files from the URL (in first parameter) to the directory in the 2n parameter.
  download_files("https://www.accessdata.fda.gov/MAUDE/ftparea/", $download_dir, $recurs_iter); 
 
  // Unzip the files.
  unzip_files($download_dir, $recurs_iter);

  rename_lowercase($download_dir, "txt"); // Changes the file names that end in .txt to be all lowercase.

  // Changes the extension of all files in the map to .txt?
  // This doesn't seem to do anything. <---------- TODO
  $recurs_iter = change_extension($files_map); 

   // What do these parameters mean?
  convert_files($download_dir, ".tmp", $recurs_iter);  

  $output_files = concatenate($config['files_map'], "txt.tmp", $download_dir);

  remove_duplicates($output_files);

  echo "===> DONE: Now manually edit the xxx-all.txt files because the first several lines, if you are fetching new data, may be erroneously formatted. mdr-all.txt will certainly be!\n";
