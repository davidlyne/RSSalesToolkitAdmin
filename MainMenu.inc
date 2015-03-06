
<div class="wrapper">

<h1>Product Highlights Administration</h1>

<?php

if ($permissionLevel > 1)
{
?>
	<a href="<?php echo $productHighlightsCategories; ?>"><button class="add">Product Categories</button></a> 
<?php
}
?>
<a href="<?php echo $productHighlightsProducts; ?>"><button class="add">Products</button></a> 
<a href="<?php echo $productHighlightsCommsPacks; ?>"><button class="add">Comms Packs</button></a> 

<br><br>
<h1>Supplier Opportunities Administration</h1>
<a href="<?php echo $supplieropportunities; ?>"><button class="add">Supplier Opportunities</button></a> 


</div>
