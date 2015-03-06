
	<div class="wrapper">
	<table><tr><td width="33%"></td><td width="33%">
	<FORM METHOD="POST" ACTION="<?php echo $productHighlightsTop; ?>">
		<h1>Sign in</h1>
		<?php
		if ($loginFailure)
			echo '<font color="red"><b>Invalid Username/Password</b></font><p>';
		?>
		<ul>
		<li>
		<label>Username</label>
		<input name="username">
	</li>
	<li>
		<label>Password</label>
		<input name="password" type="password">
	</li>
	<input type="hidden" name="LOGIN" value="LOGIN">
	<button>Sign in</button>
	</form>
	</td>
	<td width="33%"></td>
	</tr></table>