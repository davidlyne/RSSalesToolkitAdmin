

<div class="wrapper">
        <h1>Supplier Opportunities</h1>
		<?php

		echo "<a href='".$productHighlightsTop."'><button class='add'>Back</button></a> ";
		?>
			

		<p>
        <table>
            <thead>
                <th width="30%">Design Tool</th>
				<th width="30%">PDF</th>
				<th width="5%">Edit</th>
            </thead>
			 <?php
		
				$odd = 1;
				 for ($i=0;$i<count($designTools);$i++)
				 {
				 	if ($odd)
						echo "<tr>";
					else
						echo "<tr bgcolor='#dad7d7'>";
					
					
					echo "<td WIDTH='90%'>".$designTools[$i]."</td>";
					if (doesSupplierOpportunitiesExist($i))
					{
						$pdf = getSupplierOpportunitiesPDF($i);
						echo "<td><a href='".$pdf."' target='_new'><button>View</button></a></td>";
					}else
						echo "<td></td>";
						
					echo "<td><a href='".$supplieropportunitiesEdit."&ID=".$i."'><button>Edit</button></a></td>";
					echo "</tr>";
					
					$odd = !$odd;

				 }
			?>
			
		</form>

		
</div>