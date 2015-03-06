<?php
require_once("common.inc");

//$result = mysql_query("SELECT UPDATE_TIME FROM information_schema.tables WHERE TABLE_SCHEMA='".$dbname."' AND TABLE_NAME='producthighlightsproduct'");
$result = Database::Query("CHECKSUM TABLE producthighlightsproduct");
$row = Database::FetchArray($result);
$checksum = $row['Checksum'];

$result = Database::Query("CHECKSUM TABLE producthighlightscategory");
$row = Database::FetchArray($result);
$checksum += $row['Checksum'];

$result = Database::Query("CHECKSUM TABLE producthighlightscommspack");
$row = Database::FetchArray($result);
$checksum += $row['Checksum'];

$result = Database::Query("CHECKSUM TABLE supplieropportunities");
$row = Database::FetchArray($result);
$checksum += $row['Checksum'];

echo $checksum;

?>