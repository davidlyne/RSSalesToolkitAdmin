

<?php
	$catfilter=0;

		
	if (array_key_exists("FILTERCATEGORY",$_GET))
	{
		$catfilter = $_GET["FILTERCATEGORY"];
		$_SESSION["cpcatfilter1"] = $catfilter;
	}else
	{
		if (array_key_exists("cpcatfilter1",$_SESSION))
			$catfilter = $_SESSION["cpcatfilter1"];
	}
?>	

<div class="wrapper">
        <h1>Comms Packs</h1>
		<?php
		echo "<a href='".$productHighlightsTop."'><button class='add'>Back</button></a> ";
		echo "<a href='".$productHighlightsAddCommsPack."&FILTERCATEGORY=".$catfilter."'><button class='add'>Add Comms Pack</button></a> ";
		?>
		
		<p><label name="category">Category</label>
		
		<select name="commspackcat" id="commspackcat" onchange="updateCat(this);">
		<?php
		

		
		
		$result = mysql_query("SELECT * FROM producthighlightscategory WHERE Parent=0");
		
		if ($catfilter > 0)
			echo "<option value='0'>ALL</option>";
		else
			echo "<option value='0' selected >ALL</option>";		
			
		while($row = mysql_fetch_array($result))
		{
			echo "<option value='".$row["ID"]."'";
			if ($catfilter == $row["ID"])
				echo " selected>";
			else
				echo ">";				
			
			echo $row["Name"];
			echo "</option>";
		}
		?>
		</select>
		
		<script type="text/javascript">

		function updateCat(selectObj)
		{
			var selectIndex=selectObj.selectedIndex;
			var selectValue=selectObj.options[selectIndex].value;
			window.location.href = "<?php echo $productHighlightsCommsPacks; ?>" + "&FILTERCATEGORY=" + selectValue;
			
		};



		$("#commspackcat").change(updateCat);


		</script>
		<p>
        <table>
            <thead>
                <th width="40%">Name</th>
				<th width="30%">Category</th>
				<th width="10%">Date Created</th>
				<th width="10%">PDF</th>
				<th width="5%">Edit</th>
				<th width="5%">Delete</th>
            </thead>
			 <?php
				if ($catfilter > 0)
					$result = mysql_query("SELECT * FROM producthighlightscommspack WHERE Category='$catfilter' ORDER BY Name ");
				else
					$result = mysql_query("SELECT * FROM producthighlightscommspack ORDER BY Category");
			
				$odd = 1;
				 while($row = mysql_fetch_array($result))
				 {
				 	if ($odd)
						echo "<tr>";
					else
						echo "<tr bgcolor='#dad7d7'>";
							
					echo "<td>".$row['Name']."</td>";
					echo "<td>".getCategoryName($row['Category'])."</td>";
					echo "<td>".date('d/m/Y', $row['Timestamp'])."</td>";
					echo "<td><a href='".$row['PDF']."' target='_new'><button>View</button></a></td>";
					echo "<td><a href='".$productHighlightsEditCommsPack."&EDITCOMMSPACK=".$row['ID']."&ID=".$row['ID']."'><button>Edit</button></a></td>";
					echo "<td><a href='".$productHighlightsDeleteCommsPack."&DELETECOMMSPACK=".$row['ID']."'><button class=delete>Delete</button></a></td>";
					echo "</tr>";
					
					$odd = !$odd;

				 }
			?>
			
		</form>

		
</div>