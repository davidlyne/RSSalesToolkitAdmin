

<?php

	$currentCategory = 0;
	if (array_key_exists("CATEGORYID",$_GET) == TRUE)
	{
		$currentCategory = $_GET["CATEGORYID"];
	}
	
	if ($phtool == "")
	{
		include "mainmenu.inc";
	}
	else
	{				
		switch ($phtool)
		{
			case "COMMSPACKLIST":
			{
				if (array_key_exists("ADDNEWCOMMSPACK",$_POST) == TRUE)
					addCommsPack();
					
				if (array_key_exists("EDITCOMMSPACK",$_POST) == TRUE)
					updateCommsPack($_POST["EDITCOMMSPACK"]);
					
				if (array_key_exists("DELETECOMMSPACK",$_GET) == TRUE)
				{
					$id = $_GET["DELETECOMMSPACK"];
					mysql_query("DELETE FROM producthighlightscommspack WHERE ID=".$id); 
				}
				
				include "commspacklist.inc";
			}
			break;
			case "ADDCOMMSPACK":
			{
				include "addcommspack.inc";
			}
			break;
			case "EDITCOMMSPACK":
			{
				include "addcommspack.inc";
			}
			break;
			case "PRODUCTLIST":
			{
				if (array_key_exists("ADDNEWPRODUCT",$_POST) == TRUE)
					addProduct();
					
				if (array_key_exists("EDITPRODUCT",$_POST) == TRUE)
					updateProduct($_POST["EDITPRODUCT"]);
					
				if (array_key_exists("DELETEPRODUCT",$_GET) == TRUE)
				{
					$id = $_GET["DELETEPRODUCT"];
					mysql_query("DELETE FROM producthighlightsproduct WHERE ID=".$id); 
				}
				
				include "productlist.inc";
			}
			break;
			case "ADDPRODUCT":
			{
				include "addproduct.inc";
			}
			break;
			case "EDITPRODUCT":
			{
				include "addproduct.inc";
			}
			break;
			case "DELETECOMMSPACK":
			{
				$deleteid = $_GET["DELETECOMMSPACK"];
				$result = mysql_query("SELECT * FROM producthighlightscommspack WHERE ID=$deleteid");
				$row = mysql_fetch_array($result);
				$commspackname = $row["Name"];
					
				?>
				<div class="wrapper">
				
				<h1>Delete Comms Pack</h1>
				
				<form class="left-inputs">
				Confirm deletion of <b><?php echo $commspackname; ?></b> product?
                <p><br>
				<input type="hidden" name="NAV" value="PHADMIN">
				<input type="hidden" name="PHTOOL" value="COMMSPACKLIST">
				<input type="hidden" name="DELETECOMMSPACK" value="<?php echo $_GET["DELETECOMMSPACK"];?>">
				
				
				<p>
				<button>Yes</button>
				<a href='<?php echo $productHighlightsCommsPacks;?>'><button type="button" >No</button></a>
				</form>

				</div>
				
				<?php
			}
			break;
			case "DELETEPRODUCT":
			{
				$deleteid = $_GET["DELETEPRODUCT"];
				$result = mysql_query("SELECT * FROM producthighlightsproduct WHERE ID=$deleteid");
				$row = mysql_fetch_array($result);
				$productname = $row["Name"];
					
				?>
				<div class="wrapper">
				
				<h1>Delete Product Highlights Product</h1>
				
				<form class="left-inputs">
				Confirm deletion of <b><?php echo $productname; ?></b> product?
                <p><br>
				<input type="hidden" name="NAV" value="PHADMIN">
				<input type="hidden" name="PHTOOL" value="PRODUCTLIST">
				<input type="hidden" name="DELETEPRODUCT" value="<?php echo $_GET["DELETEPRODUCT"];?>">
				
				
				<p>
				<button>Yes</button>
				<a href='<?php echo $productHighlightsProducts;?>'><button type="button" >No</button></a>
				</form>

				</div>
				
				<?php
			}
			break;
			case "DELETECATEGORY":
			{
				$deleteid = $_GET["DELETECATEGORY"];
				$result = mysql_query("SELECT * FROM producthighlightscategory WHERE ID=$deleteid");
				$row = mysql_fetch_array($result);
				$catname = $row["Name"];
					
				?>
				<div class="wrapper">
				
				<h1>Delete Product Highlights Category</h1>
				
				<form class="left-inputs">
				Confirm deletion of <b><?php echo $catname; ?></b> category?
                <p><br>
				<input type="hidden" name="NAV" value="PHADMIN">
				<input type="hidden" name="PHTOOL" value="CATEGORIES">
				<input type="hidden" name="CATEGORYID" value="<?php echo $currentCategory;?>">
				<input type="hidden" name="DELETECATEGORY" value="<?php echo $_GET["DELETECATEGORY"];?>">
				
				
				<p>
				<button>Yes</button>
				<a href='<?php echo $productHighlightsCategories."&CATEGORYID=".$currentCategory;?>'><button type="button" >No</button></a>
				</form>

				</div>
				
				<?php
			}
			break;
			case "EDITCATEGORY":
			{
			
				echo '<div class="wrapper">';
				
				$catname = "";
				$editid = 0;
				if (array_key_exists("ID",$_GET) == TRUE)
				{
					$editid = $_GET["ID"];
					$result = mysql_query("SELECT * FROM producthighlightscategory WHERE ID=$editid");
					$row = mysql_fetch_array($result);
					$catname = $row["Name"];
					echo '<h1>Edit Product Highlights Category</h1>';
				}else
					echo '<h1>Add Product Highlights Category</h1>';	
					
				?>

				
				<form class="left-inputs">
                <label>Category Name</label>
                <input name="CATEGORYNAME" value="<?php echo $catname; ?>">
				<input type="hidden" name="NAV" value="PHADMIN">
				<input type="hidden" name="PHTOOL" value="CATEGORIES">
				<input type="hidden" name="CATEGORYID" value="<?php echo $currentCategory;?>">
				<?php
				if ($editid > 0)
				{
					echo '<input type="hidden" name="EDITCATEGORYID" value="'.$editid.'">';
				}
				?>
				<p>
				<button>Done</button>
				<a href='<?php echo $productHighlightsCategories."&CATEGORYID=".$currentCategory;?>'><button type="button" >Cancel</button></a>
				</form>

				</div>
				<?php
			}
			break;
			case "CATEGORIES":
			{
				echo '<div class="wrapper">';
				echo '<h1>Product Highlights Categories</h1>';

				

				// Bread crumbs

				$breadcrumb = $currentCategory;
				$i=0;
				while ($breadcrumb != 0)
				{
					$result = mysql_query("SELECT * FROM producthighlightscategory WHERE ID=$breadcrumb");
					$row = mysql_fetch_array($result);
					
					$breadcrumb = $row["Parent"];
					$breadcrumbs[$i] = $row["ID"];
					$i++;
				}
				
				$k=0;
				if ($currentCategory == 0)
				{
					echo '<div class="breadcrumb flat">';
					echo "<a href='".$productHighlightsCategories."' class='active'>";
					echo 'Top';
					echo "</a>";	
				}else
				{
					echo '<div class="breadcrumb flat">';
					echo "<a href='".$productHighlightsCategories."'>";
					echo 'Top';
					echo "</a>";	
				}


				for ($j = $i-1;$j>=0;$j--)
				{
					$id = $breadcrumbs[$j];
					$result = mysql_query("SELECT * FROM producthighlightscategory WHERE ID=$id");
					$row = mysql_fetch_array($result);
					
					$active = "";
					if ($currentCategory == $id)
						$active = 'class="active"';
						
					echo "<a href='".$productHighlightsCategories."&CATEGORYID=".$id."' ".$active.">";
					echo $row["Name"];
					echo "</a>";
					$k++;
				}
				echo "</div>";
				echo "<p>";
			
				echo "<a href='".$productHighlightsTop."'><button class='add'>Back</button></a> ";
				echo "<a href='".$productHighlightsEditCategory."&CATEGORYID=".$currentCategory."'><button class='add'>Add Category</button></a>";
				if (array_key_exists("CATEGORYNAME",$_GET) == TRUE && array_key_exists("EDITCATEGORYID",$_GET) == FALSE )
				{
					// insert new category
					$catname = $_GET["CATEGORYNAME"];
					$parentid = $currentCategory;
					mysql_query("INSERT INTO producthighlightscategory (Name, Parent) VALUES('$catname', '$parentid' ) "); 
				}else if (array_key_exists("CATEGORYNAME",$_GET) == TRUE && array_key_exists("EDITCATEGORYID",$_GET) == TRUE )
				{
					// update category
					$catname = $_GET["CATEGORYNAME"];
					$catid = $_GET["EDITCATEGORYID"];
					
					mysql_query("UPDATE producthighlightscategory SET Name='$catname' WHERE ID='$catid'"); 
				} 
				
				if (array_key_exists("DELETECATEGORY",$_GET) == TRUE)
				{
					$id = $_GET["DELETECATEGORY"];
					mysql_query("DELETE FROM producthighlightscategory WHERE ID=".$id); 
				}
				
				 $result = mysql_query("SELECT * FROM producthighlightscategory WHERE Parent=$currentCategory");
				?>
				<table>
				<thead>
					<th width='70%'>Category name</th>
					<th>No. Subcategories</th>
					<th>Edit</th>
					<th>Delete</th>

				</thead>
			
					
				 <?php
				 while($row = mysql_fetch_array($result))
				 {
					$numSubCats = getNumSubCategories($row['ID']);
					echo "<tr>";					
					echo "<td width='70%'><a href='".$productHighlightsCategories."&CATEGORYID=".$row['ID']."'>".$row['Name']."</a></td>";
					echo "<td>";
					if ($numSubCats > 0)
						echo "<b>";
					echo $numSubCats;
					if ($numSubCats > 0)
						echo "</b>";
					echo "</td>";
					echo "<td><a href='".$productHighlightsEditCategory."&CATEGORYID=".$currentCategory."&ID=".$row['ID']."'><button>Edit</button></a></td>";
					echo "<td><a href='".$productHighlightsDeleteCategory."&CATEGORYID=".$currentCategory."&DELETECATEGORY=".$row['ID']."'><button class=delete>Delete</button></a></td>";
					echo "</tr>";
				 }
				
				echo "</table>";
				
				
				 echo "</div>";
				
			}
			break;
			
		}
	}
?>

