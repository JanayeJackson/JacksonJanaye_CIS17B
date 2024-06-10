<?php # Script 9.7 - password.php
// This page lets a user change their password.

//access cookie session
session_start();
$page_title = 'Change Your Password';
include ('includes/header.html');

// Check for form submission:
if ($_SERVER['REQUEST_METHOD'] == 'POST') {

	require ('../Connect.php'); // Connect to the db.
	$user = mysqli_real_escape_string($conn, trim($_POST['user_name']));
        // Check for the current password:
	$p = mysqli_real_escape_string($conn, trim($_POST['pass']));

	// Check for a new password and match 
	// against the confirmed password:
	if ($_POST['pass1'] != $_POST['pass2']) { 
            echo'<p>Your new password did not match the confirmed password.</p>';
	} else {
            $np = mysqli_real_escape_string($conn, trim($_POST['pass1']));
	}
	
        // Check that they've entered the right email address/password combination:
	$q = "SELECT user_id FROM users WHERE (user_name='$user' AND pass=SHA1('$p') )";
	$r = @mysqli_query($conn, $q);
	$num = @mysqli_num_rows($r);
	if ($num == 1) { // Match was made.	
            // Get the user_id:
            $row = mysqli_fetch_array($r, MYSQLI_NUM);
            // Make the UPDATE query:
            $q = "UPDATE users SET pass=SHA1('$np') WHERE user_id=$row[0]";		
            $r = @mysqli_query($conn, $q);
            if (mysqli_affected_rows($conn) == 1) { // If it ran ok, print a message.
		echo '<h1>Thank you!</h1>
		<p>Your password has been updated.</p><p><br /></p>';	
            } else { // If it did not run ok, display error message:
		echo '<h1>System Error</h1>
		<p class="error">Your password could not be changed due to a system error.</p>'; 
                // Debugging message:
		echo '<p>' . mysqli_error($conn) . '<br /><br />Query: ' . $q . '</p>';
            }

            mysqli_close($conn); // Close the database connection.

            // Include the footer and quit the script (to not show the form).
            include ('includes/footer.html'); 
            exit();			
	} else { // Invalid email address/password combination.
            echo '<h1>Error!</h1>
            <p class="error">The username and password do not match those on file.</p>';
	}	
} // End of the main Submit conditional.
?>
<h1>Change Your Password</h1>
<form action="password.php" method="post">
	<p>Username: <input type="text" name="user_name" size="20" maxlength="40" value="<?php if (isset($_POST['user_name'])) echo $_POST['user_name']; ?>"  reuired/> </p>
	<p>Current Password: <input type="password" name="pass" size="10" maxlength="20" value="<?php if (isset($_POST['pass'])) echo $_POST['pass']; ?>"  required/></p>
	<p>New Password: <input type="password" name="pass1" size="10" maxlength="20" value="<?php if (isset($_POST['pass1'])) echo $_POST['pass1']; ?>"  required/></p>
	<p>Confirm New Password: <input type="password" name="pass2" size="10" maxlength="20" value="<?php if (isset($_POST['pass2'])) echo $_POST['pass2']; ?>"  required/></p>
	<p><input type="submit" name="submit" value="Change Password" /></p>
</form>
<?php include ('includes/footer.html'); ?>