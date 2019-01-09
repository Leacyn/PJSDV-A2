<?php  
$page = $_SERVER['PHP_SELF'];
$sec = "10";

$message = '';  
$user = 'Admin';

$servername = "localhost"; 
$username = "editor";
$password = "100%Domotics";
$dbname = "domotics";

$value = '';
$state = '';

$id = '';

$on = '#00ff00';
$off = 'red';
$inactive = '#ffcc00';

$L1 = $inactive; $L2 = $inactive; $L3 = $inactive; $L4 = $inactive; $L5 = $inactive; $L6 = $inactive; $L7 = $inactive; $L8 = $inactive; $L9 = $inactive; $L10 = $inactive;
$L11 = $inactive; $L12 = $inactive; $L13 = $inactive; $L14 = $inactive; $L15 = $inactive; $L16 = $inactive; $L17 = $inactive; $L18 = $inactive; $L19 = $inactive; $L20 = $inactive;
$L21 = $inactive; $L22 = $inactive; $L23 = $inactive; $L24 = $inactive; $L25 = $inactive;
/*
onload();
function onLoad(){
$on = '#00ff00';
$off = 'red';
$inactive = '#ffcc00';

$GLOBALS['$id'] = 1;

readLed();

if($GLOBALS['$state'] == 0){
	$GLOBALS['$L1'] = $off;
}
else if($GLOBALS['$state'] == 1){
	$GLOBALS['$L1'] = $on;
}
else{
	echo "Error: $L1 has incorrect or no value in database.";
}
echo $GLOBALS['$state'];
echo $GLOBALS['$L1'];
}

function readLed(){
					
	// Create connection
	$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 
				
	$value = $GLOBALS['$id'];
	$sql = "SELECT password FROM User_ WHERE id=$value"; //$sql = "SELECT stateVal FROM Sensor WHERE id=$value";
	$result = $conn->query($sql);
				
	if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {
		//echo "State changed from " . $row["password"] ;				
		$GLOBALS['$state'] = $row["password"] ;
		}
		} else {
		echo "item not found";
		}
	$conn->close();
}
*/
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
 


<html>  
      <head>  
        <title>Dashboard</title> 

		<!--<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">-->
		<link rel="stylesheet" type="text/css" media="screen" href="style.php">
			
      </head> 
	  
