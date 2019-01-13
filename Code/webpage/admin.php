<?php  
$page = $_SERVER['PHP_SELF'];
$sec = "5";

$message = '';  
$user = 'Admin';


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
checkWarnings();
}

function checkLed(){ //check the status of all the leds and give them the correct color;
	//Lights
	$GLOBALS['$id'] = 2; readLed(); $GLOBALS['$id'] = 1; writeLed();
	$GLOBALS['$id'] = 6; readLed(); writeLed();
	$GLOBALS['$id'] = 22; readLed(); $GLOBALS['$id'] = 21; writeLed();

	//alerts
	$GLOBALS['$id'] = 3; readLed(); writeLed();
	$GLOBALS['$id'] = 4; readLed(); writeLed();
	$GLOBALS['$id'] = 7; readLed(); writeLed();
	$GLOBALS['$id'] = 10; readLed(); writeLed();
	$GLOBALS['$id'] = 15; readLed(); writeLed();
	$GLOBALS['$id'] = 16; readLed(); writeLed();
	$GLOBALS['$id'] = 17; readLed(); writeLed();

	//center buttons
	$GLOBALS['$id'] = 5; readLed(); writeLed();
	$GLOBALS['$id'] = 8; readLed(); writeLed();
	$GLOBALS['$id'] = 9; readLed(); writeLed();
	$GLOBALS['$id'] = 11; readLed(); writeLed();
	$GLOBALS['$id'] = 12; readLed(); writeLed();
	$GLOBALS['$id'] = 13; readLed(); writeLed();
	$GLOBALS['$id'] = 18; readLed(); writeLed();
	$GLOBALS['$id'] = 19; readLed(); writeLed();
	$GLOBALS['$id'] = 20; readLed(); writeLed();
}

