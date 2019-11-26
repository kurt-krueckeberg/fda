<?php
use Maude\SplFileObjectExtended;

require_once("php-src/SplClassLoader.php");

function boot_strap()
{
 $spl_loader = new SplClassLoader('Maude', 'php-src');

 $spl_loader->register();
};

boot_strap();

$files = array("foidev-all.txt", "foitext-all.txt", "mdrfoi-all.txt");

foreach ($files as $file) {

    $file_name = "./data/" . $file;

    echo "Processing " . $file_name . "\n";
        
    $fin =  new SplFileObjectExtended($file_name);
    
    $fout = $file_name . ".new"; 

    $fileinfo = new SplFileInfo($fout);

    $fout = $fileinfo->openFile('w');
    
    rewrite($fin, $fout, 6068586);
}

function rewrite(\SplFileObject $in, \SplFileObject $out, $max)
{
  foreach ($in as $line) {

     $matches;

     preg_match("/^(\d+)|/", $line, $matches);    
    
     $mdr_report_key = intval($matches[1]);
    
     if ($mdr_report_key <= $max) continue;
         
     $out->fwrite($line);
     
   }
}
