<?php # Script 9.5 - register.php #2
// This script performs an INSERT query to add a record to the users table.

//access cookie session
session_start();
$page_title = 'Register';
include ('includes/header.html');

// Check for form submission:
if ($_SERVER['REQUEST_METHOD'] == 'POST') {

	require ('../Connect.php'); // Connect to the db.
	$errors = array(); // Initialize an error array.
	//initialize form variables
        $fn = mysqli_real_escape_string($conn, trim($_POST['first_name']));
	$ln = mysqli_real_escape_string($conn, trim($_POST['last_name']));
	$em = mysqli_real_escape_string($conn, trim($_POST['email']));
        $us = mysqli_real_escape_string($conn, trim($_POST['user_name']));
	// Validate password and confirmed password
        if ($_POST['pass1'] != $_POST['pass2']) {
			echo '<p>Your password did not match the confirmed password.</p>';
	} else {
            $p = mysqli_real_escape_string($conn, trim($_POST['pass1']));
	}
	
	// Register the user in the database...
	// Make the query:
	$q = "INSERT INTO users (first_name, last_name, email, user_name, pass, registration_date) "
                . "VALUES ('$fn', '$ln', '$em', '$us', SHA1('$p'), NOW())";		
	$r = @mysqli_query ($conn, $q); // Run the query.
	if ($r) { // If it ran ok, print a message:
            echo '<h1>Thank you!</h1>
		<p>You are now registered</p><p><br /></p>';	
		} else { // If it did not run ok display error message:
			echo '<h1>System Error</h1>
			<p class="error">You could not be registered due to a system error</p>'; 
			// Debugging message:
			echo '<p>' . mysqli_error($conn) . '<br /><br />Query: ' . $q . '</p>';			
		} // End of if ($r) IF.
		
		mysqli_close($conn); // Close the database connection.

		// Include the footer and quit the script:
		include ('includes/footer.html'); 
		exit();

} // End of the main Submit conditional.
?>
<h1>Register</h1>
<form action="register.php" method="post">
	<p>First Name: <input type="text" name="first_name" size="15" maxlength="20" value="<?php if (isset($_POST['first_name'])) echo $_POST['first_name']; ?>" required/></p>
	<p>Last Name: <input type="text" name="last_name" size="15" maxlength="40" value="<?php if (isset($_POST['last_name'])) echo $_POST['last_name']; ?>" required/></p>
	<p>Email Address: <input type="text" name="email" size="20" maxlength="60" value="<?php if (isset($_POST['email'])) echo $_POST['email']; ?>"  required/> </p>
        <p>Username: <input type="text" name="user_name" size="15" maxlength="40" value="<?php if (isset($_POST['user_name'])) echo $_POST['user_name']; ?>"  required/> </p>
	<p>Password: <input type="password" name="pass1" size="10" maxlength="20" value="<?php if (isset($_POST['pass1'])) echo $_POST['pass1']; ?>"  required/></p>
	<p>Confirm Password: <input type="password" name="pass2" size="10" maxlength="20" value="<?php if (isset($_POST['pass2'])) echo $_POST['pass2']; ?>"  required/></p>
	<p><input type="submit" name="submit" value="Register" /></p>
</form>
<?php include ('includes/footer.html'); ?>