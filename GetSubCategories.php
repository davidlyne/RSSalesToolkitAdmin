<?php
header('Content-Type: application/json');
require_once("common.inc");

$parentid = $_GET['id'];

if (array_key_exists("selectid",$_GET) == TRUE)
	$selectid = $_GET['selectid'];
else
	$selectid = 0;

if (array_key_exists("doselection",$_GET) == TRUE)
	$doselection = $_GET['doselection'];
else
	$doselection = 0;

if ($doselection == "false")
	$doselection = 1;
else
	$doselection = 0;
	
if (!isset($parentid) || !is_numeric($parentid))
    $reponse = array('success' => FALSE);
else {

	$options = "";
	$result = Database::Query("SELECT * FROM producthighlightscategory WHERE Parent=".$parentid);
	$i=0;
	while($row = Database::FetchArray($result))
	{
		$options .= '<option value="'. $row["ID"] .'"';
		if ($row["ID"] == $selectid && $doselection > 0)
				$options .= "selected ";
		$options .= '>'. $row["Name"] .'</option>';
		$i++;
	}
	
	
	if ($options == "")
	{
		$response = array(
			'success' => FALSE,
			'options' => $options
		);	
	}else
	{
		$response = array(
			'success' => TRUE,
			'options' => $options
		);
	}
}


echo json_encode($response);
?>