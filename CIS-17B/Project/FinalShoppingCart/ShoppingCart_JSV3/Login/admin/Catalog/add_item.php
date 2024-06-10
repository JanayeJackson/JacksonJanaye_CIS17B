<?php 
/* 
 * script:   add_item.php
 * Author: Janaye Jackson
 *
 * Created on June 1st, 2024, 1:52 AM
 * Purpose: This page allows the administrator to add new items to catalog
 */
    //access cookie session
    session_start();
    $page_title = 'Add an Item';
    include ('../includes/header.html');
    require ('../../../../Connect.php');
    echo '<h1>Add an Item</h1>';
    //access cookie session
    session_start();
    // Check for valid admin id
    if ( (!isset($_SESSION['admin_id']))) { // From cookie session
	echo '<p class="error">You do not have permission to view this page.</p>';
        include ('../includes/footer.html'); 
	exit();
    }
    if ($_SERVER['REQUEST_METHOD'] == 'POST') { // Handle the form.
        // Add item to the database:
        //Initialize required variables
	$name = trim($_POST['name']);
	// Create a temporary file name:
	$temp = '../../uploads/' . md5($_FILES['image']['name']);
	// Move the file over:
	if (move_uploaded_file($_FILES['image']['tmp_name'], $temp)) {
            echo '<p>The file has been uploaded!</p>';
            // Set the $i variable to the image's name:
            $i = $_FILES['image']['name'];
        } else { // Couldn't move the file over.
            echo '<p>The file could not be moved.</p>';
            $temp = $_FILES['image']['tmp_name'];
        }
	// Check for a price:
	if (is_numeric($_POST['price']) && ($_POST['price'] > 0)) {
		$p = (float) $_POST['price'];
	} else {
		 echo '<p>Please enter a valid price! </p>';
	}
        // Check for a color (not required):
	if (is_numeric($_POST['size']) && ($_POST['size'] > 0) && ($_POST['size']) < 11) {
		$si = (int) $_POST['size'];
	} else {
		 $si = NULL;
	}
	// Check for a description (not required):
	$d = (!empty($_POST['description'])) ? trim($_POST['description']) : NULL;
	
	$q = "INSERT INTO catalog (name, image, price, size, description) "
                    . "VALUES ('$name', '$i', '$p','$si','$d')";
        $r = @mysqli_query ($conn, $q); // Run the query.
        if ($r) { // If it ran ok, print a message:
            echo '<h1>ADDED!</h1>
            <p>item has been added!</p><p><br /></p>';	
        } else { // If it did not run ok, display error:
            echo '<h1>System Error</h1>
            <p class="error">Item could not be added due to a system error.</p>'; 
            // Debugging message:
            echo '<p>' . mysqli_error($conn) . '<br /><br />Query: ' . $q . '</p>';			
        } // End of if ($r) IF.
        mysqli_close($conn); // Close the database connection.
            // Include the footer and quit the script:
        include ('../includes/footer.html'); 
	// Delete the uploaded file if it still exists:
	if ( isset($temp) && file_exists ($temp) && is_file($temp) ) {
		unlink ($temp);
	}
} // End of the submission

// Display the form...
?>
<h1>Add an Item</h1>
<form enctype="multipart/form-data" action="add_item.php" method="post">
	<input type="hidden" name="MAX_FILE_SIZE" value="524288" />
	<fieldset><legend>Fill out the form to add an item to the catalog:</legend>
	<p>Item Name:</b> <input type="text" name="name" size="30" maxlength="60" value="<?php if (isset($_POST['name'])) echo htmlspecialchars($_POST['name']); ?>" required/></p>
	<p>Image: <input type="file" name="image" /></p>
	<p>Price: <input type="text" name="price" size="10" maxlength="10" value="<?php if (isset($_POST['price'])) echo $_POST['price']; ?>" required/><small>Do not include the dollar sign or commas.</small> </p>
        <p>Color: <input type="text" name="color" size="10" maxlength="10" value="<?php if(isset($_POST['color'])) echo $_POST['color']; ?>"/>(optional)</p>
	<p><b>Description:</b> <textarea name="description" cols="40" rows="5"><?php if (isset($_POST['description'])) echo $_POST['description']; ?></textarea> (optional)</p>
	</fieldset>	
	<div align="center"><input type="submit" name="submit" value="Submit" /></div>

</form>
<?php include ('../includes/footer.html'); ?>
