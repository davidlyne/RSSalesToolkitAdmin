<?php
header('Content-Type: application/json');
require_once("common.inc");

$parentid = $_GET['id'];


if (!isset($parentid) || !is_numeric($parentid))
    $reponse = array('success' => FALSE);
else {

	$options = "";
	$result = mysql_query("SELECT * FROM producthighlightscategory WHERE Parent=".$parentid);
	$i=0;
	$row = mysql_fetch_array($result);
	$options = $row["ID"];

	
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