<!DOCTYPE html>
<html>
<head>
<style>
body {width: 50%; margin-left: 25%;}
body img {margin-left: 25%; width: 50%;}
input {margin-left: 25%; width: 50%; font-size: 2.5vw; margin: 1% 0 1% 25%;}
form {padding: 5% 0 5% 0; margin-top: 100px; background-color: #F5F5F5; box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2); float: left;}
#button{background-color: grey; border: none; color: white; font-size: 2.5vw; padding: 5px 5px; text-align: center; text-decoration: none; display: block;}
.messages{position: relative; margin-left: 25%; width: 50%; height: 30px; font-size: 1.5vw; margin: 1% 0 1% 25%; background-color: #F5F5F5; font-family: arial; color: red; font-weight: bold;}	
</style>
</head>

<body>
	<form method="post">
		
		<img src="logo.png"></img>
		<input type="text" name="user_id" id="user_id" placeholder="Username"></input><br>
            
		<input type="password" name="user_pass" id="user_pass" placeholder="Password"></input><br>
            	
		<input type="submit" name="login" value="Log in" id="button"/>
		
		<div class="messages">
		<?php

			if(array_key_exists('login',$_POST)){
			   login();
			}

			function login()
			{
			require('db_connect.php');
				
			// Assigning POST values to variables. 
			$username = $_POST['user_id'];
			$password = $_POST['user_pass'];

			// CHECK FOR THE RECORD FROM TABLE
			$query = "SELECT * FROM `_User` WHERE username='$username' and Password='$password'"; //$query = "SELECT * FROM `_User` WHERE username='$username' and Password='$password'";
			 
			$result = mysqli_query($connection, $query) or die(mysqli_error($connection));
			$count = mysqli_num_rows($result);

			if ($count == 1){

			//echo "Login Credentials verified";
			 header('Location: admin.php');

			}else{
			 echo "Invalid Login Credentials";
			}
			}
		?>
		</div>
	</form>
</body>
