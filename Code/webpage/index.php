<?php  
$page = $_SERVER['PHP_SELF'];
$sec = "5";

$message = '';  
$user = 'Peter';

$servername = "localhost"; 
$username = "editor";
$password = "100%Domotics";
$dbname = "domotics";

$value = '';
$state = '';

$id = '';

onload(); 

function onLoad(){
checkLed(); 
}

function checkLed(){ //check the status of all the leds and give them the correct color;
	//Lights
	$GLOBALS['$id'] = 2; readLed(); $GLOBALS['$id'] = 1; writeLed();
	$GLOBALS['$id'] = 6; readLed(); writeLed();
	$GLOBALS['$id'] = 22; readLed(); $GLOBALS['$id'] = 21; writeLed();
}

function alert(){ //this function is triggered once the emergency button is pressed, the admin page will pickup on the database change and react accordingly.
				
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
	} 
				
	$localState = $GLOBALS['$state'];
	$localId = $GLOBALS['$id'];
    $sql = "UPDATE dashData SET val=1 WHERE id=1";

    if ($conn->query($sql) === TRUE) {
    } else {
         echo "Error updating record: " . $conn->error;
    }

    $conn->close();
	onload();
}

function readLed(){ //checks the status of a led.
					
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
	while($row = $result->fetch_assoc()) {				
		$GLOBALS['$state'] = $row["stateVal"] ;
		}
		} else {
		echo "item not found";
		}
	$conn->close();
}

function writeLed(){ //write the .bulb leds with the corresponding color based on the status from each led from the database.
	if($GLOBALS['$state'] == 0){
	 ?>
			<style type="text/css">
				#Cl<?=$GLOBALS['$id']?> {
					background: red;
				}
			</style>
	<?php
	} 
	else if($GLOBALS['$state'] == 1){
	 ?>
			<style type="text/css">
				#Cl<?=$GLOBALS['$id']?> {
				   background: #00cc00;
				}
			</style>
	<?php
	} 
	else{
		echo 'Error: A Led has an incorrect or no value in database.';
	}
}
function toggle(){ //toggle function to switch between 1 and 0, is triggered when a button is pressed.
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
				
function write(){ //writes a given id with new information from toggle().
				
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
	onload();
}

function read(){ //checks data from the database to be used in toggle().
					
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
	while($row = $result->fetch_assoc()) {
		echo "State changed from " . $row["stateVal"] ;				
		$GLOBALS['$state'] = $row["stateVal"] ;
		}
		} else {
		echo "0 results";
		}
	$conn->close();
}
function slider(){ //write function adjusted for the Ledstrip slider.
	
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
	} 
				
	$localValue = $GLOBALS['$value'];
	$localId = $GLOBALS['$id'];
    $sql = "UPDATE Sensor SET stateVal=$localValue WHERE id=$localId";

    if ($conn->query($sql) === TRUE) {
    } else {
         echo "Error updating record: " . $conn->error;
    }
				
    $conn->close();	
	$localValue = '';
	$localId = '';
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

					<input type="submit" name="toggleAlert" value="Press for Emergencies" class="Button2"/>
					<div class="message">
					<?php
						if(array_key_exists('toggleAlert',$_POST)){
							alert();
						}					
					?>
					</div>
				</div>
				
				<div class="button-group">
					<div class="box">
						<div class="bulb" id="Cl1"></div>
						<h3>Bedlamp</h3>
					</div>
					
					<input type="submit" name="toggle2" value="Turn On/Off" class="button"/>
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
						<div class="bulb" id="Cl6"></div>
						<h3>Lamp</h3>
					</div>
					
					<input type="submit" name="toggle6" value="Turn On/Off" class="button"/>

					<div class="message">
					<?php
						if(array_key_exists('toggle6',$_POST)){
							$GLOBALS['$id'] = 6;
							toggle();
						}
					?>
					</div>
				</div>
				<div class="button-group">
				
					<div class="box">
						<div class="bulb" id="Cl21"></div>
						<h3>Chairlamp</h3>
					</div>
					
					<input type="submit" name="toggle22" value="Turn On/Off" class="button"/>

					<div class="message">
					<?php
						if(array_key_exists('toggle22',$_POST)){
							$GLOBALS['$id'] = 22;
							toggle();
						}
					?>
					</div>
				</div>
				<div class="button-group">
					<div class="box">
					<h3>Ledstrip</h3> 
					<div id="bar"></div>
					</div>
						
						
					<input type="range" min="0" max="10" step="1" value="1" id="slider" name="light" onchange='document.getElementById("bar").innerHTML = document.getElementById("slider").value;'/>
						
					<input type=submit value="Toggle" class="button" /> 
					
					<div class="message">
					<?php
					if(isset($_POST["light"])){
						echo "State changed to: ".$_POST["light"];
						$GLOBALS['$value'] = $_POST["light"];
						$GLOBALS['$id'] = 14;
						slider();	
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
 
 
 

 
