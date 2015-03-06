<?php
header('Content-Type: application/xml');
require_once("common.inc");

echo "<ProductList>\n";
$result = mysql_query("SELECT * FROM producthighlightsproduct");
$currentURL = "http://$_SERVER[HTTP_HOST]";
echo "<NumProducts>".getNumProducts()."</NumProducts>\n";


 while($row = mysql_fetch_array($result))
 {
	echo "<Product>\n";
	echo "<Name>".htmlspecialchars($row['Name'])."</Name>\n";
	echo "<Category>".htmlspecialchars(getProductCategoryPath($row['ID']))."</Category>\n";
	echo "<Brand>".htmlspecialchars($row['Brand'])."</Brand>\n";
	echo "<StockNo>".htmlspecialchars($row['StockNo'])."</StockNo>\n";
	echo "<BestSelling>".getBoolYesNo($row['BestSelling'])."</BestSelling>\n";
	echo "<URL>".$row['URL']."</URL>\n";
	echo "<Image1>".$currentURL."/".$row['Image1']."</Image1>\n";
	if ($row['Image2'] != "")
		echo "<Image2>".$currentURL."/".$row['Image2']."</Image2>\n";
	if ($row['Image3'] != "")	
		echo "<Image3>".htmlspecialchars($currentURL."/".$row['Image3'])."</Image3>\n";
	echo "<ShortDesc>".htmlspecialchars($row['ShortDesc'], ENT_QUOTES, 'UTF-8')."</ShortDesc>\n";
	echo "<LongDesc>".htmlspecialchars($row['LongDesc'], ENT_QUOTES, 'UTF-8')."</LongDesc>\n";
	echo "</Product>\n";

 }
echo "</ProductList>";
?>