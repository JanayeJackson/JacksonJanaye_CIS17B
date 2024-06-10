<?php # Script 12.2 - login_functions.inc.php
// This page defines two functions used by the login/logout process.

/* This function determines an absolute URL and redirects the user there.
 * The function takes one argument: the page to be redirected to.
 * The argument defaults to index.php.
 */
function redirect_user ($page = 'index.php') {

	// Start defining the URL...
	// URL is http:// plus the host name plus the current directory:
	$url = 'http://' . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']);
	
	// Remove any trailing slashes:
	$url = rtrim($url, '/\\');
	
	// Add the page:
	$url .= '/' . $page;
	
	// Redirect the user:
	header("Location: $url");
	exit(); // Quit the script.

} // End of redirect_user() function.


/* This function validates the form data (the email address and password).
 * If both are present, the database is queried.
 * The function requires a database connection.
 * The function returns an array of information, including:
 * - a TRUE/FALSE variable indicating success
 * - an array of either errors or the database result
 */
function check_login($conn, $user_name = '', $pass = '') {

	$errors = array(); // Initialize error array.

	// Validate the email address:
	$us = mysqli_real_escape_string($conn, trim($user_name));
	//Initialize the password:
        $p = mysqli_real_escape_string($conn, trim($pass));

		// Retrieve user_name to query against admins
		$q = "SELECT user_name FROM admins WHERE user_name='$us'";//AND pass=SHA1('$p')";		
		$r = @mysqli_query ($conn, $q); // Run the query.
		
		// Check the result:
		if (mysqli_num_rows($r) == 1) { //if admin, query username and password to set admin_id/username
                    $q = "SELECT admin_id, user_name FROM admins WHERE user_name='$us'AND pass=SHA1('$p')";
                    $r = @mysqli_query ($conn, $q); // Run the query.
                    if (mysqli_num_rows($r) == 1) {//Match
			// Fetch the record:
			$row = mysqli_fetch_array ($r, MYSQLI_ASSOC);
                        // Return true and the record:
			return array(true, $row);
                    }else{//Not a match
                        echo '<p> The username and password entered fo not match those on file.</p>';
                    }//end of admin search    
                } else { // if not admin, query against users table
			$q = "SELECT user_id, user_name FROM users WHERE user_name='$us'AND pass=SHA1('$p')";
                        $r = @mysqli_query ($conn, $q); // Run the query.
                        if (mysqli_num_rows($r) == 1) {//Match
                            // Fetch the record:
                            $row = mysqli_fetch_array ($r, MYSQLI_ASSOC);
                            // Return true and the record:
                            return array(true, $row);
                        }else{//Not a match
                            echo '<p> The username and password entered do not match those on file.</p>';
                        }//end of user search   
		}
	
	// Return false and the errors:
	return array(false, $errors);

} // End of check_login() function.