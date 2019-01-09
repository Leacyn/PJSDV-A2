<?php  
 $messageColor = '';
 $message = '';  
 $error = '';  
 if(isset($_POST["submit"]))  
 {  
      if(empty($_POST["A"]))  
      {  
		   $error = "<label class='error'>Please fill in all variables</label>";  
      }  
      else if(empty($_POST["B"]))  
      {  
		   $error = "<label class='error'>Please fill in all variables</label>";  
      }  
      else if(empty($_POST["C"]))  
      {  
		   $error = "<label class='error'>Please fill in all variables</label>";  
      }  
      else  
      {  
           if(file_exists('output.json'))  
           {  
                $current_data = file_get_contents('output.json');  
                $array_data = json_decode($current_data, true);  
                $extra = array(  
                     'A'               =>     $_POST['A'],  
                     'B'          =>     $_POST["B"],  
                     'C'     =>     $_POST["C"]  
                );  
                $array_data[] = $extra;  
                $final_data = json_encode($array_data);  
                if(file_put_contents('output.json', $final_data))  
                {  
                     $message = "<label class='success'>File Appended Successfully</p>";  
                }  
           }  
           else  
           {  
                $error = 'JSON File not exits';  
           }  
      }  
 }  
 ?>  
 
<!DOCTYPE html>  
 <html>  
      <head>  
           <title>Dashboard</title> 

			<style>
			body { margin: 0; background-color: lightgrey;}
			h3   {color: black;}
			label{color: darkblue;}
			
			.container{margin-left: 37.5%; width: 25%; text-align: left;}
			.input {width: 100%; font-size: 24px;}
			.button {width: 50%; margin-left: 25%; margin-top: 5px; font-size: 24px;}
			.error { color: red; font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;}
			.success { color: green font-weight: bold; line-height: 50px; margin-left: 15px; height: 50px; width: 100%;} 
			
			#messages{ position: fixed; bottom: 0; height: 50px; width: 100%; background-color: green; visibility: hidden;}
			#errors{ position: fixed; bottom: 0; height: 50px; width: 100%; background-color: red; visibility: hidden;}
			</style>
			
      </head> 
	  
      <body>   
           <div class="container">  
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
      </body> 
	  
	  <div class="messages">
			<?php  
                if(isset($message))  
                {  
					 
				echo $message;  
                }  
            ?> 
	
	  </div>
	  <div class="errors">
			<?php   
				if(isset($error))  
				{  
				echo $error;  
				}  
            ?>    
	  </div>

<script type="text/javascript">
function jsFunction(){
	document.getElementById('messages').style.visibility = 'visible';
};
</script>	
 </html>  
 
 

 