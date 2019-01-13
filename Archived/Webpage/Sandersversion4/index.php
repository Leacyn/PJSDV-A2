<?php  
$page = $_SERVER['PHP_SELF'];
$sec = "10";

$message = '';  
$user = 'Peter';

$servername = "localhost"; 
$username = "editor";
$password = "100%Domotics";
$dbname = "domotics";

$value = '';
$state = '';

$id = '';

function toggle(){
	read();
	
	if($GLOBALS['$state'] == 0){
		$GLOBALS['$state'] = 1;
	}
	else if($GLOBALS['$state'] == 1){
		$GLOBALS['$state'] = 0;
	}
	else{
		echo "Error: Incorrect value in database.";
		$GLOBALS['$state'] = 0;
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
    $sql = "UPDATE Sensor SET stateVal=$localState WHERE id=$localId";

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
	$sql = "SELECT stateVal FROM Sensor WHERE id=$value";
	$result = $conn->query($sql);
				
	if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {
		echo "State changed from " . $row["password"] ;				
		$GLOBALS['$state'] = $row["password"] ;
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

			<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">-->
			<link rel="stylesheet" type="text/css" media="screen" href="style.php">
			
      </head> 
	  
      <body>  
			<div id="header">
				<div class="user">
					<p>Welcome, <?php echo $user; ?></p>
				</div>
				
				<div class="exit">
					<a href="login.php" class="login"/>Log in</a>
				</div>
				
			</div>
			
		<div class="container">
			<div class="panel">	
				<form method="post">
				
				<div class="button-group">
					<div class="box">
						<div class="bulb2"></div>
						<h3>Object A</h3>
					</div>
					
					<input type="submit" name="toggle1" value="Toggle State" class="button"/>

					<div class="message">
					<?php
						if(array_key_exists('toggle1',$_POST)){
							$GLOBALS['$id'] = 1;
							toggle();
						}
					?>
					</div>
				</div>
				
				<div class="button-group">
					<div class="box">
						<div class="bulb2"></div>
						<h3>Object B</h3>
					</div>
					
					<input type="submit" name="toggle2" value="Toggle State" class="button" onclick="test()"/>
					<div class="message">
					<?php
						if(array_key_exists('toggle2',$_POST)){
							$GLOBALS['$id'] = 2;
							toggle();
						}					
					?>
					</div>
				</div>
				<div class="button-group">	
					<div class="box">
						<div class="bulb2"></div>
						<h3>Object C</h3>
					</div>
					
					<input type="submit" name="toggle3" value="Toggle State" class="button"/>
					<div class="message">
						<?php
						if(array_key_exists('toggle3',$_POST)){
							$GLOBALS['$id'] = 3;
							toggle();
						}
						?>
					</div>
				</div>
				
				<div class="button-group">				
					<div class="box">
						<div class="bulb2"></div>
						<h3>Object D</h3>
					</div>
					
					<input type="submit" name="toggle4" value="Toggle State" class="button"/>

					<div class="message">
					<?php
						if(array_key_exists('toggle4',$_POST)){
							$GLOBALS['$id'] = 4;
							toggle();
						}
					?>
					</div>
				</div>
				
				<div class="button-group">
					<div class="box">
						<div class="bulb2"></div>
						<h3>Object E</h3>
					</div>
					
					<input type="submit" name="toggle5" value="Toggle State" class="button"/>

					<div class="message">
					<?php
						if(array_key_exists('toggle5',$_POST)){
							$GLOBALS['$id'] = 5;
							toggle();
						}
					?>
					</div>
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
 </html>  
 
 
 

 