<body>  
	<div id="header">
		<div class="user">
			<p>Welcome, <?php echo $user; ?></p>
		</div>
		
		<div class="exit">
			<a href="index.php" class="exit-button"/>Exit</a>
		</div>
		
		<!--<div class="statusbar">
			<div class="bulb" id="Cl1"><i>LedA</i></div>
			<div class="bulb" id="Cl2"><i>LedB</i></div>
			<div class="bulb" id="Cl3"><i>LedC</i></div>
			<div class="bulb" id="Cl4"><i>LedD</i></div>
			<div class="bulb" id="Cl5"><i>LedE</i></div>
		</div>-->
		
	</div>
			
	<div class="container">
		
		<div class="object">
		<h1>Bed</h1>
			<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl1"></div>
					<h3>Nightlight</h3>
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
				
				<div class="box">
					<div class="bulb" id="Cl2"></div>
					<h3>Nightlight switch</h3>
				</div>
				
				<input type="submit" name="toggle2" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle2',$_POST)){
						$GLOBALS['$id'] = 2;
						toggle();
					}					
				?>
				</div>
				
				<div class="box">
					<div class="bulb" id="Cl3"></div>
					<h3>Pressure Sensor</h3>
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
			</form>
		</div>
		
		<div class="object">
		<h1>Chair</h1>
			<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl4"></div>
					<h3>Pressure sensor</h3>
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
				
				<div class="box">
					<div class="bulb" id="Cl5"></div>
					<h3>Vibration motor</h3>
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
			</form>
		</div>
		
		<div class="object">
		<h1>Lamp</h1>
			<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl6"></div>
					<h3>Light</h3>
				</div>
				
				<input type="submit" name="toggle6" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle6',$_POST)){
						$GLOBALS['$id'] = 6;
						toggle();
					}
				?>
				</div>
				
				<div class="box">
					<div class="bulb" id="Cl7"></div>
					<h3>Motion Sensor</h3>
				</div>
				
				<input type="submit" name="toggle7" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle7',$_POST)){
						$GLOBALS['$id'] = 7;
						toggle();
					}					
				?>
				</div>
			</form>
		</div>
		
		<div class="object">
		<h1>Column</h1>
			<form method="post">
	
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
					<h3>Buzzer</h3>
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
					<div class="bulb" id="Cl10"></div>
					<h3>Smoke detector</h3>
				</div>
				
				<input type="submit" name="toggle10" value="Toggle State" class="button"/>
				<div class="message">
					<?php
					if(array_key_exists('toggle10',$_POST)){
						$GLOBALS['$id'] = 10;
						toggle();
					}
					?>
				</div>
			</form>
		</div>

		<div class="object">
		<h1>Wall</h1>
			<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl11"></div>
					<h3>LDR</h3>
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
					<h3>Dimmer</h3>
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
					<div class="bulb" id="Cl14"></div>
					<h3>Ledstrip</h3>
				</div>
				
				<input type="submit" name="toggle14" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle14',$_POST)){
						$GLOBALS['$id'] = 14;
						toggle();
					}
				?>
				</div>
			</form>
		</div>
		
		<div class="object">
		<h1>Fridge</h1>
			<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl15"></div>
					<h3>Fridge Door</h3>
				</div>
				
				<input type="submit" name="toggle15" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle15',$_POST)){
						$GLOBALS['$id'] = 15;
						toggle();
					}
				?>
				</div>
				
				<div class="box">
					<div class="bulb" id="Cl16"></div>
					<h3>Cooler</h3>
				</div>
				
				<input type="submit" name="toggle16" value="Toggle State" class="button"/>
				<div class="message">
				<?php
					if(array_key_exists('toggle16',$_POST)){
						$GLOBALS['$id'] = 16;
						toggle();
					}					
				?>
				</div>

			</form>
		</div>
		
		<div class="object">
		<h1>Door</h1>
		<form method="post">
				
				<div class="box">
					<div class="bulb" id="Cl17"></div>
					<h3>Doorlight</h3>
				</div>
				
				<input type="submit" name="toggle17" value="Toggle State" class="button"/>

				<div class="message">
				<?php
					if(array_key_exists('toggle17',$_POST)){
						$GLOBALS['$id'] = 17;
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
	
			</form>
		</div>
			<!--<div class="graph">
				<script type="text/javascript" src="loader.js"></script>
				<div id="chart_div"></div>
				

				<div class="month">      
					<ul>
						<li class="prev">&#10094;</li>
						<li class="next">&#10095;</li>
						<li>
						August<br>
						<span style="font-size:18px">2017</span>
						</li>
					</ul>
				</div>

				<ul class="weekdays">
				  <li>Mo</li>
				  <li>Tu</li>
				  <li>We</li>
				  <li>Th</li>
				  <li>Fr</li>
				  <li>Sa</li>
				  <li>Su</li>
				</ul>

				<ul class="days">  
				  <li>1</li>
				  <li>2</li>
				  <li>3</li>
				  <li>4</li>
				  <li>5</li>
				  <li>6</li>
				  <li>7</li>
				  <li>8</li>
				  <li>9</li>
				  <li><span class="active">10</span></li>
				  <li>11</li>
				  <li>12</li>
				  <li>13</li>
				  <li>14</li>
				  <li>15</li>
				  <li>16</li>
				  <li>17</li>
				  <li>18</li>
				  <li>19</li>
				  <li>20</li>
				  <li>21</li>
				  <li>22</li>
				  <li>23</li>
				  <li>24</li>
				  <li>25</li>
				  <li>26</li>
				  <li>27</li>
				  <li>28</li>
				  <li>29</li>
				  <li>30</li>
				  <li>31</li>
				</ul>
			</div>
		</div>
		
		-->
		
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
      data.addColumn('number', 'Dogs');

      data.addRows([
        [12, 0],   [13, 10],  [14, 80],  [15, 17],  [16, 18],  [17, 9],
        [18, 11],  [19, 27],  [20, 33],  [21, 40],  [22, 32], [23, 35],
        [24, 30], [13, 40], [14, 42], [15, 47], [16, 44], [17, 48],
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
 
 
 

 
