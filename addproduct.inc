

<script src="http://jqueryjs.googlecode.com/files/jquery-1.3.2.min.js" type="text/javascript"></script>

<?php
	if (array_key_exists("EDITPRODUCT",$_GET) == TRUE)
	{
		$editid = $_GET["EDITPRODUCT"];	
		$result = mysql_query("SELECT * FROM producthighlightsproduct WHERE ID=$editid");
		$row = mysql_fetch_array($result);
		$productname = $row["Name"];
		$productStockNo = $row["StockNo"];
		$productBrand = $row["Brand"];
		$productURL = $row["URL"];
		$productShortDesc = $row["ShortDesc"];
		$productLongDesc = $row["LongDesc"];
		$image1 = $row["Image1"];
		$image2 = $row["Image2"];
		$image3 = $row["Image3"];
		$cat1 = $row["Category"];
		$cat2 = $row["Category2"];
		$catfilter1=0;
		if (array_key_exists("FILTERCATEGORY1",$_GET))
			$catfilter1 = $_GET["FILTERCATEGORY1"];
		$cat2=0;	
		if (array_key_exists("FILTERCATEGORY2",$_GET))
			$cat2 = $_GET["FILTERCATEGORY2"];
	}else
	{
		$editid = 0;
		$productname = "";
		$productStockNo = "";
		$productBrand = "";
		$productURL = "http://";
		$productShortDesc = "";
		$productLongDesc = "";
		$image1 = "";
		$image2 = "";
		$image3 = "";
		$cat1 = 0;
		$catfilter1=0;
		if (array_key_exists("FILTERCATEGORY1",$_GET))
			$catfilter1 = $_GET["FILTERCATEGORY1"];
		$cat2=0;	
		if (array_key_exists("FILTERCATEGORY2",$_GET))
			$cat2 = $_GET["FILTERCATEGORY2"];
	}

?>

