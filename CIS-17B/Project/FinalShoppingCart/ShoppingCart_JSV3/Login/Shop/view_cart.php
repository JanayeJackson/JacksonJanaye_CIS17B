<?php # Script - view_cart.php
// This page displays the contents of the shopping cart.
// This page also lets the user update the contents of the cart.

// Set the page title and include the HTML header:
session_start();
$page_title = 'View Your Shopping Cart';
include ('includes/header.html');
if (isset($_SESSION['user_id'])) {
	$id = $_SESSION['user_id'];
} else { // No valid ID, kill the script.
	echo '<p class="error">This page has been accessed in error.</p>';
	include ('includes/footer.html'); 
	exit();
}

// Check if the form has been submitted (to update the cart):
if ($_SERVER['REQUEST_METHOD'] == 'POST') {

	// Change any quantities:
	foreach ($_POST['qty'] as $k => $v) {

		// Must be integers!
		$id = (int) $k;
		$qty = (int) $v;
		
		if ( $qty == 0 ) { // Delete.
			unset ($_SESSION['cart'][$id]);
		} elseif ( $qty > 0 ) { // Change quantity.
			$_SESSION['cart'][$id]['quantity'] = $qty;
		}
		
	} // End of FOREACH.
	
} // End of SUBMITTED IF.

// Display the cart if it's not empty...
if (!empty($_SESSION['cart'])) {

	// Retrieve all of the information for the items in the cart:
	require ('../../Connect.php'); // Connect to the database.
	$q = "SELECT item_id, image, name, enum_size.size, price, description FROM catalog, enum_size "
                . "WHERE `catalog`.`size` = `enum_size`.`size_id` AND item_id IN (";
	foreach ($_SESSION['cart'] as $id => $value) {
		$q .= $id . ',';
	}
	$q = substr($q, 0, -1) . ') ORDER BY catalog.name ASC';
	$r = mysqli_query ($conn, $q);
	// Create a form and a table:
	echo '<form action="view_cart.php" method="post">
	<table border="0" width="90%" cellspacing="3" cellpadding="3" align="center">
	<tr>
		<td align="left" width="30%"><b>Item</b></td>
		<td align="left" width="30%"><b>Name</b></td>
                <td align="left" width="30%"><b>Size</b></td>
                <td align="center" width="10%"><b>Qty</b></td>
		<td align="right" width="10%"><b>Price</b></td>
		<td align="right" width="10%"><b>Total Price</b></td>
	</tr>
	';

	// Print each item...
	$total = 0; // Total cost of the order.
	while ($row = mysqli_fetch_array ($r, MYSQLI_ASSOC)) {
	
		// Calculate the total and sub-totals.
		$subtotal = $_SESSION['cart'][$row['item_id']]['quantity'] * $_SESSION['cart'][$row['item_id']]['price'];
		$total += $subtotal;
		
		// Print the row:
		echo '<tr>
                <td id="image" align="left"><img src="pics/'.$row['image'].'" alt="" /></td>
		<td align="left">'.$row['name'].'</td>
                <td align="left">'.$row['size'].'</td>   
                <td align="center"><input type="text" size="3" name= qty"' . $row['item_id'] . '" value="'.$_SESSION['cart'][$row['item_id']]['quantity'].'" /></td>
		<td align="right">$'.$_SESSION['cart'][$row['item_id']]['price'].'</td>
		<td align="right">$' . number_format ($subtotal, 2) . '</td>
		</tr>';
	
	} // End of the WHILE loop.

	mysqli_close($conn); // Close the database connection.

	// Print the total, close the table, and the form:
	echo '<tr>
		<td colspan="4" align="right"><b>Total:</b></td>
		<td align="right">$' . number_format ($total, 2) . '</td>
	</tr>
	</table>
	<div align="center"><input type="submit" name="submit" value="Update My Cart" /></div>
	</form><p align="center">Enter a quantity of 0 to remove an item.
	<br /><br /><a href="checkout.php?total=' . $total .'">Checkout</a></p>';

} else {
	echo '<p>Your cart is currently empty.</p>';
}

include ('includes/footer.html');
?>