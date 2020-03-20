<?php

function download_files(string $url_prefix, string $download_dir, \RecursiveIteratorIterator $iter)
{
  $curl_prefix = 'curl -O ';

  $cmd = '';

  foreach($iter as $file_name) {
      
      $cmd = $curl_prefix . $url_prefix . $file_name;

      echo "\nDownloading $file_name...\n";

      exec( $cmd );
      
      $mv_cmd = 'mv  ' . "./$file_name $download_dir";

      echo "\nMoving $file_name to $download_dir\n";

      exec($mv_cmd);
  }

  return;
}

function unzip_files(string $download_dir, \RecursiveIteratorIterator $iter)
{
  foreach ($iter as $file_name) {

     $actual_file = $download_dir . "/$file_name";
    
     $unzip_cmd = "unzip -o -d $download_dir $actual_file"; // -o is force overwrite, if needed, -ext is output directory.

     echo "\n $unzip_cmd\n";

     exec($unzip_cmd);
   }
}
/*
 * TODO: Rename all the files in directory dir
 */
function rename_lowercase(string $dir, string $ext)
{
 foreach (new DirectoryIterator($dir) as $fileInfo) {

    if(!$fileInfo->isDot() && $fileInfo->getExtension() == 'txt'){

        $file = $fileInfo->getBasename();

        $newFile = strtolower($file);

        $path = $fileInfo->getPath();    
        
        rename($path .DIRECTORY_SEPARATOR . $file, $path . DIRECTORY_SEPARATOR . DIRECTORY_SEPARATOR . $newFile);
    }
  }
}

/* 
 * Alters the extension of all file names in $files array to be .txt
 * Returns iterator to newly changed array
 */
function change_extension(&$files) : \RecursiveIteratorIterator
{
  array_walk_recursive ($files, function(&$fname) {
     $ext_index = strpos($fname, ".");
     $fname = substr_replace($fname, ".txt", $ext_index);} 
    );


  return  new \RecursiveIteratorIterator(new \RecursiveArrayIterator($files) );
}  

function convert_files(string $download_dir, string $tmp_ext, \RecursiveIteratorIterator $iter)
{
 foreach($iter as $file_name) {
     
     $actual_file = $download_dir . "/$file_name";   
     
     convert_file($tmp_ext, $actual_file);      
 }
}

/* 
   Prepare_files:

1. Removes all control characters
2. Converts file from DOS format to Linux fomrat
3. Removes first line column header

Requirements: sponge package must be installed.
 */
function convert_file($tmp_ext, $file)
{
    $tmp = $file . $tmp_ext;

    echo "Creating temp file $tmp\n";

    exec( "cp $file $tmp");

    // 1. Remove control characters
    echo "Removing control characters from $tmp.\n";

    $tr_cmd =  "tr -cd '\\11\\12\\15\\40-\\176'" . "< " . $tmp . " | sponge $tmp";

    exec( $tr_cmd );

    // 2. Do dos2unix
    echo "Doing dos2unix $tmp\n";

    $dos2unix_cmd = "dos2unix $tmp";

    exec ($dos2unix_cmd); 

    // 3. Remove header line
    echo "Removing first line header from $tmp.\n";

    $remove_1st =  "tail -n +2 $tmp | sponge $tmp";

    exec ($remove_1st); 
}
/*
 * Removes all duplicate lines
 */
/*
function remove_duplicates(string $file)
{
    // sort $file
    $cmd_sort =  "sort -t\"|\" -n -k 1 $file | sponge $file";

    exec($cmd_sort);

    // Remove duplicates
    $cmd_remove_dups =  "uniq -u $file | sponge $file";

    echo "Removing duplicate lines from $file.\n";

    exec($cmd_remove_dups);
}
*/
function remove_duplicates(array $files) : void
{
 foreach($files as $file) {

    // sort $file
    $cmd_sort =  "sort -t\"|\" -n -k 1 $file | sponge $file";

    exec($cmd_sort);

    // Remove duplicates
    $cmd_remove_dups =  "uniq -u $file | sponge $file";

    echo "Removing duplicate lines from $file.\n";

    exec($cmd_remove_dups);
 }
}

function concatenate(array $files, string $ext, string $dir) : array
{
  $output_files = array();

  foreach ($files as $key => $zip_files) {
      
     foreach($zip_files as $zip_file) {
     
        $cmd = "cat ";
     
        $fname = "$dir/" . substr($zip_file, 0, strpos($zip_file, '.')) .  ".$ext";
     
        $cmd .= $fname . ' ';
     
        $output = "$dir/" . $key . "-all.txt"; 
        
        $cmd .= " >> $output";
        
        exec($cmd);
     } 
     
     array_push($output_files, $output);

     echo "\n$output created.\n";
  }
  return $output_files;
}
/*
function concatenate(string $in, string $out)
{
   echo "Doing: cat $in > $out\n";

   // catenate all text files into one big files.
   $cmd_concat = "cat $in > $out"; //foitext*.txt > foitext-all.txt";

   exec($cmd_concat);

   echo "\n$out created.\n";
}
*/
?>
