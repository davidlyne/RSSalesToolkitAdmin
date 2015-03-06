<?php
	include "common.inc";
?>
<!doctype html>
<html class="no-js" lang="">
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title></title>
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <!-- Place favicon.ico and apple-touch-icon(s) in the root directory -->

        <link rel="stylesheet" href="css/normalize.css">
        <link rel="stylesheet" href="css/main.css">
        <link href='http://fonts.googleapis.com/css?family=Lato:100,300,400,700,900,100italic,300italic,400italic,700italic,900italic' rel='stylesheet' type='text/css'>
    </head>
    <body >
        <header class="branding"><img src="img/RS_D00000_72dpi.png" width="100px"></header>
		<?php
			if (array_key_exists("permissionLevel",$_SESSION) == TRUE)
			{
				?>
					<div align="right"><a href="<?php echo $productHighlightsLogout; ?>">Log Out</a>&nbsp;&nbsp;</div> 
				<?php
			}
		?>
		<?php 
			if ($nav == "")
				include "Login.inc";
			else
			{		
				switch ($nav)
				{
					case "PHADMIN":
						include "phadmin.inc";
					break;
					case "SOADMIN":
						include "soadmin.inc";
					break;
					default:
						include "Login.inc";
					
				}
			}
		?>

 
    </body>
</html>