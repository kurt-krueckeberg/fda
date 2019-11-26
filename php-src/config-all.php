<?php

// mdrfoi
$mdr = array(
"mdrfoithru2018.zip",
"mdrfoi.zip",
"mdrfoiadd.zip"
);

// foidev
$device = array(
"foidevthru1997.zip",
"foidev1998.zip",
"foidev1999.zip",
"foidev2000.zip",
"foidev2001.zip",
"foidev2002.zip",
"foidev2003.zip",
"foidev2004.zip",
"foidev2005.zip",
"foidev2006.zip",
"foidev2007.zip",
"foidev2008.zip",
"foidev2009.zip",
"foidev2010.zip",
"foidev2011.zip",
"foidev2012.zip",
"foidev2013.zip",
"foidev2014.zip",
"foidev2015.zip",
"foidev2016.zip",
"foidev2017.zip",
"foidev2018.zip",
"foidev.zip",
"foidevadd.zip"
);

//foitext
$text = array(
"foitextthru1995.zip",
"foitext1996.zip",
"foitext1997.zip",
"foitext1998.zip",
"foitext1999.zip",
"foitext2000.zip",
"foitext2001.zip",
"foitext2002.zip",
"foitext2003.zip",
"foitext2004.zip",
"foitext2005.zip",
"foitext2006.zip",
"foitext2007.zip",
"foitext2008.zip",
"foitext2009.zip",
"foitext2010.zip",
"foitext2011.zip",
"foitext2012.zip",
"foitext2013.zip",
"foitext2014.zip",
"foitext2015.zip",
"foitext2016.zip",
"foitext2017.zip",
"foitext2018.zip",
"foitext.zip",
"foitextadd.zip"
);

// To simply add the latest records to the database, use someting like this:
/*
$device = array("foidev2017.zip", "foidev.zip", "foidevadd.zip");
$mdr   =  array("mdrfoithru2017.zip", "mdrfoi.zip", "mdrfoiadd.zip" );
$text  =  array("foitext2017.zip", "foitext.zip", "foitextadd.zip");
*/
/*

 The year to date files for 2019 still reference 2018--at least for foitext*.zip and foidev*.zip, but this is not true for mdr.
 TODO: Fix out which files have only 2019 data and which have both 2019 and 2019?
$device = array("foidev2018.zip", "foidevadd.zip");
$mdr   =  array("mdrfoithru2018.zip", "mdrfoiadd.zip" );
$text  =  array("foitext2018.zip", "foitextadd.zip");

*/

/* To build the maude_medwatch database from scratch use all the foi files, which would be something line this:
$device = array("foidevthru1997.zip", "foidev1998.zip", "foidev1999.zip", "foidev2000.zip", "foidev2001.zip", "foidev2002.zip", "foidev2003.zip", "foidev2004.zip", "foidev2005.zip", "foidev2006.zip", "foidev2007.zip", "foidev2008.zip", "foidev2009.zip", "foidev2010.zip", "foidev2011.zip", "foidev2012.zip", "foidev2013.zip", "foidev2014.zip", "foidev2015.zip", "foidev2016.zip", "foidev2017.zip", "foidev.zip", "foidevadd.zip");

$mdr = array("mdrfoithru2017.zip", "mdrfoi.zip", "mdrfoiadd.zip"); 

$text = array("foitextthru1995.zip", "foitext1996.zip", "foitext1997.zip", "foitext1998.zip", "foitext1999.zip", "foitext2000.zip", "foitext2001.zip", "foitext2002.zip", "foitext2003.zip", "foitext2004.zip", "foitext2005.zip", "foitext2006.zip", "foitext2007.zip", "foitext2008.zip", "foitext2009.zip", "foitext2010.zip", "foitext2011.zip", "foitext2012.zip", "foitext2013.zip", "foitext2014.zip", "foitext2015.zip", "foitext2016.zip", "foitext2017.zip", "foitext.zip", "foitextadd.zip");
*/

$config['files'] = array('device' => $device, 'mdr' => $mdr, 'text' => $text);

$config['download-dir'] = "../data";
?>
