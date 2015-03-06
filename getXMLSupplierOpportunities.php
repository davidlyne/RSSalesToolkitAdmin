<?php
header('Content-Type: application/xml');
require_once("common.inc");

echo "<SupplierOpportunitiesList>\n";
$result = mysql_query("SELECT * FROM supplieropportunities");
$currentURL = "http://$_SERVER[HTTP_HOST]";


for ($i=0;$i<count($designTools);$i++)
 {
	echo "<SupplierOpportunities>\n";
	echo "<DesignTool>".$designTools[$i]."</DesignTool>\n";
	echo "<PDF>".$currentURL."/".getSupplierOpportunitiesPDF($i)."</PDF>\n";
	echo "</SupplierOpportunities>\n";
	
 }
echo "</SupplierOpportunitiesList>";
?>