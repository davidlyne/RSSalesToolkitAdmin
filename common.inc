<?php
        require 'Config.php';
        require 'UserDB.php';
        require 'Database.php';
        
	
	$adminPage = basename($_SERVER['PHP_SELF']);
	$productHighlightsTop = $adminPage."?NAV=PHADMIN";
	$productHighlightsLogout = $adminPage."?NAV=LOGOUT";
	$productHighlightsCategories = $adminPage."?NAV=PHADMIN&PHTOOL=CATEGORIES";
	$productHighlightsEditCategory = $adminPage."?NAV=PHADMIN&PHTOOL=EDITCATEGORY";
	$productHighlightsDeleteCategory = $adminPage."?NAV=PHADMIN&PHTOOL=DELETECATEGORY";
	$productHighlightsProducts = $adminPage."?NAV=PHADMIN&PHTOOL=PRODUCTLIST";
	$productHighlightsAddProduct = $adminPage."?NAV=PHADMIN&PHTOOL=ADDPRODUCT";
	$productHighlightsDeleteProduct = $adminPage."?NAV=PHADMIN&PHTOOL=DELETEPRODUCT";
	$productHighlightsEditProduct = $adminPage."?NAV=PHADMIN&PHTOOL=EDITPRODUCT";
	$productHighlightsCommsPacks = $adminPage."?NAV=PHADMIN&PHTOOL=COMMSPACKLIST";
	$productHighlightsAddCommsPack = $adminPage."?NAV=PHADMIN&PHTOOL=ADDCOMMSPACK";
	$productHighlightsEditCommsPack = $adminPage."?NAV=PHADMIN&PHTOOL=EDITCOMMSPACK";
	$productHighlightsAddCommsPack = $adminPage."?NAV=PHADMIN&PHTOOL=ADDCOMMSPACK";
	$productHighlightsDeleteCommsPack = $adminPage."?NAV=PHADMIN&PHTOOL=DELETECOMMSPACK";
	$supplieropportunities = $adminPage."?NAV=SOADMIN&SOTOOL=SUPPLIEROPPORTUNITIESLIST";
	$supplieropportunitiesEdit = $adminPage."?NAV=SOADMIN&SOTOOL=SUPPLIEROPPORTUNITIESEDIT";
	
	
	$designTools = array(
    0 => "DS PCB",
    1 => "DS Mechanical",
	2 => "DS ModelSource",
	3 => "DesignSpark",
	4 => "RS ToolBox",
	5 => "DS DesignShare",
	);


        Database::connect();
	
	$phtool = "";
	if (array_key_exists("PHTOOL",$_GET))
		$phtool = $_GET["PHTOOL"];
	if (array_key_exists("PHTOOL",$_POST))
		$phtool = $_POST["PHTOOL"];
	
	$sotool = "";
	if (array_key_exists("SOTOOL",$_GET))
		$sotool = $_GET["SOTOOL"];
	if (array_key_exists("SOTOOL",$_POST))
		$sotool = $_POST["SOTOOL"];
		
	$nav = "";
	if (array_key_exists("NAV",$_GET))
		$nav = $_GET["NAV"];
	if (array_key_exists("NAV",$_POST))
		$nav = $_POST["NAV"];
	
	if (array_key_exists("NAV",$_GET))
	{
		if ($_GET["NAV"] == "LOGOUT")
		{
			session_start();
			session_unset();
			session_destroy(); 
			$nav="";
		}
	}
	
	$permissionLevel = 0;
	$loginFailure = 0;
	
	if (array_key_exists("LOGIN",$_POST) == TRUE)
	{
		
                $permissionLevel = UserDB::getPermissionLevel();
                
		if ($permissionLevel <= 0)
		{
			$loginFailure = 1;
			$nav = "";
		}
		session_start();
		if ($permissionLevel > 0)
		{
			$_SESSION["permissionLevel"] = $permissionLevel;
		}
		
	}else
	{
	
		session_start();
		if (array_key_exists("permissionLevel",$_SESSION) == FALSE)
		{
			$nav = "";
		}else
			$permissionLevel = $_SESSION["permissionLevel"];
		
	}
			
	function getNumSubCategories($catid)
	{  
		$result=Database::Query("SELECT COUNT(*) FROM producthighlightscategory WHERE Parent='$catid'");
		$row = Database::FetchRow($result);
		return $row[0];
	}
	
	function getNumProducts()
	{
            	$result=Database::Query("SELECT COUNT(*) FROM producthighlightsproduct");
		$row = Database::FetchRow($result);
		return $row[0];
	}
	
	function getNumCommsPacks()
	{
                $result=Database::Query("SELECT COUNT(*) FROM producthighlightscommspack");
		$row = Database::FetchRow($result);
		return $row[0];
	}
	
	function getBoolYesNo($valin)
	{
	
		switch ($valin)
		{
			case 0:
				return "NO";
			case 1:
				return "YES";				
		}
		
		return "YES";
	}
	function getCategoryName($catid)
	{
		$result=Database::Query("SELECT * from producthighlightscategory WHERE ID='$catid'");
		$data=Database::FetchArray($result);
		return strtoupper($data['Name']);
	}
	
	function getProductCategoryPath($productid)
	{
		$result = Database::Query("SELECT * FROM producthighlightsproduct WHERE ID=".$productid);
		$row = Database::FetchArray($result);
		$cat1 = $row['Category'];
		$cat2 = $row['Category2'];
		
		return getCategoryName($cat1)."/".getCategoryName($cat2);
	}
	
	function getCommsPackCategoryPath($commspackid)
	{
		$result = Database::Query("SELECT * FROM producthighlightscommspack WHERE ID=".$commspackid);
		$row = Database::FetchArray($result);
		$cat1 = $row['Category'];
		
		return getCategoryName($cat1);
	}
	
	
	function replace_extension($filename, $new_extension) {
		$info = pathinfo($filename);
		return  $info['dirname']."/".$info['filename'] . '.' . $new_extension;
	}
	
	class SimpleImage {

   var $image;
   var $image_type;

   function load($filename) {

      $image_info = getimagesize($filename);
      $this->image_type = $image_info[2];
      if( $this->image_type == IMAGETYPE_JPEG ) {

         $this->image = imagecreatefromjpeg($filename);
      } elseif( $this->image_type == IMAGETYPE_GIF ) {

         $this->image = imagecreatefromgif($filename);
      } elseif( $this->image_type == IMAGETYPE_PNG ) {

         $this->image = imagecreatefrompng($filename);
      }
   }


   function save($filename, $image_type=IMAGETYPE_JPEG, $compression=75, $permissions=null) {
	  $filenameout = $filename;

      if( $image_type == IMAGETYPE_JPEG ) {
		 $filenameout = replace_extension($filename,"jpg");
         imagejpeg($this->image,$filenameout,$compression);
      } elseif( $image_type == IMAGETYPE_GIF ) {	
	  echo "IMAGETYPE_GIF";
		 $filenameout = replace_extension($filename,"png");
         imagejpeg($this->image,$filenameout);
      } elseif( $image_type == IMAGETYPE_PNG ) {

         imagepng($this->image,$filename);
      }
      if( $permissions != null) {

         chmod($filename,$permissions);
      }
	  return $filenameout;
   }
   function output($image_type=IMAGETYPE_JPEG) {

      if( $image_type == IMAGETYPE_JPEG ) {
         imagejpeg($this->image);
      } elseif( $image_type == IMAGETYPE_GIF ) {

         imagegif($this->image);
      } elseif( $image_type == IMAGETYPE_PNG ) {

         imagepng($this->image);
      }
   }
   function getWidth() {

      return imagesx($this->image);
   }
   function getHeight() {

      return imagesy($this->image);
   }
   function resizeToHeight($height) {

      $ratio = $height / $this->getHeight();
      $width = $this->getWidth() * $ratio;
      $this->resize($width,$height);
   }

   function resizeToWidth($width) {
      $ratio = $width / $this->getWidth();
      $height = $this->getheight() * $ratio;
      $this->resize($width,$height);
   }

   function scale($scale) {
      $width = $this->getWidth() * $scale/100;
      $height = $this->getheight() * $scale/100;
      $this->resize($width,$height);
   }

   function resize($width,$height) {
      $new_image = imagecreatetruecolor($width, $height);
      imagecopyresampled($new_image, $this->image, 0, 0, 0, 0, $width, $height, $this->getWidth(), $this->getHeight());
      $this->image = $new_image;
   }      

}

	function resizeImage($filename)
	{
		$maxSize=512;
		$size = getimagesize($filename);
		if ($size[0] > $maxSize || $size[1] > $maxSize)
		{
			$newwidth = 0;
			$newheight = 0;
			
			if ($size[0] > $size[1])
			{
				$newwidth = $maxSize;
				$newheight = $maxSize/($size[0]/$size[1]);
			}else
			{
				$newheight = $maxSize;
				$newwidth = $maxSize/($size[1]/$size[0]);
			}
			
			$simg = new SimpleImage();
			$simg = new SimpleImage();
			$simg->load($filename);
			$simg->resize($newwidth,$newheight);
			return $simg->save($filename);
			//$simg->destroy();
			
		}else
		{
			$newwidth = $size[0];
			$newheight = $size[1];
			$simg = new SimpleImage();
			$simg = new SimpleImage();
			$simg->load($filename);
			$simg->resize($newwidth,$newheight);
			return $simg->save($filename);
		}
		
	
	}


 
	function getDisplayImageWidth($filename, $maxsize)
	{
		$size = getimagesize($filename);
		$w = $maxsize;
		$h = $maxsize;
		if ($size[0] > $size[1])
		{
			$w = $maxsize;
			$h = $w/($size[0]/$size[1]);
		}else
		{
			$h = $maxsize;
			$w = $h/($size[1]/$size[0]);
		}
		return $w;
	}
	
	function getDisplayImageHeight($filename, $maxsize)
	{
		$size = getimagesize($filename);
		$w = $maxsize;
		$h = $maxsize;
		if ($size[0] > $size[1])
		{
			$w = $maxsize;
			$h = $w/($size[0]/$size[1]);
		}else
		{
			$h = $maxsize;
			$w = $h/($size[1]/$size[0]);
		}
		return $h;
	}
	function updateProduct($editid)
	{
		
		addProduct($editid);
	}
	
	function updateCommsPack($editid)
	{
		
		addCommsPack($editid);
	}
	function addProduct($editid=0)
	{
	
		$cat1 = "";	
		if (array_key_exists("productcat",$_POST) == TRUE)
			$cat1 = $_POST["productcat"];
		
		$cat2 = "";	
		if (array_key_exists("subcat",$_POST)  == TRUE)
			$cat2 = $_POST["subcat"];
		
		$name = "";	
		if (array_key_exists("Name",$_POST)  == TRUE)
		{
			$name = addslashes($_POST["Name"]);
		}
		$stockNo = "";
		if (array_key_exists("StockNo",$_POST)  == TRUE)
			$stockNo = addslashes($_POST["StockNo"]);
		
		$brand = "";
		if (array_key_exists("Brand",$_POST)  == TRUE)
			$brand = addslashes($_POST["Brand"]);
		
		$url = "";
		if (array_key_exists("URL",$_POST)  == TRUE)
			$url = addslashes($_POST["URL"]);
		
		$mainImageFilename = "";
		if (array_key_exists("main-image",$_FILES)  == TRUE)
			$mainImageFilename = $_FILES['main-image']['name'];	

		$secondImageFilename = "";
		if (array_key_exists("second-image",$_FILES)  == TRUE)
			$secondImageFilename = $_FILES['second-image']['name'];	
		
		$thirdImageFilename = "";
		if (array_key_exists("third-image",$_FILES)  == TRUE)
			$thirdImageFilename = $_FILES['third-image']['name'];	
			
		$shortDesc = "";
		if (array_key_exists("ShortDesc",$_POST)  == TRUE)
			$shortDesc = addslashes($_POST["ShortDesc"]);
			
		$longDesc = "";
		if (array_key_exists("LongDesc",$_POST)  == TRUE)
			$longDesc = addslashes($_POST["LongDesc"]);
			
			
		$published = 1;
		$t = time();
		
		if ($editid > 0)
		{
			$sql = 	"UPDATE producthighlightsproduct SET Category = '$cat1', Category2 = '$cat2', Name = '$name', Brand = '$brand', StockNo = '$stockNo', Published = '$published', ShortDesc = '$shortDesc', LongDesc = '$longDesc', URL = '$url', Updated = '$t' WHERE ID = '$editid'";
		}
		else
		{
			$sql = 	"INSERT INTO producthighlightsproduct (	Category, Category2, Name, Brand, StockNo, Published, ShortDesc, LongDesc, URL, Timestamp, Updated  ) VALUES('$cat1','$cat2','$name','$brand','$stockNo','$published','$shortDesc','$longDesc','$url','$t','$t')";
		}
		
                
		Database::Query($sql); 
		
		if ($editid > 0)
			$id = $editid;
		else
			$id = Database::GetInsertID();
			
		if ($mainImageFilename != "")
		{
			$uid = $id."_1_";
			$target = "ProductImages/";
			$target = $target . $uid . basename( $mainImageFilename);	
			if(move_uploaded_file($_FILES['main-image']['tmp_name'], $target))
			{

				$target = resizeImage($target);
				Database::Query("UPDATE producthighlightsproduct SET Image1='$target' WHERE ID='$id'"); 

			}

		}
		
		if ($secondImageFilename != "")
		{
			$uid = $id."_2_";
			$target = "ProductImages/";
			$target = $target . $uid . basename( $secondImageFilename);	
			if(move_uploaded_file($_FILES['second-image']['tmp_name'], $target))
			{
				$target = resizeImage($target);
				Database::Query("UPDATE producthighlightsproduct SET Image2='$target' WHERE ID='$id'"); 

			}

		}
		
		if ($thirdImageFilename != "")
		{
			$uid = $id."_3_";
			$target = "ProductImages/";
			$target = $target . $uid . basename( $thirdImageFilename);	
			if(move_uploaded_file($_FILES['third-image']['tmp_name'], $target))
			{
				$target = resizeImage($target);
				Database::Query("UPDATE producthighlightsproduct SET Image3='$target' WHERE ID='$id'"); 

			}

		}
 
	}
	
	
	function addCommsPack($editid=0)
	{
	
		$cat1 = "";	
		if (array_key_exists("commspackcat",$_POST) == TRUE)
			$cat1 = $_POST["commspackcat"];
		
		$name = "";	
		if (array_key_exists("Name",$_POST)  == TRUE)
		{
			$name = addslashes($_POST["Name"]);
		}
		
		
		$pdfFilename = "";
		if (array_key_exists("pdf",$_FILES)  == TRUE)
			$pdfFilename = $_FILES['pdf']['name'];	

		
		$t = time();
		
		if ($editid > 0)
		{
			$sql = 	"UPDATE producthighlightscommspack SET Category = '$cat1', Name = '$name', Updated = '$t' WHERE ID = '$editid'";
		}
		else
		{
			
			$sql = 	"INSERT INTO producthighlightscommspack (	Category, Name, Timestamp, Updated ) VALUES('$cat1','$name','$t','$t')";
		}
		
		Database::Query($sql); 
		
		if ($editid > 0)
			$id = $editid;
		else
			$id = Database::GetInsertID ();
			
		if ($pdfFilename != "")
		{
			$uid = $id."_1_";
			$target = "CommsPacks/";
			$target = $target . $uid . basename( $pdfFilename);	
			if(move_uploaded_file($_FILES['pdf']['tmp_name'], $target))
			{

				Database::Query("UPDATE producthighlightscommspack SET PDF='$target' WHERE ID='$id'"); 

			}

		}
		
	
 
	}
	
	function doesSupplierOpportunitiesExist($editid=0)
	{
            	$result=Database::Query("SELECT COUNT(*) FROM supplieropportunities WHERE ID='$editid'");
		$row = Database::FetchRow($result);
		return $row[0] > 0;
	}
	
	function getSupplierOpportunitiesPDF($id=0)
	{
		$result=Database::Query("SELECT * from supplieropportunities WHERE ID='$id'");
		$row = Database::FetchArray($result);
		return $row["PDF"];
	}
	
	function updateSupplierOpportunities($editid=0)
	{
		$insertid=0;
		if (doesSupplierOpportunitiesExist($editid) == FALSE)
		{
			$insertid=1;

		}
		
		$pdfFilename = $_FILES['pdf']['name'];	

	
		$uid = $editid."_1_";
		$target = "SupplierOpportunities/";
		$target = $target . $uid . basename( $pdfFilename);	
		$t = time();
		if(move_uploaded_file($_FILES['pdf']['tmp_name'], $target))
		{	

			if ($insertid > 0)
				Database::Query("INSERT INTO supplieropportunities ( ID, PDF,Timestamp, Updated ) VALUES('$editid','$target','$t','$t')"); 
			else
				Database::Query("UPDATE supplieropportunities SET PDF='$target', Updated = '$t'  WHERE ID='$editid'"); 

		}else
		{
			echo "Failed to move pdf";
		}

		
		
	
 
	}
	
	
?>