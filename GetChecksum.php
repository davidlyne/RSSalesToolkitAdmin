<?php
require_once("common.inc");

//$result = mysql_query("SELECT UPDATE_TIME FROM information_schema.tables WHERE TABLE_SCHEMA='".$dbname."' AND TABLE_NAME='producthighlightsproduct'");
$result = mysql_query("CHECKSUM TABLE producthighlightsproduct");
$row = mysql_fetch_array($result);
$checksum = $row['Checksum'];

$result = mysql_query("CHECKSUM TABLE producthighlightscategory");
$row = mysql_fetch_array($result);
$checksum += $row['Checksum'];

$result = mysql_query("CHECKSUM TABLE producthighlightscommspack");
$row = mysql_fetch_array($result);
$checksum += $row['Checksum'];

$result = mysql_query("CHECKSUM TABLE supplieropportunities");
$row = mysql_fetch_array($result);
$checksum += $row['Checksum'];

echo $checksum;

?>