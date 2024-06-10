<?php
/* 
 * script:   view_admin.php
 * Author: Janaye Jackson
 *
 * Created on May 30th, 2024, 10:32 PM
 * Purpose: This script retrieves all the records from the admins table.
 *          This new version allows the results to be sorted in different ways.
 */

//access cookie session
session_start();

$page_title = 'View the Current Users';
include ('includes/header.html');
echo '<h1>Registered Users</h1>';
    // Check for a valid user ID, through GET or POST:
    if (isset($_SESSION['admin_id'])) { // From view_users.php
        $user = $_SESSION['user_name'];
    } else { // No valid ID, kill the script.
	echo '<p class="error">You do not have access to this page</br> Please login as admin.</p>';
	include ('includes/footer.html'); 
	exit();
    }
    require ('../../Connect.php');
    // Number of records to show per page, only 10 admins allowed:
    $display = 10;
    $start = 0;
    $sort = (isset($_GET['sort'])) ? $_GET['sort'] : 'ln';
    // Determine the sorting order:
    switch ($sort) {
        case 'ln':
            $order_by = 'last_name ASC';
            break;
        case 'fn':
            $order_by = 'first_name ASC';
            break;
        case 'rd':
            $order_by = 'registration_date ASC';
            break;
        default:
            $order_by = 'registration_date ASC';
            $sort = 'rd';
            break;
        }
	
        // Define the query:
        $q = "SELECT last_name, first_name, user_name, DATE_FORMAT(add_date, '%M %d, %Y') AS dr, admin_id FROM admins ORDER BY $order_by LIMIT $start, $display";		
        $r = @mysqli_query ($conn, $q); // Run the query.

        // Table header:
        echo '<table align="center" cellspacing="0" cellpadding="5" width="75%">
        <tr>
            <td align="left"><b>Edit</b></td>
            <td align="left"><b>Delete</b></td>
            <td align="left"><b><a href="view_admin.php?sort=ln">Last Name</a></b></td>
            <td align="left"><b><a href="view_admin.php?sort=fn">First Name</a></b></td>
            <td align="left"><b><a href="view_admin.php?sort=us">Username</a></b></td>
            <td align="left"><b><a href="view_admin.php?sort=rd">Date Registered</a></b></td>
        </tr>
        ';

        // Fetch and print all the records....
        $bg = '#eeeeee'; 
        while ($row = mysqli_fetch_array($r, MYSQLI_ASSOC)) {
            $bg = ($bg=='#eeeeee' ? '#ffffff' : '#eeeeee');
		echo '<tr bgcolor="' . $bg . '">
                <td align="left"><a href="edit_admin.php?id=' . $row['admin_id'] . '&user=' . $user .'">Edit</a></td>
		<td align="left"><a href="delete_admin.php?id=' . $row['admin_id'] . '&user='.$user.'">Delete</a></td>
		<td align="left">' . $row['last_name'] . '</td>
		<td align="left">' . $row['first_name'] . '</td>
		<td align="left">' . $row['user_name'] . '</td>
                <td align="left">' . $row['dr'] . '</td>
            </tr>
            ';
        } // End of WHILE loop.

        echo '</table>';
        mysqli_free_result ($r);
        mysqli_close($conn);
        include ('includes/footer.html');
?>

