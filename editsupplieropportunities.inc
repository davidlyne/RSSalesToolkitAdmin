

<script src="http://jqueryjs.googlecode.com/files/jquery-1.3.2.min.js" type="text/javascript"></script>

<?php
	$editid = $_GET["ID"];	
?>
<script type="text/javascript">
function validateForm() {
    
	var missingFields = "";
	
	x = document.forms["form"]["pdf"].value;
	if (x == null || x == "") {
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
	
	echo "<h1>Edit Supplier Opportunities: <b>".$designTools[$editid]."</b></h1>";
			
	echo "<a href='".$supplieropportunities."'><button class='add'>Back</button></a><p>";

	?>
	<div id='validationError'>
	</div>
	
	<section class="product-details-input">
		<form name="form" method="post" action="index.php" onsubmit="return validateForm()" enctype="multipart/form-data">
		<div class="left-inputs">
			<ul>


		<li>
			<label for="pdf">Upload PDF</label>
			<input type="file" name="pdf" accept="application/pdf">
		</li>
		
		</ul>

		
		<input type="hidden" name="NAV" value="SOADMIN">
			<input type="hidden" name="SOTOOL" value="SUPPLIEROPPORTUNITIESLIST">
			<?php
				echo '<input type="hidden" name="EDITSUPPLIEROPPORTUNITIES" value="'.$editid.'">';
	
			?>
			
			<input type="hidden" name="MAX_FILE_SIZE" value="35000000000">
		</li>
		
		<?php
			echo "<button>Update</button>";
		
		?>
		
		</div>
		</form>
		
	</section>
</div>