<?php
/* 
 * File:   connect.php
 * Author: Janaye Jackson
 *
 * Created on May 28th, 2024, 6:58 PM
 * Purpose: Connect to shoppingcart database
 */
	
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "shoppingcart";

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
?>

