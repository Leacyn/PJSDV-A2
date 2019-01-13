<?php
header("Content-type: text/css");

$on = '#00ff00';
$off = 'red';
$inactive = '#00ff00';

$L1 = $inactive; $L2 = $inactive; $L3 = $inactive; $L4 = $inactive; $L5 = $inactive; $L6 = $inactive; $L7 = $inactive; $L8 = $inactive; $L9 = $inactive; $L10 = $inactive;
$L11 = $inactive; $L12 = $inactive; $L13 = $inactive; $L14 = $inactive; $L15 = $inactive; $L16 = $inactive; $L17 = $inactive; $L18 = $inactive; $L19 = $inactive; $L20 = $inactive;
$L21 = $inactive; $L22 = $inactive; $L23 = $inactive; $L24 = $inactive; $L25 = $inactive;


?>

#Cl1{background:<?=$L1?>;}#Cl2{background:<?=$L2?>;}#Cl3{background:<?=$L3?>;}#Cl4{background:<?=$L4?>;}#Cl5{background:<?=$L5?>;}
#Cl6{background:<?=$L6?>;}#Cl7{background:<?=$L7?>;}#Cl8{background:<?=$L8?>;}#Cl9{background:<?=$L9?>;}#Cl10{background:<?=$L10?>;}
#Cl11{background:<?=$L11?>;}#Cl12{background:<?=$L12?>;}#Cl13{background:<?=$L13?>;}#Cl14{background:<?=$L14?>;}#Cl15{background:<?=$L15?>;}
#Cl16{background:<?=$L16?>;}#Cl17{background:<?=$L17?>;}#Cl18{background:<?=$L18?>;}#Cl19{background:<?=$L19?>;}#Cl20{background:<?=$L20?>;}
#Cl21{background:<?=$L21?>;}#Cl22{background:<?=$L22?>;}#Cl23{background:<?=$L23?>;}#Cl24{background:<?=$L24?>;}#Cl25{background:<?=$L25?>;}

.object{width: 200px; float: left; min-height: 500px; margin-top: 50px;}
.object h1{text-align: center;}
.object form{margin-left: 20%;}


body {
	margin: 0; 
	background-color: white;
	font-family: Arial, Helvetica, sans-serif;
}
			
h3{
	color: black; 
	line-height: 27px; 
	margin-bottom: 5px;
	font-size: 15px;
}

label{
	color: darkblue;
}

p{ 
	margin-left: 15px; 
	color: black; 
	font-weight: bold;
}

.container{
	width: 100%; 
	text-align: left; 
	float: left;
}

.panel{
	padding: 75px 50px 50px 50px; 
	width: 66%; 
	position: absolute;
}

.graph{
	padding: 75px 50px 0 0; 
	margin-left: 66%; 
	width: 33%; 
	position: absolute;
}

.input {
	width: 50%; 
	font-size: 24px; 
	margin-bottom: 3px;
}
label {
	margin-left: 25%;
}

.error {
	color: red; 
	font-weight: bold; 
	line-height: 50px; 
	margin-left: 15px; 
	height: 50px; 
	width: 100%;
}

.success { 
	color: green; 
	font-weight: bold; 
	line-height: 50px; 
	margin-left: 15px; 
	height: 50px; 
	width: 100%;
} 

.user {
	float: left;
}

#header{
	position: fixed; 
	top: 0; 
	height: 50px; 
	width: 100%; 
	background-color: lightgrey; 
	box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2); 
	float: left;

}
#messages{
	position: fixed;
	bottom: 0;
	height: 50px;
	width: 100%;
	background-color: lightgrey;
}
.button {
	background-color: grey;
	border: none;
	color: white;
	padding: 15px;
	text-align: center;
	text-decoration: none;
	display: block;
	font-size: 16px;
	margin-bottom: 5px;
}	
.exit-button {
	background-color: grey;
	border: none;
	color: white;
	width: 75px;
	float: right;
	padding: 15px;
	text-align: center;
	text-decoration: none;
	display: block;
	font-size: 16px;
}		

.login{
	background-color: lightgrey;
	border: none;
	color: white;
	width: 75px;
	float: right;
	padding: 15px;
	text-align: center;
	text-decoration: none;
	display: block;
	font-size: 16px;
}
.bulb{
	border-radius: 50%;
	height: 25px;
	width: 25px;
	margin: 0 10px 0 0;
	float: left;
}

.bulb2{
	background-color: #00ff00;
	border-radius: 50%;
	height: 25px;
	width: 25px;
	margin: 0 10px 0 0;
	float: left;
}

.statusbar{
	float: right;
	margin-top: 13px;
}
.statusbar div{
	margin: 0 50px 0 0;
}
.statusbar i{
	margin-left: 30px;
	line-height: 25px;
}
.message{
	height: auto; 
	font-weight: bold; 
	color: #0078FF;
}
.box{
	height: 25px;
	margin-bottom: 8px;
}

.button-group{
float: left;
margin-left: 15px;
}

* {
	box-sizing: border-box;
}
ul {
	list-style-type: none;
}

.month {
  padding: 5px 25px;
  width: 100%;
  background: #0078FF;
  text-align: center;
}

.month ul {
  margin: 0;
  padding: 0;
}

.month ul li {
  color: white;
  font-size: 20px;
  text-transform: uppercase;
  letter-spacing: 3px;
}

.month .prev {
  float: left;
  padding-top: 10px;
}

.month .next {
  float: right;
  padding-top: 10px;
}

.weekdays {
  margin: 0;
  padding: 10px 0;
  background-color: #ddd;
}

.weekdays li {
  display: inline-block;
  width: 13.6%;
  color: #666;
  text-align: center;
}

.days {
  padding: 10px 0;
  background: #eee;
  margin: 0;
}

.days li {
  list-style-type: none;
  display: inline-block;
  width: 13.6%;
  text-align: center;
  margin-bottom: 5px;
  font-size:12px;
  color: #777;
}

.days li .active {
  padding: 5px;
  background: #0078FF;
  color: white !important
}

/* Add media queries for smaller screens */
@media screen and (max-width:720px) {
  .weekdays li, .days li {width: 13.1%;}
}

@media screen and (max-width: 420px) {
  .weekdays li, .days li {width: 12.5%;}
  .days li .active {padding: 2px;}
}

@media screen and (max-width: 290px) {
  .weekdays li, .days li {width: 12.2%;}
}
