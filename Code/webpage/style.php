<?php
header("Content-type: text/css"); //this page contains the style used in index.php, login.php and admin.php.
?>
.object{ width: 30%;float: left; margin: 0 5% 0 5%;}
.alert{ width: 40%; float: left; margin: 0 3% 0 3%; }

.pop-back{
	position: fixed; 
	top: 0; 
	height: 100%; 
	width: 100%;
	margin: 0; 
	background-color: rgba(0, 0, 0, 0.2); 
	z-index: 1;
	visibility: hidden;
}

.pop-up{
	position: fixed; 
	top: 250px; 
	height: 350px; 
	width: 40%;
	margin-left: 30%; 
	background-color: white; 
	box-shadow: 0 0px 8px 0 rgba(0, 0, 0, 0.2); 
	z-index: 1;
}

.pop-header{
	width: 100%;
	top: 0;
	height: 75px;
	background-color: red;
	text-align: center;
}

.pop-header h1{
color: white;
line-height: 65px;
}

form{max-height: 100%;}
body {
	margin: 0; 
	background-color: white;
	font-family: Arial, Helvetica, sans-serif;
}

.left{
Width: 33.3%;
height: 100%;
float: left;
}

.lights{
width: 100%;
height: 50%;
box-shadow: 1px 1px 20px -5px lightgrey;
padding: 10px;
}

.lights h1{
padding: 55px 0 0 5px;
}
.alerts{
Width: 100%;
height: 50%;
box-shadow: 1px 1px 20px -5px lightgrey;
padding: 10px;
 
}
.center{
Width: 33.3%;
height: 100%;
float: left;
box-shadow: 1px 1px 20px -5px lightgrey;
padding: 100px 10px 10px 10px;
}
	
.right{
Width: 33.3%;
height: 100%;
float: left;
box-shadow: 1px 1px 20px -5px lightgrey;
padding: 10px;
}

.right h1{
padding: 55px 0 0 5px;
}

h1{
margin: 0;
padding: 5 0 0 5px;

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
	width: 66%; 
	text-align: left; 
	float: left;
	
}

.container-33{
	width: 33.3%; 
	text-align: left; 
	float: left;
}

.panel{
	padding: 75px 50px 50px 50px; 
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

.button2 {
	background-color: red;
	border: none;
	color: white;
	padding: 15px;
	text-align: center;
	text-decoration: none;
	display: block;
	font-size: 16px;
	margin-bottom: 5px;
	margin: 48px 0 0 0;
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

.closeButton {
	position: absolute;
	bottom: 0;
	right: 0;
	background-color: darkgrey;
	border: none;
	color: white;
	padding: 15px;
	text-align: center;
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

#slider {
  -webkit-appearance: none;
  width: 113px;
  height: 25px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
  margin: 0 0 10px 0px;
  border-radius: 50px;
}

#slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  background: #0078FF;
  border-radius: 50px;
  cursor: pointer;
}

#slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #0078FF;
  cursor: pointer;
}

#bar{
margin-left: 120px;
margin-top: 10px;
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