<script type="text/javascript">
function validateForm() {
    
	var missingFields = "";
	
	var x = document.forms["form"]["productcat"].value;
	if (x == null || x == "") {
        missingFields += "Product Category<br>";
    }
	x = document.forms["form"]["subcat"].value;
    if (x == null || x == "") {
        missingFields += "Sub-category 1<br>";
    }

	x = document.forms["form"]["Name"].value;
    if (x == null || x == "") {
        missingFields += "Product Name<br>";
    }
	x = document.forms["form"]["StockNo"].value;
    if (x == null || x == "") {
        missingFields += "Stock No<br>";
    }
	
	x = document.forms["form"]["Brand"].value;
    if (x == null || x == "") {
        missingFields += "Brand<br>";
    }
	
	x = document.forms["form"]["URL"].value;
    if (x == null || x == "" || x == "http://") {
        missingFields += "URL<br>";
    }
	<?php
	
	if ($editid <= 0)
	{
		?>
		x = document.forms["form"]["main-image"].value;
		if (x == null || x == "") {
			missingFields += "Main Image<br>";
		}
		<?php
	}
	?>
	
	if (document.forms["form"]["main-image"].value.length > 0)
	{
		if (!document.forms["form"]["main-image"].value.match(/\.(jpg|jpeg|png|gif)$/))
			missingFields += "Main Image<br>";	
	}
	
	
	x = document.forms["form"]["ShortDesc"].value;
    if (x == null || x == "") {
        missingFields += "Short Description<br>";
    }
	
	x = document.forms["form"]["LongDesc"].value;
    if (x == null || x == "") {
        missingFields += "Long Description<br>";
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
			echo "<h1>Edit Product</h1>";
		else
			echo "<h1>Add Product</h1>";	
			
	echo "<a href='".$productHighlightsProducts."'><button class='add'>Back</button></a><p>";

	?>
	<div id='validationError'>
	</div>
	
	<section class="product-details-input">
		<form name="form" method="post" action="index.php" onsubmit="return validateForm()" enctype="multipart/form-data">
		<div class="left-inputs">
			<ul>

			<li>
			<label for="productcat">Product Category</label>
			<select name="productcat" id="productcat">
			<?php
			$result = mysql_query("SELECT * FROM producthighlightscategory WHERE Parent=0");
			while($row = mysql_fetch_array($result))
			{
				echo "<option value='".$row["ID"]."'";
				if ($editid > 0 && $cat1 == $row["ID"])
					echo " selected>";
				else if ($catfilter1 == $row["ID"])
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
			<label name="subcat">Sub-category 1</label>
			<select name="subcat" id="subcat"></select>
			
			<script type="text/javascript">
			
			function updateCat1()
			{
				
				$.ajax({
					url : "GetSubCategories.php?selectid=<?php echo $cat2; ?>&id=" + $("#productcat").val(),                          
					type: 'GET',                   
					dataType:'json',                   
					success : function(data) {  
						if (data.success) {
							$('#subcat').html(data.options);
							document.getElementById("subcat").disabled = false;
						}else
						{
							$('#subcat').html(data.options);
							document.getElementById("subcat").disabled = true;
				
						}
					
					}
				});

				
			};
		

			
			$("#productcat").change(updateCat1);
			window.onload = function()
			{

				updateCat1();

				
			};

			</script>
		</li>	

		<li>
			<label for="Name">Product Name</label>
			<input name="Name" value="<?php echo $productname;?>">
		</li>
		<li>
			<label for="rs-part-number">Stock No.</label>
			<input name="StockNo" value="<?php echo $productStockNo;?>">
		</li>
		<li>
			<label for="brand">Brand</label>
			<input name="Brand" value="<?php echo $productBrand;?>">
		</li>
		</ul>
		</div>
		<div class="right-inputs">
			<ul>
				<li>
			<label for="url">URL</label>
			<input name="URL" value="<?php echo $productURL;?>">
		</li>
		<li>
			<label for="main-image">Main Image</label>
			<input type="file" name="main-image" accept="image/*">
		</li>
		<li>
			<label for="second-image">Second Image</label>
			<input type="file" name="second-image" accept="image/*">
		</li>
		<li>
			<label for="third-image">Third Image</label>
			<input type="file" name="third-image" accept="image/*" >
		</li>
		<?php
			//phpinfo();	
			if ($editid != 0 && $image1 != "")
			{
				?>
				<script type="text/javascript">
				function changeImage(a,w,h) {
					document.getElementById("img").src=a;
					document.getElementById("img").width=w;
					document.getElementById("img").height=h;
				}
				</script>
				
				<?php
				$maxsize = 512;
				$w = getDisplayImageWidth($image1, $maxsize);
				$h = getDisplayImageHeight($image1, $maxsize);
				echo "<li>";
				echo '<center><img id="img" src="'.$image1.'" width="'.$w.'px" height="'.$h.'px" ></center>';
				echo "</li>";
				
				if ($image2 != "")
				{
					?>
					<center>
					<form action="">
					<?php
					if ($image1 != "")
					{
						$w = getDisplayImageWidth($image1, $maxsize);
						$h = getDisplayImageHeight($image1, $maxsize);
						?>
						<input type="radio" name="imgswap" value="0" onclick="changeImage('<?php echo $image1;?>',<?php echo $w;?>,<?php echo $h;?>);" checked="checked" >Main
						<?php
					}
					if ($image2 != "")
					{
						$w = getDisplayImageWidth($image2, $maxsize);
						$h = getDisplayImageHeight($image2, $maxsize);
						?>
						<input type="radio" name="imgswap" value="1" onclick="changeImage('<?php echo $image2;?>',<?php echo $w;?>,<?php echo $h;?>);">Second
						<?php
					}
					if ($image3 != "")
					{
						$w = getDisplayImageWidth($image3, $maxsize);
						$h = getDisplayImageHeight($image3, $maxsize);
						?>
						<input type="radio" name="imgswap" value="1" onclick="changeImage('<?php echo $image3;?>',<?php echo $w;?>,<?php echo $h;?>);">Third
						<?php
					}
					?>
					</form>
					</center>
					<p>
					<?php
				}
			}
		?>
		<li>
			<label for="description">Short Product Description</label>
			<textarea name="ShortDesc" maxlength="256"><?php echo $productShortDesc;?></textarea>
		</li>

		<li>
			<label for="description">Long Product Description</label>
			<textarea name="LongDesc"><?php echo $productLongDesc;?></textarea>
			<input type="hidden" name="NAV" value="PHADMIN">
			<input type="hidden" name="PHTOOL" value="PRODUCTLIST">
			<?php
				if ($editid != 0)
					echo '<input type="hidden" name="EDITPRODUCT" value="'.$editid.'">';
				else
					echo '<input type="hidden" name="ADDNEWPRODUCT" value="TRUE">';
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