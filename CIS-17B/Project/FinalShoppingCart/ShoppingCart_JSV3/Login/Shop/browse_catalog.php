
<?php
        session_start();
        $page_title = 'Browse Catalog';
        include('includes/header.html');//in
        echo '<h1>Catalog</h1>';
        // Check for a valid user ID, through GET or POST:
    if (isset($_SESSION['user_id'])) {
	$id = $_SESSION['user_id'];
    } else { // No valid ID, kill the script.
	echo '<p class="error">This page has been accessed in error.</p>';
	include ('includes/footer.html'); 
	exit();
    }
        require('../../Connect.php');
        // Number of records to show per page:
    $display = 10;

    // Determine how many pages there are...
    if (isset($_GET['p']) && is_numeric($_GET['p'])) { // Already been determined.
        $pages = $_GET['p'];
    } else { // Need to determine.
            // Count the number of records:
            $q = "SELECT COUNT(item_id) FROM catalog";
            $r = @mysqli_query ($conn, $q);
            $row = @mysqli_fetch_array ($r, MYSQLI_NUM);
            $records = $row[0];
            // Calculate the number of pages...
            if ($records > $display) { // More than 1 page.
		$pages = ceil ($records/$display);
            } else {
		$pages = 1;
            }
        } // End of p IF.

        // Determine where in the database to start returning results...
        if (isset($_GET['s']) && is_numeric($_GET['s'])) {
            $start = $_GET['s'];
        } else {
            $start = 0;
        }
        // Determine the sort...
        // Default is by last name.
        $sort = (isset($_GET['sort'])) ? $_GET['sort'] : 'n';
        // Determine the sorting order:
        switch ($sort) {
            case 'n':
		$order_by = 'name ASC';
		break;
            case 'pr':
		$order_by = 'price ASC';
		break;
            case 'si':
		$order_by = 'size ASC';
		break;
            default:
		$order_by = 'name ASC';
		$sort = 'n';
		break;
        }
        
        
        // Table header:
        echo '<table align="center" cellspacing="0" cellpadding="5" width="75%">
        <tr>
            <td align="left"><b>Item</b></td>
            <td align="left"><b><a href="browse_catalog.php?sort=n">Name</a></b></td>
            <td align="left"><b><a href="browse_catalog.php?sort=pr">Price</a></b></td>
            <td align="left"><b><a href="browse_catalog.php?sort=si">Size</a></b></td>
            <td align="left"><b>Add to Cart</b></td>
        </tr>
        ';
          
	//Query the database
        $sql="SELECT item_id, image, name, enum_size.size, price, description FROM catalog, enum_size "
                . "WHERE `catalog`.`size` = `enum_size`.`size_id` ORDER BY $order_by LIMIT $start, $display";
        $result=$conn->query($sql);
        // Fetch and print all the records....
        $bg = '#eeeeee'; 
        while($re = $result->fetch_assoc()){
            $bg = ($bg=='#eeeeee' ? '#ffffff' : '#eeeeee');
		echo '<tr bgcolor="' . $bg . '">
                <td id="image" align="left"><img src="pics/'.$re['image'].'" alt="" /></td>
                <td align="left">'.$re['name'].'</td>    
                <td align="left">'.$re['price'].'</td>
                <td align="left">'.$re['size'].'</td>
                <td align="left"><a href="add_cart.php?id=' . $re['item_id'] .'">Add To Cart</a></td>
                    </tr>';
        }
        echo '</table>';
        
        // Make the links to other pages, if necessary.
        if ($pages > 1) {
            echo '<br /><p>';
            $current_page = ($start/$display) + 1;
            // If it's not the first page, make a Previous button:
            if ($current_page != 1) {
		echo '<a href="view_cat.php?s=' . ($start - $display) . '&p=' . $pages . '&sort=' . $sort . '">Previous</a> ';
            }
            // Make all the numbered pages:
            for ($i = 1; $i <= $pages; $i++) {
		if ($i != $current_page) {
			echo '<a href="view_cat.php?s=' . (($display * ($i - 1))) . '&p=' . $pages . '&sort=' . $sort . '">' . $i . '</a> ';
		} else {
			echo $i . ' ';
		}
            } // End of FOR loop.
            // If it's not the last page, make a Next button:
            if ($current_page != $pages) {
		echo '<a href="view_cat.php?s=' . ($start + $display) . '&p=' . $pages . '&sort=' . $sort . '">Next</a>';
            }
            echo '</p>'; // Close the paragraph.	
        } // End of links section.
        include('includes/footer.html');
?>