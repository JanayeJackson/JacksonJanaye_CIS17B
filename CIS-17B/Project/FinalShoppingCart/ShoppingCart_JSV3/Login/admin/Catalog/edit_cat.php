<?php 
/* 
 * script:   edit_cat.php
 * Author: Janaye Jackson
 *
 * Created on June 5th, 2024, 9:52 PM
 * Purpose: This page is for editing an item record.
 *          This page is accessed through view_cat.php.
 */
//access cookie session
session_start();
$page_title = 'Edit an Item';
include ('includes/display.html');
echo '<h1>Edit an Item</h1>';
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
            $upload =false;
            // Edit item in the database:
            //Initialize required variables
            $name = trim($_POST['name']);
            // Move the file over:
            if(is_uploaded_file ($_FILES['image']['tmp_name'])){
                $temp = 'pics/' . md5($_FILES['image']['name']);
                if (move_uploaded_file($_FILES['image']['tmp_name'], $temp)) {
                    $upload = true;
                    echo '<p>The file has been uploaded!</p>';
                    // Set the $i variable to the image's name:
                    $i = $_FILES['image']['name'];
                } else { // Couldn't move the file over.
                    echo '<p>The file could not be moved.</p>';
                    $temp = $_FILES['image']['tmp_name'];
                }
            }
            // Check for a price:
            if (is_numeric($_POST['price']) && ($_POST['price'] > 0)) {
		$pr = (float) $_POST['price'];
            } else {
		 echo '<p>Please enter a valid price! </p>';
            }
            // Check for a size (not required):
            if (is_numeric($_POST['size']) && ($_POST['size'] > 0) && ($_POST['size']) < 11) {
		$si = (int) $_POST['size'];
            } else {
		 $si = NULL;
            }
            // Check for a description (not required):
            $d = (!empty($_POST['description'])) ? trim($_POST['description']) : NULL;

            //  Test for unique email address:
           $q = "SELECT item_id FROM catalog WHERE name='$name' AND item_id != $id";
            $r = @mysqli_query($conn, $q);
            if (mysqli_num_rows($r) == 0) {
                // Make the query:
                if($upload){
                    $q = "UPDATE catalog SET name='$name', image='$i', price='$pr', size='$si', description='$d'  WHERE item_id=$id LIMIT 1";
                }
                else{
                     $q = "UPDATE catalog SET name='$name', price='$pr', size='$si', description='$d'  WHERE item_id=$id LIMIT 1";
                }
                $r = @mysqli_query ($conn, $q);
                if (mysqli_affected_rows($conn) == 1) { // If it ran ok, Print a message:
                    echo '<p>The item has been edited.</p>';	
                } else { // If it did not run OK.
                    echo '<p class="error">The item could not be edited due to a system error.</p>'; // Public message.
                    echo '<p>' . mysqli_error($conn) . '<br />Query: ' . $q . '</p>'; // Debugging message.
                }			
            } else { // Already registered.
		echo '<p class="error">The item already exists.</p>';
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
$q = "SELECT name, image, price, size, description FROM catalog WHERE item_id=$id";		
$r = @mysqli_query ($conn, $q);

if (mysqli_num_rows($r) == 1) { // Valid user ID, show the form.
	// Get the user's information:
	$row = mysqli_fetch_array ($r, MYSQLI_NUM);
	
        // Create the form:
        echo'<form enctype="multipart/form-data" action="edit_cat.php" method="post">
                <input type="hidden" name="MAX_FILE_SIZE" value="524288" />
                <fieldset><legend>Fill out the form to edit an item to the catalog:</legend>
                <p>Item Name: <input type="text" name="name" size="40" maxlength="100" value="' . $row[0] . '" /></p>
                <p>Image: <input type="file" name="image"/></p>
                <p>Price: <input type="text" name="price" size="20" maxlength="60" value="' . $row[2] . '"  /> </p>
                <p>Size: <input type="text" name="size" size="2" maxlength="10" value="'.$row[3].'" /></p>
                <p>Description: <br><textarea name="description" cols="40" rows="5" value="'.$row[4].'"/></textarea></br> (optional)</p>
                <input type="hidden" name="id" value="' . $id . '" />
                <input type="hidden" name="user" value="' . $user . '" />
            </fieldset>	
            <div align="center"><input type="submit" name="submit" value="Submit" /></div>
        </form>';
	

        } else { // Not a valid user ID.
            echo '<p class="error">This page has been accessed in error.</p>';
        }

    mysqli_close($conn);
		
include ('includes/footer.html');
?>