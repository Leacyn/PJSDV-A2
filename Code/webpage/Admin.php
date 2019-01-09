<?php  
$message = '';  
$user = 'Admin';


			/*function check0()
			{
			require('db_connect.php');
				
			// Assigning POST values to variables.
			$username = $_POST['user_id'];
			$password = $_POST['user_pass'];
			

			// CHECK FOR THE RECORD FROM TABLE
			$query = "SELECT * FROM `user_` WHERE username='$username' and Password='$password'";
			 
			$result = mysqli_query($connection, $query) or die(mysqli_error($connection));
			$count = mysqli_num_rows($result);

			if ($count == 1){

			//echo "Login Credentials verified";
			 header('Location: admin.php');

			}else{
			 echo "Invalid Login Credentials";
			}
			}
			
			if(array_key_exists('toggle1',$_POST)){
			   toggle1();
			}
			
			function toggle1()
			{
			$servername = "localhost";
			$username = "root";
			$password = "1234";
			$dbname = "pjsysdev";
			
				
			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
			} 
			
			if($value1 == '1'){
			 $value1 = '0';
			 
			}
			else{
			 $value1 = '1';	 
			}
		
			$sql = "UPDATE user_ SET password='$value1' WHERE id=1";
			
			if ($conn->query($sql) === TRUE) {
			echo "state changed to $value1";
			} else {
			echo "Error updating record: " . $conn->error;
			}

			$conn->close();
			
			}
			
			if(array_key_exists('toggle2',$_POST)){
			   toggle2();
			}
			
			function toggle2()
			{

			
			}
			
			if(array_key_exists('check3',$_POST)){
			   toggle3();
			}
			
			function toggle3()
			{
			echo "hey1";
			}
			*/
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
					<input type="submit" name="toggle1" value="Set A to 0" class="button"/>
			
			<?php
			   if(array_key_exists('toggle1',$_POST)){
			   toggle1();
			}
			
			function toggle1()
			{
			$servername = "localhost";
			$username = "monitor";
			$password = "100%Domotica";
			$dbname = "domotics";
			
				
			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
			} 
			
			$sql = "UPDATE Sensor SET stateVal='0' WHERE id=1";
			
			if ($conn->query($sql) === TRUE) {
			} else {
			echo "Error updating record: " . $conn->error;
			}

			$conn->close();
			
			}
			?>
					<input type="submit" name="toggle2" value="Set A to 1" class="button"/>
			
			<?php
			   if(array_key_exists('toggle1',$_POST)){
			   toggle1();
			}
			
			function toggle2()
			{
			$servername = "localhost";
			$username = "monitor";
			$password = "100%Domotica";
			$dbname = "domotics";
			
				
			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
			} 
			
			$$sql = "UPDATE Sensor SET stateVal='1' WHERE id=1";
			
			if ($conn->query($sql) === TRUE) {
			} else {
			echo "Error updating record: " . $conn->error;
			}

			$conn->close();
			
			}
			?>
					<!--<input type="submit" name="toggle3" value="toggle3" class="button"/>-->
					</form>
					</div>
			<div id="messages">
			</div>
				
           <!--<div class="container">  
              <h3>Dashboard</h3>	
                <form method="post">  
                      
                     <label>A</label> 
                     <input type="text" name="A" class="input"/> 
					 <br>
                     <label>B</label>					 
                     <input type="text" name="B" class="input"/> 
					 <br>
                     <label>C</label> 					 
                     <input type="text" name="C" class="input"/> 
					 <br>
                     <input type="submit" name="submit" value="Send" class="button"/>
					 <br>
                </form>  
           </div>
		   <div class="container">
		   
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
 
 

 