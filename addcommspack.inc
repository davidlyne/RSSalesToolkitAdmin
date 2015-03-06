

<script src="http://jqueryjs.googlecode.com/files/jquery-1.3.2.min.js" type="text/javascript"></script>

<?php
	if (array_key_exists("EDITCOMMSPACK",$_GET) == TRUE)
	{
		$editid = $_GET["EDITCOMMSPACK"];	
		$result = Database::Query("SELECT * FROM producthighlightscommspack WHERE ID=$editid");
		$row = Database::FetchArray($result);
		$commspackname = $row["Name"];
		$pdf = $row["PDF"];
		$cat = $row["Category"];
	}else
	{
		$catfilter=0;
		if (array_key_exists("FILTERCATEGORY",$_GET))
			$catfilter = $_GET["FILTERCATEGORY"];
		
		$editid = 0;
		$commspackname = "";
		$pdf = "";
		$cat = 0;
	}

?>

<script type="text/javascript">
function validateForm() {
    
	var missingFields = "";
	
	var x = document.forms["form"]["commspackcat"].value;
	if (x == null || x == "") {
        missingFields += "Comms Pack Category<br>";
    }
	
	x = document.forms["form"]["Name"].value;
    if (x == null || x == "") {
        missingFields += "Comms Pack Name<br>";
    }
	
	
	<?php
	
	if ($editid <= 0)
	{
		?>
		x = document.forms["form"]["pdf"].value;
		if (x == null || x == "") {
			missingFields += "PDF Document<br>";
		}
		<?php
	}
	?>
	
	if (document.forms["form"]["pdf"].value.length > 0)
	{
		if (!document.forms["form"]["pdf"].value.match(/\.(pdf)$/))
			missingFields += "PDF Document<br>";	
	}
	
	
	if (missingFields.length > 0)
	{
		$('html,body').scrollTop(0);
		document.getElementById('validationError').innerHTML = '<font color="red"><b>The following fields are missing or invalid:</b><p>' + missingFields + '</div>';
		return false;
	}
}
</script>

<div class="wrapper">

	<?php
		if ($editid > 0)
			echo "<h1>Edit Comms Pack</h1>";
		else
			echo "<h1>Add Comms Pack</h1>";	
			
	echo "<a href='".$productHighlightsCommsPacks."'><button class='add'>Back</button></a><p>";

	?>
	<div id='validationError'>
	</div>
	
	<section class="product-details-input">
		<form name="form" method="post" action="index.php" onsubmit="return validateForm()" enctype="multipart/form-data">
		<div class="left-inputs">
			<ul>

			<li>
			<label for="commspackcat">Comms Pack Category</label>
			<select name="commspackcat" id="commspackcat">
			<?php
			$result = Database::Query("SELECT * FROM producthighlightscategory WHERE Parent=0");
			while($row = Database::FetchArray($result))
			{
				echo "<option value='".$row["ID"]."'";
				if ($editid > 0 && $cat == $row["ID"])
					echo " selected>";
				else if ($catfilter > 0 && $catfilter == $row["ID"] )
					echo " selected>";		
				else
					echo ">";				
				
				echo $row["Name"];
				echo "</option>";
			}
			?>
			</select>
		</li>


		<li>
			<label for="Name">Comms Pack Name</label>
			<input name="Name" value="<?php echo $commspackname;?>">
		</li>
		<li>
			<label for="pdf">PDF</label>
			<input type="file" name="pdf" accept="application/pdf">
		</li>
		
		</ul>

		
		<input type="hidden" name="NAV" value="PHADMIN">
			<input type="hidden" name="PHTOOL" value="COMMSPACKLIST">
			<?php
				if ($editid != 0)
					echo '<input type="hidden" name="EDITCOMMSPACK" value="'.$editid.'">';
				else
					echo '<input type="hidden" name="ADDNEWCOMMSPACK" value="TRUE">';
			?>
			
			<input type="hidden" name="MAX_FILE_SIZE" value="35000000000">
		</li>
		
		<?php
			if ($editid > 0)
				echo "<button>Update</button>";
			else
				echo "<button>Publish</button>";			
		?>
		
		</div>
		</form>
		
	</section>
</div>