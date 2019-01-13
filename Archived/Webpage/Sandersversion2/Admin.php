<?php  
$message = '';  
$user = 'Admin';

$servername = "localhost"; //$servername = "localhost"; 
$username = "root"; //$username = "editor";
$password = "1234"; //$password = "100%Domotics";
$dbname = "pjsysdev"; //$password = "100%Domotics";

$value = '';
$state = '';

$id = '';
			
			function write(){
				
                 // Create connection
                $conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
                // Check connection
                if ($conn->connect_error) {
                        die("Connection failed: " . $conn->connect_error);
                } 
				
				$value = $GLOBALS['$state'];
				$value2 = $GLOBALS['$id'];
                $sql = "UPDATE User_ SET password=$value WHERE id=$value2"; //$sql = "UPDATE _User SET stateVal=$value WHERE id=$value2";

                if ($conn->query($sql) === TRUE) {
                } else {
                       echo "Error updating record: " . $conn->error;
                }
				
				echo 'State changed to $value'
                $conn->close();

                }
 ?>  
 
<!DOCTYPE html>  
 <html>  
      <head>  
           <title>Dashboard</title> 

			<style>
			body { margin: 0; background-color: white;  font-family: Arial, Helvetica, sans-serif;}
			h3   {margin-left: 15px; color: black;}
			label{color: darkblue;}
			p { margin-left: 15px; color: black; font-weight: bold;}
			
			.container{padding: 100px 50px 50px 50px; width: 100%; text-align: left;}
			.input {width: 50%; font-size: 24px; margin-bottom: 5px;}
			label {margin-left: 25%;}
			.error { color: red; font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;}
			.success { color: green; font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;} 
			.user {float: left;}
			
			#header{ position: fixed; top: 0; height: 50px; width: 100%; background-color: lightgrey; box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2); float: left;}
			#messages{ position: fixed; bottom: 0; height: 50px; width: 100%; background-color: lightgrey;}
			.button {background-color: grey; border: none; color: white; width: 75px; padding: 15px; text-align: center; text-decoration: none; display: block; font-size: 16px; margin-bottom: 5px;}	
			.exit-button {background-color: grey; border: none; color: white; width: 75px; float: right; padding: 15px; text-align: center; text-decoration: none; display: block; font-size: 16px;}		
			</style>
			
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
					<input type="submit" name="toggle1" value="Toggle1" class="button"/>
			
			<?php
			
			if(array_key_exists('toggle1',$_POST)){
			toggle1();
			}

			function toggle1()
			{
				$GLOBALS['$id'] = 1;
				read();
				
				if(id == 1){
				$GLOBALS['$state'] = 2;
				}
				else{
				$GLOBALS['$state'] = 1;	
				}
				write();
			}
			?>
				<input type="submit" name="toggle2" value="Toggle2" class="button"/>
			
			<?php
			
			if(array_key_exists('toggle2',$_POST)){
			   toggle2();
			}
			
			function toggle2(){	
				$GLOBALS['$id'] = 2;
				read();
				
				if(id == 1){
				$GLOBALS['$state'] = 2;
				}
				else{
				$GLOBALS['$state'] = 1;	
				}
				write();
			}					
			?>
							<input type="submit" name="toggle3" value="Toggle3" class="button"/>
			
			<?php
			
			if(array_key_exists('toggle3',$_POST)){
			   toggle3();
			}
			
			function toggle3(){	
				$GLOBALS['$id'] = 3;
				read();
				
				if(id == 1){
				$GLOBALS['$state'] = 2;
				}
				else{
				$GLOBALS['$state'] = 1;	
				}
				write();
			}
			?>				
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

<script type="text/javascript">
</script>	
 </html>  
 
 <?php
 				function read(){
				// Create connection
				$conn = new mysqli($GLOBALS['servername'], $GLOBALS['username'], $GLOBALS['password'], $GLOBALS['dbname']);
				// Check connection
				if ($conn->connect_error) {
					die("Connection failed: " . $conn->connect_error);
				} 
				
				$value = $GLOBALS['$id'];
				$sql = "SELECT password FROM User_ WHERE id=$value"; //$sql = "SELECT stateVal FROM _User WHERE id=$value";
				$result = $conn->query($sql);
				
				if ($result->num_rows > 0) {
					// output data of each row
					while($row = $result->fetch_assoc()) {
						$GLOBALS['$state'] == "$row[password];
					}
				} else {
					echo "0 results";
				}
				}
 ?>
 
 

 
