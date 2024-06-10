<?php # Script - checkout.php
// This page inserts the order information into the table.
// This page would come after the billing process.
// This page assumes that the billing process worked (the money has been taken).

// Set the page title and include the HTML header:
session_start();
$page_title = 'Order Confirmation';
include ('includes/header.html');
if (isset($_SESSION['user_id']) && isset($_GET['total'])) {
	$cid = $_SESSION['user_id'];
        $total = $_GET['total'];
    } else { // No valid ID, kill the script.
	echo '<p class="error">This page has been accessed in error.</p>';
	include ('includes/footer.html'); 
	exit();
 }


require ('../../Connect.php'); // Connect to the database.
// Turn autocommit off:
mysqli_autocommit($conn, FALSE);
// Add the order to the orders table...
$q = "INSERT INTO orders (customer_id, total) VALUES ($cid, $total)";
$r = mysqli_query($conn, $q);
if (mysqli_affected_rows($conn) == 1) {
	// Need the order ID:
	$oid = mysqli_insert_id($conn);
	// Insert the specific order contents into the database...
	// Prepare the query:
	$q = "INSERT INTO order_contents (order_id, item_id, quantity, price) VALUES (?, ?, ?, ?)";
	$stmt = mysqli_prepare($conn, $q);
	mysqli_stmt_bind_param($stmt, 'iiid', $oid, $id, $qty, $price);
	// Execute each query; count the total affected:
	$affected = 0;
	foreach ($_SESSION['cart'] as $id => $item) {
		$qty = $item['quantity'];
		$price = $item['price'];
		mysqli_stmt_execute($stmt);
		$affected += mysqli_stmt_affected_rows($stmt);
	}

	// Close this prepared statement:
	mysqli_stmt_close($stmt);
	// Report on the success....
	if ($affected == count($_SESSION['cart'])) { // Whohoo!
		// Commit the transaction:
		mysqli_commit($conn);
		// Clear the cart:
		unset($_SESSION['cart']);
		// Message to the customer:
		echo '<p>Thank you for your order. You will be notified when the items ship.</p>';
		// Send emails and do whatever else.
	} else { // Rollback and report the problem.
		mysqli_rollback($conn);
		echo '<p>Your order could not be processed due to a system error. You will be contacted in order to have the problem fixed. We apologize for the inconvenience.</p>';
		// Send the order information to the administrator.
		
	}
} else { // Rollback and report the problem.
	mysqli_rollback($conn);
	echo '<p>Your order could not be processed due to a system error. You will be contacted in order to have the problem fixed. We apologize for the inconvenience.</p>';
	// Send the order information to the administrator.
	
}

mysqli_close($conn);

include ('includes/footer.html');
?>