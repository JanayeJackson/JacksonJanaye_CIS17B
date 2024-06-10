<?php # Script - add_cart.php
// This page adds prints to the shopping cart.

// Set the page title and include the HTML header:
session_start();
$page_title = 'Add to Cart';
include ('includes/header.html');

if (isset ($_GET['id']) && filter_var($_GET['id'], FILTER_VALIDATE_INT, array('min_range' => 1))  ) { // Check for a print ID.
	$id = $_GET['id'];

	// Check if the cart already contains one of these items;
	// If so, increment the quantity:
	if (isset($_SESSION['cart'][$id])) {
		$_SESSION['cart'][$id]['quantity']++; // Add another.
		// Display a message:
		echo '<p>Another copy of this item has been added to your shopping cart.</p>';
	} else { // New product to the cart.
		// Get the item's price from the database:
		require('../../Connect.php'); // Connect to the database.
		$q = "SELECT price FROM catalog WHERE item_id=$id";
		$r = mysqli_query ($conn, $q);		
		if (mysqli_num_rows($r) == 1) { // Valid print ID.
			// Fetch the information.
			list($price) = mysqli_fetch_array ($r, MYSQLI_NUM);
			// Add to the cart:
			$_SESSION['cart'][$id] = array ('quantity' => 1, 'price' => $price);
			// Display a message:
			echo '<p>The item has been added to your shopping cart.</p>';
		} else { // Not a valid print ID.
			echo '<div align="center">This page has been accessed in error!</div>';
		}
		
		mysqli_close($conn);

	} // End of isset($_SESSION['cart'][$id] conditional.
} else { // No print ID.
	echo '<div align="center">This page has been accessed in error!</div>';
}

include ('includes/footer.html');
?>