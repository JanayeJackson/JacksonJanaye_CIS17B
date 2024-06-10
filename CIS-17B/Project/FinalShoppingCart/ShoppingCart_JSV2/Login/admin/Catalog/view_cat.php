
<?php
	//Dr. Mark E. Lehr
	//Create a connection to the database
	//DB, UN, Pass, DB
        require_once ('../../../Connect.php'); // Connect to the db.
        session_start();
        include('display.html');//require_once ('ConnectTest.php'); // Connect to the db.
        
          
	//Query the database
        $sql="SELECT `item_id`, `name`, `image`, `color`, 
		               `description`, `price` FROM 		
					   `catalog`;";
        $result=$conn->query($sql);
        while($re = $result->fetch_assoc()){
        echo '<div id ="item">
                <div id= "image">
                    <img src="pics/'.$re['image'].'" alt="" />
                </div>
                <div id="description">
                    <span>'.$re['name'].'</span>    
                    <span>'.$re['description'].'</span>
                </div>
                <div id="quantity">
                    <button id="plus-btn" type="button" name="button">
                        <img src="pics/plus.svg" alt="" />
                    </button>
                <input type="text" name="name" value="1">
                    <button id="minus-btn" type="button" name="button">
                        <img src="pics/minus.svg" alt="" />
                    </button>
                </div>
            </div>';
        }
        echo '  </div>';
?>