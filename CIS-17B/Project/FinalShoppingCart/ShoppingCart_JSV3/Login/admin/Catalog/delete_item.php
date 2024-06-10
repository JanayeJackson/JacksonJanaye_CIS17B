<?php 
/* 
 * script:   delete_item.php
 * Author: Janaye Jackson
 *
 * Created on June 5th, 2024, 9:52 PM
 * Purpose: This page allows the administrator to delete items from catalog
 */

//access cookie session
session_start();
$page_title = 'Delete an Item';
include ('includes/display.html');
echo '<h1>Delete an Item</h1>';
// Check for a valid user ID, through GET or POST:
if ( (isset($_GET['id'])) && (is_numeric($_GET['id'])) ) { // From view_cat.php
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

require ('../../../Connect.php');

    // Check that user is an admin
    $q = "SELECT admin_id FROM admins WHERE (user_name='$user')";
    $r = @mysqli_query($conn, $q);
    $num = @mysqli_num_rows($r);
    if ($num == 1) { // Match was made.
    // Check if the form has been submitted:
        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            if ($_POST['sure'] == 'Yes') { // Delete the record.
		// Make the query:
		$q = "DELETE FROM catalog WHERE item_id=$id LIMIT 1";		
		$r = @mysqli_query ($conn, $q);
		if (mysqli_affected_rows($conn) == 1) { // If it ran OK.
			// Print a message:
			echo '<p>The item has been deleted.</p>';	

		} else { // If the query did not run OK.
			echo '<p class="error">The item could not be deleted due to a system error.</p>'; // Public message.
			echo '<p>' . mysqli_error($conn) . '<br />Query: ' . $q . '</p>'; // Debugging message.
		}
	
            } else { // No confirmation of deletion.
		echo '<p>The item has NOT been deleted.</p>';	
            }
        } else { // Show the form.
            // Retrieve the user's information:
            $q = "SELECT name FROM catalog WHERE item_id=$id";
            $r = @mysqli_query ($conn, $q);

            if (mysqli_num_rows($r) == 1) { // Valid user ID, show the form.
		// Get the user's information:
		$row = mysqli_fetch_array ($r, MYSQLI_NUM);
		// Display the record being deleted:
		echo "<h3>Name: $row[0]</h3>
		Are you sure you want to delete this item?";
		
		// Create the form:
		echo '<form action="delete_item.php" method="post">
                    <input type="radio" name="sure" value="Yes" /> Yes 
                    <input type="radio" name="sure" value="No" checked="checked" /> No
                    <input type="submit" name="submit" value="Submit" />
                    <input type="hidden" name="id" value="' . $id . '" />
                    <input type="hidden" name="user" value="' . $user . '" />
                </form>';
            } else { // Not a valid user ID.
		echo '<p class="error">This page has been accessed in error.</p>';
            }
        } // End of the main submission conditional.
        mysqli_close($conn);
        include ('includes/footer.html');
    }else{
        mysqli_close($conn);
        echo'<p>You do not have permission to view this page</p>';
        include ('includes/footer.html');
    } 
?>