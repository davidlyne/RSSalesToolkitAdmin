<?php
header('Content-Type: application/xml');
require_once("common.inc");

echo "<CommsPackList>\n";
$result = Database::Query("SELECT * FROM producthighlightscommspack ORDER BY Timestamp DESC");
$currentURL = "http://$_SERVER[HTTP_HOST]";
echo "<NumCommsPacks>".getNumCommsPacks()."</NumCommsPacks>\n";


 while($row = Database::FetchArray($result))
 {
	echo "<CommsPack>\n";
	echo "<Name>".htmlspecialchars($row['Name'])."</Name>\n";
	echo "<Category>".htmlspecialchars(getCommsPackCategoryPath($row['ID']))."</Category>\n";
	echo "<PDF>".$currentURL."/".$row['PDF']."</PDF>\n";
	echo "</CommsPack>\n";

 }
echo "</CommsPackList>";
?>