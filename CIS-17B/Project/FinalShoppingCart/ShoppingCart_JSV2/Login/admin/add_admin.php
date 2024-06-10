<?php 
/* 
 * script:   add_admin.php
 * Author: Janaye Jackson
 *
 * Created on May 30th, 2024, 9:52 PM
 * Purpose: This page allows the administrator to add new admins
 */
    //access cookie session
    session_start();
    $page_title = 'Add an Admin';
    include ('includes/header.html');
    require ('../../Connect.php');
    echo '<h1>Add an Admin</h1>';
    //access cookie session
    session_start();
    // Check for a valid admin id
    if ( (!isset($_SESSION['admin_id']))) {//From scookie ession
	echo '<p class="error">You do not have permission to view this page.</p>';
        include ('includes/footer.html'); 
	exit();
    }
    if ($_SERVER['REQUEST_METHOD'] == 'POST') { // Handle the form.
        // Add admin to the database:
        // Validate the first and last names - not required:
        $fn = (!empty($_POST['first_name'])) ? trim($_POST['first_name']) : NULL;
        $ln = (!empty($_POST['last_name'])) ? trim($_POST['last_name']) : NULL;
        //required fields 
        $em = trim($_POST['email']);
        $us = mysqli_real_escape_string($conn, trim($_POST['user_name']));
        //Validate password confirmation
        if ($_POST['pass1'] != $_POST['pass2']) {
            echo 'Your password did not match the confirmed password.';
        } else {
            $p = mysqli_real_escape_string($conn, trim($_POST['pass1']));
            $q = "INSERT INTO admins (first_name, last_name, email, user_name, pass, add_date) "
                    . "VALUES ('$fn', '$ln', '$em','$us', SHA1('$p'), NOW())";
            $r = @mysqli_query ($conn, $q); // Run the query.
            if ($r) { // If it ran ok, print a message:
		echo '<h1>ADDED!</h1>
                <p>Admin has been added!</p><p><br /></p>';	
            } else { // If it did not run ok, display error:
		echo '<h1>System Error</h1>
		<p class="error">Admin could not be added due to a system error.</p>'; 
		// Debugging message:
		echo '<p>' . mysqli_error($conn) . '<br /><br />Query: ' . $q . '</p>';			
            } // End of if ($r) IF.
            mysqli_close($conn); // Close the database connection.

            // Include the footer and quit the script:
            include ('includes/footer.html'); 
        }    
}// End of the main Submit conditional.
// Display the form...
?>
<h1>Add an Admin</h1>
<form action="add_admin.php" method="post">
	
	<fieldset><legend>Fill out the form to add an admin:</legend>
	
	<p>First Name:<input type="text" name="first_name" size="10" maxlength="20" value="<?php if (isset($_POST['first_name'])) echo $_POST['first_name']; ?>" required/></p>
	<p>Last Name: <input type="text" name="last_name" size="10" maxlength="40" value="<?php if (isset($_POST['last_name'])) echo $_POST['last_name']; ?>" required/></p>
        <p>Email: <input type="email" name = "email" size ="20" maxlength = "60" value="<?php if (isset($_POST['email'])) echo $_POST['email']; ?>" required/></p>
        <p>Username: <input type="text" name="user_name" size="15" maxlength="40" value="<?php if (isset($_POST['user_name'])) echo $_POST['user_name']; ?>"  /> </p>
        <p>Password: <input type="password" name="pass1" size="10" maxlength="20" value="<?php if (isset($_POST['pass1'])) echo $_POST['pass1']; ?>"  required/></p>
	<p>Confirm Password: <input type="password" name="pass2" size="10" maxlength="20" value="<?php if (isset($_POST['pass2'])) echo $_POST['pass2']; ?>"  required/></p>
	</fieldset>	
	<div align="center"><input type="submit" name="submit" value="Submit" /></div>

</form>
<?php include ('includes/footer.html'); ?>