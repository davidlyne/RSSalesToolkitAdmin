

<?php

	
	if ($sotool == "")
	{
		include "mainmenu.inc";
	}
	else
	{				
		switch ($sotool)
		{
			case "SUPPLIEROPPORTUNITIESLIST":
			{
				//if (array_key_exists("ADDNEWCOMMSPACK",$_POST) == TRUE)
				//	addCommsPack();
					
				if (array_key_exists("EDITSUPPLIEROPPORTUNITIES",$_POST) == TRUE)
					updateSupplierOpportunities($_POST["EDITSUPPLIEROPPORTUNITIES"]);
					
				//if (array_key_exists("DELETECOMMSPACK",$_GET) == TRUE)
				//{
				//	$id = $_GET["DELETECOMMSPACK"];
				//	mysql_query("DELETE FROM producthighlightscommspack WHERE ID=".$id); 
				//}
				
				include "supplieropportunitieslist.inc";
			}
			break;
			case "SUPPLIEROPPORTUNITIESEDIT":
			{
				
				include "editsupplieropportunities.inc";
			}
			break;
			
		}
	}
?>

