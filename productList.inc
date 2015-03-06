<script src="http://jqueryjs.googlecode.com/files/jquery-1.3.2.min.js" type="text/javascript"></script>

<?php
	$catfilter1=0;

	if (array_key_exists("FILTERCATEGORY1",$_GET))
	{
		$catfilter1 = $_GET["FILTERCATEGORY1"];
		$_SESSION["catfilter1"] = $catfilter1;
	}else
	{
		if (array_key_exists("catfilter1",$_SESSION))
			$catfilter1 = $_SESSION["catfilter1"];
	}
		
	$catfilter2=0;

	if (array_key_exists("FILTERCATEGORY2",$_GET))
	{
		$catfilter2 = $_GET["FILTERCATEGORY2"];
		$_SESSION["catfilter2"] = $catfilter2;
	}else
	{
		if (array_key_exists("catfilter2",$_SESSION))
			$catfilter2 = $_SESSION["catfilter2"];
	}
	
	if ($catfilter1 == 0)
		$catfilter2=0;
?>	

<script type="text/javascript">

function updateCat1(selectObj)
{
	var selectIndex=selectObj.selectedIndex;
	var selectValue=selectObj.options[selectIndex].value;
	window.location.href = "<?php echo $productHighlightsProducts; ?>" + "&FILTERCATEGORY1=" + selectValue + "&FILTERCATEGORY2=0";
	
};

function updateCat2(selectObj)
{
	var selectIndex=selectObj.selectedIndex;
	var selectValue=selectObj.options[selectIndex].value;
	window.location.href = "<?php echo $productHighlightsProducts; ?>" + "&FILTERCATEGORY1=<?php echo $catfilter1; ?>" + "&FILTERCATEGORY2=" + selectValue;
	
};


</script>
		
<div class="wrapper">
        <h1>Products</h1>
		<?php
		echo "<a href='".$productHighlightsTop."'><button class='add'>Back</button></a> ";
		echo "<a href='".$productHighlightsAddProduct."&FILTERCATEGORY1=".$catfilter1."&FILTERCATEGORY2=".$catfilter2."'><button class='add'>Add Product</button></a>";
		
		?>
		<p>
		
		<label for="productcat">Category</label>

		<select name="productcat" id="productcat" onchange="updateCat1(this);">
			
		<?php
		
		if ($catfilter1 > 0)
			echo "<option value='0'>ALL</option>";
		else
			echo "<option value='0' selected >ALL</option>";	
			
		$result = Database::Query("SELECT * FROM producthighlightscategory WHERE Parent=0");
		while($row = Database::FetchArray($result))
		{
			echo "<option value='".$row["ID"]."'";
			if ($catfilter1 == $row["ID"])
				echo " selected>";
			else
				echo ">";				
			
			echo $row["Name"];
			echo "</option>";
		}
		?>
		</select>
		
		<?php
		if ($catfilter1 == 0)
		{

		}else
		{
		?>
			 / 
			 
			 <select name="subcat" id="subcat" onchange="updateCat2(this);">
				
			<?php
			
			
			if ($catfilter2 > 0)
				echo "<option value='0'>ALL</option>";
			else
				echo "<option value='0' selected >ALL</option>";	
				
			$result = Database::Query("SELECT * FROM producthighlightscategory WHERE Parent='$catfilter1'");
			while($row = Database::FetchArray($result))
			{
				echo "<option value='".$row["ID"]."'";
				if ($catfilter2 == $row["ID"])
					echo " selected>";
				else
					echo ">";				
				
				echo $row["Name"];
				echo "</option>";
			}
			?>
			</select>
		<?php
		}
		?>
		
        <table>
            <thead>
                <th width="7%">Stock No.</th>
                <th width="7%">Brand</th>
                <th width="37%">Category</th>
                <th width="37%">Name</th>
				<th width="5%">Edit</th>
				<th width="5%">Delete</th>
            </thead>
			 <?php
				if ($catfilter1 <= 0 && $catfilter2 <= 0)
					$result = Database::Query("SELECT * FROM producthighlightsproduct ORDER BY Category ");
				else if ($catfilter1 > 0 && $catfilter2 <= 0)
					$result = Database::Query("SELECT * FROM producthighlightsproduct WHERE Category='$catfilter1' ORDER BY Category2 ");
				else
					$result = Database::Query("SELECT * FROM producthighlightsproduct WHERE Category='$catfilter1' AND Category2='$catfilter2' ORDER BY Name ");
				$odd = 0;
				 while($row = Database::FetchArray($result))
				 {
				 	if ($odd)
						echo "<tr>";
					else
						echo "<tr bgcolor='#dad7d7'>";
						
					echo "<td>".$row['StockNo'],"</td>";
					echo "<td>".$row['Brand'],"</td>";
					echo "<td>".getProductCategoryPath($row['ID'])."</td>";
					echo "<td>".$row['Name'],"</td>";
					echo "<td><a href='".$productHighlightsEditProduct."&EDITPRODUCT=".$row['ID']."&ID=".$row['ID']."'><button>Edit</button></a></td>";
					echo "<td><a href='".$productHighlightsDeleteProduct."&DELETEPRODUCT=".$row['ID']."'><button class=delete>Delete</button></a></td>";
					echo "</tr>";
					
					$odd = !$odd;
				 }
			?>
			
		</form>

		
</div>