function readLed(){  //checks the status of a led.					
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
	while($row = $result->fetch_assoc()) {
		//echo "State changed from " . $row["password"] ;				
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

function checkWarnings(){ //as soon as a warning is triggered on the patients page, this function will detect it and create the pop-up.
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
				
	$value = $GLOBALS['$id'];
	$sql = "SELECT val FROM dashData WHERE id=1"; //$sql = "SELECT stateVal FROM Sensor WHERE id=$value";
	$result = $conn->query($sql);
				
	if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {				
		$GLOBALS['$state'] = $row["val"];
		}
		} else {
		echo "0 results";
		}
	$conn->close();
	
	if($GLOBALS['$state'] == 0){
	 ?>
			<style type="text/css">
				.pop-back {
				visibility: hidden;
			}
			</style>
	<?php
	} 
	
	else if($GLOBALS['$state'] == 1){
	 ?>
			<style type="text/css">
				.pop-back {
					visibility: visible;
				}
			</style>
	<?php
	$GLOBALS['$message'] = "Patient has pressed the emergency button.";
	}
	

	else if($GLOBALS['$state'] == 2){
	 ?>
			<style type="text/css">
				.pop-back {
					visibility: visible;
				}
			</style>
	<?php
	$GLOBALS['$message'] = "The smoke detector in the patients room has gone off.";
	}
	
	else{
	 echo 'Error: alertId has an incorrect or no value in database.';
	}
}

function dismissWarning(){ //dismissed the pop-up once the dismiss button is pressed.
// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
	} 

    $sql = "UPDATE dashData SET val=0 WHERE id=1";

    if ($conn->query($sql) === TRUE) {
    } else {
         echo "Error updating record: " . $conn->error;
    }

    $conn->close();
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

<html>  
      <head>  
        <title>Dashboard</title> 

		<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
		<link rel="stylesheet" type="text/css" media="screen" href="style.php">
		
		<div class="pop-back">
			<div class="pop-up">
				<div class="pop-header">
				<h1> Warning! </h1>
				<form method="post">
					<input type="submit" name="closeWarning" value="Dismiss" class="CloseButton"/>
					<div class="message">
						<?php
						if(array_key_exists('closeWarning',$_POST)){ //hides the pop-up and dismisses the trigger.
						?>
						<style type="text/css">
							.pop-back {
								visibility: hidden;
							}
						</style>
						<?php
						dismissWarning();
						}
						?>
						</div>
				</div>
				<h2><?php echo $GLOBALS['$message'];?></h2>
			</div>
		</div>
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
	
	<div class="left">
		<div class="lights">
			<h1>Lights</h1>
			<form method="post">
				
				<div class="object">
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
				<div class="object">
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
		
		<div class="alerts">
			<h1>Alerts</h1>
			<form method="post">
				<div class="alert">
					<div class="box">
						<div class="bulb" id="Cl3"></div>
						<h3>Bed Pressure Sensor</h3>
					</div>
					
					<div class="box">
						<div class="bulb" id="Cl4"></div>
						<h3>Chair Pressure sensor</h3>
					</div>
					
					<div class="box">
						<div class="bulb" id="Cl7"></div>
						<h3>Lamp Motion Sensor</h3>
					</div>
					
					<div class="box">
						<div class="bulb" id="Cl10"></div>
						<h3>Smoke detector</h3>
					</div>
					
				</div>
				<div class="alert">		
					<div class="box">
						<div class="bulb" id="Cl15"></div>
						<h3>Fridge Door</h3>
					</div>
					
					<div class="box">
						<div class="bulb" id="Cl16"></div>
						<h3>Cooler</h3>
					</div>
				
					<div class="box">
						<div class="bulb" id="Cl17"></div>
						<h3>Doorlight</h3>
					</div>
					
				</div>
			</div>
		</form>
	</div>
	
	<div class="center">
		<form method="post">
			<div class="object">	
				<div class="box">
					<div class="bulb" id="Cl5"></div>
					<h3>Chair Vibration</h3>
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

				<div class="box">
					<div class="bulb" id="Cl8"></div>
					<h3>Column switch</h3>
				</div>
				
				<input type="submit" name="toggle8" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle8',$_POST)){
						$GLOBALS['$id'] = 8;
						toggle();
					}					
				?>
				</div>

				<div class="box">
					<div class="bulb" id="Cl9"></div>
					<h3>Column Buzzer</h3>
				</div>
				
				<input type="submit" name="toggle9" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle9',$_POST)){
						$GLOBALS['$id'] = 9;
						toggle();
					}
				?>
				</div>

				<div class="box">
					<div class="bulb" id="Cl11"></div>
					<h3>Wall LDR</h3>
				</div>
				
				<input type="submit" name="toggle11" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle11',$_POST)){
						$GLOBALS['$id'] = 11;
						toggle();
					}
				?>
				</div>

				<div class="box">
					<div class="bulb" id="Cl12"></div>
					<h3>Wall Dimmer</h3>
				</div>
				
				<input type="submit" name="toggle12" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle12',$_POST)){
						$GLOBALS['$id'] = 12;
						toggle();
					}					
				?>
				</div>
			</div>
			<div class="object">	
				<div class="box">
					<div class="bulb" id="Cl13"></div>
					<h3>Window</h3>
				</div>
				
				<input type="submit" name="toggle13" value="Toggle State" class="button"/>
				<div class="message">
					<?php
					if(array_key_exists('toggle13',$_POST)){
						$GLOBALS['$id'] = 13;
						toggle();
					}
					?>
				</div>

				<div class="box">
					<div class="bulb" id="Cl18"></div>
					<h3>Servo</h3>
				</div>
				
				<input type="submit" name="toggle18" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle18',$_POST)){
						$GLOBALS['$id'] = 18;
						toggle();
					}					
				?>
				</div>
				
				<div class="box">
					<div class="bulb" id="Cl19"></div>
					<h3>Doorknob Room</h3>
				</div>

				<input type="submit" name="toggle19" value="Toggle State" class="button"/>
				<div class="message">
					<?php
					if(array_key_exists('toggle19',$_POST)){
						$GLOBALS['$id'] = 19;
						toggle();
					}
					?>
				</div>

				<div class="box">
					<div class="bulb" id="Cl20"></div>
					<h3>Doorknob Hall</h3>
				</div>
				
				<input type="submit" name="toggle20" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle20',$_POST)){
						$GLOBALS['$id'] = 20;
						toggle();
					}
				?>
				</div>
			</div>
		</form>
	</div>
	
	<div class="right">
	<h1>Sleep statistics</h1>
	
				<div class="graph">
				<script type="text/javascript" src="loader.js"></script>
				<div id="chart_div"></div>
				
			</div>
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
	  
	<script>
	google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic);

	function drawBasic() {

      var data = new google.visualization.DataTable();
      data.addColumn('number', 'X');
      data.addColumn('number', 'activity');

      data.addRows([
        [1, 10],  [2, 20],  [3, 17],  [4, 18],  [5, 9],
        [6, 8],  [7, 27],  [8, 33],  [9, 40],  [10, 32], [11, 35],
        [12, 30], [13, 40], [14, 42], [15, 47], [16, 44], [17, 48],
        [18, 52], [19, 54], [20, 42], [21, 55], [22, 56], [23, 57],
        [24, 60], [25, 50], [26, 52], [27, 51], [28, 49], [29, 53]
    
      ]);

      var options = {
        hAxis: {
          title: 'Time'
        },
        vAxis: {
          title: 'Motion'
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div'));

      chart.draw(data, options);
    }
	</script>
 </html>  
 
 
 

 
