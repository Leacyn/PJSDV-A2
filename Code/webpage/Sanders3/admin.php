<?php  
$page = $_SERVER['PHP_SELF'];
$sec = "10";

$message = '';  
$user = 'Admin';

$servername = "localhost";  //$servername = "localhost"; 
$username = "editor"; 		//$username = "editor";
$password = "100%Domotics"; //$password = "100%Domotics";
$dbname = "domotics"; 		//$password = "100%Domotics";

$value = '';
$state = '';

$id = '';

function toggle(){
	read();
				
	if($GLOBALS['$state'] == 1){
		$GLOBALS['$state'] = 2;
	}
	else if($GLOBALS['$state'] == 2){
		$GLOBALS['$state'] = 1;
	}
	else{
		echo "Error: Incorrect State";
	}
	
	write();
}
				
function write(){
				
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
	} 
				
	$localState = $GLOBALS['$state'];
	$localId = $GLOBALS['$id'];
    $sql = "UPDATE Sensor SET stateVal=$localState WHERE id=$localId"; //$sql = "UPDATE Sensor SET stateVal=$localState WHERE id=$localId";

    if ($conn->query($sql) === TRUE) {
    } else {
         echo "Error updating record: " . $conn->error;
    }
				
	echo " to $localState.";
    $conn->close();

}

function read(){
					
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
				
	$value = $GLOBALS['$id'];
	$sql = "SELECT stateVal FROM Sensor WHERE id=$value"; //$sql = "SELECT stateVal FROM Sensor WHERE id=$value";
	$result = $conn->query($sql);
				
	if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {
		echo "State changed from " . $row["stateVal"] ;				
		$GLOBALS['$state'] = $row["stateVal"] ;
		}
		} else {
		echo "0 results";
		}
	$conn->close();
}
 ?>  
 
<!DOCTYPE html>  
 <html>  
      <head>  
           <title>Dashboard</title> 

			<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
			
      </head> 
	  
      <body>  
			<div id="header">
				<div class="user">
					<p>Welcome, <?php echo $user; ?></p>
				</div>
				<div class="exit">
					<a href="index.php" class="exit-button"/>Exit</a>
				</div>
			</div>
			
			<div class="container">
				<form method="post">
					
					<h3>Object A</h3>
					<input type="submit" name="toggle1" value="Toggle State" class="button"/>
					
					<div class="message">
					<?php
						if(array_key_exists('toggle1',$_POST)){
							$GLOBALS['$id'] = 1;
							toggle();
						}
					?>
					</div>
					
					<h3>Object B</h3>
					<input type="submit" name="toggle2" value="Toggle State" class="button"/>
					
					<div class="message">
					<?php
						if(array_key_exists('toggle2',$_POST)){
							$GLOBALS['$id'] = 2;
							toggle();
						}					
					?>
					</div>
					
					<h3>Object C</h3>
					<input type="submit" name="toggle3" value="Toggle State" class="button"/>
					
					<div class="message">
						<?php
						if(array_key_exists('toggle3',$_POST)){
							$GLOBALS['$id'] = 3;
							toggle();
						}
						?>
					</div>
			
				</form>
			</div>

	  <div id="messages">
			<?php  
                if(isset($message))  
                {  
				echo $message;  
                }  
            ?> 
			
			<?php   
				if(isset($error))  
				{  
				echo $error;  
				}  
            ?>  
	  </div>
	  </body> 
	  
	 <style>
			body { margin: 0; background-color: white;  font-family: Arial, Helvetica, sans-serif;}
			h3   {color: black;}
			label{color: darkblue;}
			p { margin-left: 15px; color: black; font-weight: bold;}
			
			.container{padding: 75px 50px 50px 50px; max-width: 100%; text-align: left;}
			.input {width: 50%; font-size: 24px; margin-bottom: 5px;}
			label {margin-left: 25%;}
			.error { color: red; font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;}
			.success { color: green; font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;} 
			.user {float: left;}
			
			#header{ position: fixed; top: 0; height: 50px; width: 100%; background-color: lightgrey; box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2); float: left;}
			#messages{ position: fixed; bottom: 0; height: 50px; width: 100%; background-color: lightgrey;}
			.button {background-color: grey; border: none; color: white; padding: 15px; text-align: center; text-decoration: none; display: block; font-size: 16px; margin-bottom: 5px;}	
			.exit-button {background-color: grey; border: none; color: white; width: 75px; float: right; padding: 15px; text-align: center; text-decoration: none; display: block; font-size: 16px;}		
			
			.message{height: 10px; font-weight: bold; color: #0078FF;}
	</style>
			
 </html>  
 
 
 

 
