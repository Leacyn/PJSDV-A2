<?php
$connection = mysqli_connect('localhost', 'editor', '100%Domotics','domotics'); //('localhost', 'editor', '100%Domotics','domotics');
if (!$connection){
    die("Database Connection Failed" . mysqli_error($connection));
}
$select_db = mysqli_select_db($connection, 'domotics');
if (!$select_db){
    die("Database Selection Failed" . mysqli_error($connection));
}
?>