<?php 
/* 
 * script:   edit_admin.php
 * Author: Janaye Jackson
 *
 * Created on May 30th, 2024, 11:22 PM
 * Purpose: This page is for editing an admin record.
 *          This page is accessed through view_admin.php.
 */
//access cookie session
session_start();
$page_title = 'Edit an Admin';
include ('includes/header.html');
echo '<h1>Edit an Admin</h1>';
    // Check for a valid user ID, through GET or POST:
    if ( (isset($_GET['id'])) && (is_numeric($_GET['id'])) ) { // From view_users.php
	$id = $_GET['id'];
        $user = $_GET['user'];
    } elseif ( (isset($_POST['id'])) && (is_numeric($_POST['id'])) ) { // Form submission.
	$id = $_POST['id'];
        $user = $_POST['user'];
    } else { // No valid ID, kill the script.
	echo '<p class="error">This page has been accessed in error.</p>';
	include ('includes/footer.html'); 
	exit();
    }
    require ('../../Connect.php');
    // Check that user is an admin
    $q = "SELECT admin_id FROM admins WHERE (user_name='$user')";
    $r = @mysqli_query($conn, $q);
    $num = @mysqli_num_rows($r);
    if ($num == 1) { // Match was made.
        // Check if the form has been submitted:
        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            $fn = mysqli_real_escape_string($conn, trim($_POST['first_name']));
            $ln = mysqli_real_escape_string($conn, trim($_POST['last_name']));
            $em = mysqli_real_escape_string($conn, trim($_POST['email']));
            //  Test for unique email address:
            $q = "SELECT admin_id FROM admins WHERE email='$em' AND admin_id != $id";
            $r = @mysqli_query($conn, $q);
            if (mysqli_num_rows($r) == 0) {
                // Make the query:
                $q = "UPDATE admins SET first_name='$fn', last_name='$ln', email='$em' WHERE admin_id=$id LIMIT 1";
                $r = @mysqli_query ($conn, $q);
                if (mysqli_affected_rows($conn) == 1) { // If it ran ok, Print a message:
                    echo '<p>The admin has been edited.</p>';	
                } else { // If it did not run OK.
                    echo '<p class="error">The admin could not be edited due to a system error.</p>'; // Public message.
                    echo '<p>' . mysqli_error($conn) . '<br />Query: ' . $q . '</p>'; // Debugging message.
                }			
            } else { // Already registered.
		echo '<p class="error">The email address has already been registered.</p>';
            }
		
        } // End of submit conditional.
    } else{
        mysqli_close($conn);
        echo'<p>You do not have permission to view this page</p>';
        include ('includes/footer.html');
        exit();
    }

// Always show the form...

// Retrieve the user's information:
$q = "SELECT first_name, last_name, email FROM admins WHERE admin_id=$id";		
$r = @mysqli_query ($conn, $q);

if (mysqli_num_rows($r) == 1) { // Valid user ID, show the form.
	// Get the user's information:
	$row = mysqli_fetch_array ($r, MYSQLI_NUM);
	
	// Create the form:
	echo '<form action="edit_admin.php" method="post">
            <p>First Name: <input type="text" name="first_name" size="15" maxlength="15" value="' . $row[0] . '" /></p>
            <p>Last Name: <input type="text" name="last_name" size="15" maxlength="30" value="' . $row[1] . '" /></p>
            <p>Email Address: <input type="text" name="email" size="20" maxlength="60" value="' . $row[2] . '"  /> </p>
            <p><input type="submit" name="submit" value="Submit" /></p>
            <input type="hidden" name="id" value="' . $id . '" />
        </form>';

        } else { // Not a valid user ID.
            echo '<p class="error">This page has been accessed in error.</p>';
        }

    mysqli_close($conn);
		
include ('includes/footer.html');
?>
