/*-----------------------------------
  Logic definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/



using namespace std;


map<string, int> /*Domotica::*/logic(map<string, int> IO){/*execute logic on IO map (name, value)*/

  int currentTime = getCurrentTime();/*Get current time in seconds since 00:00*/

  if ((currentTime > 22*60*60) && (currentTime < (22*60*60)+30)){ /*If current between 22:00 and 22:00:30 turn light off*/
    IO["bed_led"]=OFF;
    IO["lamp_led"]=OFF;
    IO["wall_window"]=ON;
    IO["wall_led"]=OFF;
    IO["door_led"]=OFF;
  }
  if ((currentTime > 7*60*60) && (currentTime < (7*60*60)+30)){/*If current between 7:00 and 7:00:30 turn light on and open curtains*/
    IO["bed_led"]=ON;
    IO["wall_window"]=OFF;
  }


  if (IO.count("chair_pressure")>0){ /*Check if anyone is sitting and set the time for when said person started sitting*/
    if ((IO["chair_pressure"]>0)&&(!sitting)){
      logSwitch("chair", "sitting");
      startedSitting = time(0);
      sitting = 1;
    } else if (IO["chair_pressure"]<=0){
      logSwitch("chair", "not sitting");
      sitting = 0;
      startedSitting = 0;
      IO["chair_vibration"]=OFF;
    }
  }
  if (sitting && ((time(0) - startedSitting) > (20 * 60))){/*If anyone is sitting for more than 15 min chair starts vibrating*/
    IO["chair_vibration"]=ON;
  }


  if (IO.count("bed_switch")>0){/*Toggle led on switch press*/
    IO["bed_led"]=toggle("bed_led");
  }

  if (IO.count("lamp_motion")>0){/*Set led when motion is detected*/
    if (IO["lamp_motion"]){
      timeOn = time(0);
    }
    if (((time(0) - timeOn) < (5 * 60)) || !timeOn){
      IO["lamp_led"] = ON;
    }else {
      IO["lamp_led"] = OFF;
    }
  }

  if (IO.count("column_smoke")>0){/*Enable buzzer when smoke is detected*/
    IO["column_buzzer"]=IO["column_smoke"];
  }

  if (IO.count("door_switch_buiten")>0){ /*Open door when switch (outside) is pressed*/
    IO["door_servo"]=toggle("door_servo");
    if (IO["door_servo"]){
      logSwitch("door", "open");
    } else {
      logSwitch("door", "closed");
    }
    IO["door_led"]=OFF;
  }

  if (IO.count("door_switch_binnen")>0){/*Toggle led on switch press*/
    IO["door_led"]=toggle("door_led");
  }

  if (IO.count("bed_pressure")>0){/*Log sleep pattern*/
    logSleep(IO["bed_pressure"]);
  }

  if (IO.count("fridge_door_switch")>0){/*Check if fridge door is open*/
    if (!IO["fridge_door_switch"] && !fridgeOpen){
      IO["fridge_cooling"] = 0;
      logSwitch("fridge", "open");
      fridgeOpen = 1;
      fridgeOpeningTime = time(0);
    } else if (IO["fridge_door_switch"]){
      IO["fridge_cooling"] = 1;
      logSwitch("fridge", "closed");
      fridgeOpen = 0;
      tooLong = 0;
      IO["column_buzzer"]=OFF;
    }
  }


  if (!tooLong && fridgeOpen && ((time(0) - fridgeOpeningTime) > (5 ))){/*If fridge door is open for more than 5 minutes start buzzer*/
    tooLong=1;
    //clog << "open for too long \n";
    IO["column_buzzer"]=ON;
  }
/* volgende statements:

B = Bedschakelaar	  actuatoren/outputs
D = deurswitch	       B' = bedLED
I = interface	         D' = DeurLED
L = ldr	               DS = DeurServo
M = beweginssensor	   M' = Venster
R = rookmelder      	 S' = SchemerLed
S = druksensor stoel	 Z' = Zuilzoemer
Z = zuilswitch

Actief	     ALS
BedLed	    B!DI!L!M!R!Z
DeurLed	    !BDI!L!M!R!Z
DeurServeo	!B!DI!L!M!R!Z
Venster	    !B!DIL!M!R!Z
SchemerLED	!B!DI!LM!R!Z
Zoemer    	!B!DI!L!MR!Z
alle LEDS	  !B!DI!L!M!RZ

*/
  return IO;
}
