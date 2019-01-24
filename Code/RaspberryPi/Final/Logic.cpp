/*-----------------------------------
  Logic definition
  version: 1.0
  contributors:
  Stijn van Es 17018498
  ----------------------------------*/

using namespace std;

/*execute logic on IO map (name, value)*/
map<string, int> Domotica::logic(map<string, int> IO){

  int currentTime = getCurrentTime();/*Get current time in seconds since 00:00*/


/*If current between 22:00 and 22:00:30 turn light off*/
  if ((currentTime > 22*60*60) && (currentTime < (22*60*60)+30)){
    IO["bed_led"]=OFF;
    IO["lamp_led"]=OFF;
    IO["wall_window"]=ON;
    IO["wall_led"]=OFF;
    IO["door_led"]=OFF;
  }

/*If current between 7:00 and 7:00:30 turn light on and open curtains*/
  if ((currentTime > 7*60*60) && (currentTime < (7*60*60)+30)){
    IO["bed_led"]=ON;
    IO["wall_window"]=OFF;
  }

/*Check if someone sits in the chair, starts a wait timer*/
  if (IO.count("chair_pressure")>0){
    if ((IO["chair_pressure"]>0)&&(!sitting)){
      logSwitch("chair", "sitting");
      startedSitting = time(0);
      sitting = 1;
    } else if (IO["chair_pressure"]<=0){
      logSwitch("chair", "not sitting");
      sitting = 0;
      startedSitting = 0;
      IO["chair_vibration"]= OFF;
    }
  }

/*If someone sits for more than 15 min in the chair it starts vibrating*/
  if (sitting && ((time(0) - startedSitting) > (20 ))){
    IO["chair_vibration"]=2;
  }

/*Toggle bed led on switch press*/
  if (IO.count("bed_switch")>0){
    IO["bed_led"]=toggle("bed_led");
  }

/*Toggle chair led on switch press*/
  if (IO.count("chair_switch")>0){
    IO["chair_led"]=toggle("chair_led");
  }

/*turn room lamp on when motion is detected*/
  if (IO.count("lamp_motion")>0){
    if (IO["lamp_motion"]){
      timeOn = time(0);
    }
    if (((time(0) - timeOn) < (5 * 60)) || !timeOn){
      IO["lamp_led"] = ON;
    }else {
      IO["lamp_led"] = OFF;
    }
  }

/*Enable buzzer when smoke is detected*/
  if (IO.count("column_smoke")>0){
    if (IO["column_smoke"] == 4||IO["column_smoke"] == 3) {
      IO["column_buzzer"]=OFF;
      // trillen uit
      IO["chair_vibration"]=0;
    } else {
      IO["column_buzzer"]=ON;
      // trillen aan
      IO["chair_vibration"]=2;
    }
  }

/*Open door when switch (outside) is pressed*/
  if (IO.count("door_switch_buiten")>0){
    IO["door_servo"]=toggle("door_servo");
    if (IO["door_servo"]){
      logSwitch("door", "open");
    } else {
      logSwitch("door", "closed");
    }
    IO["door_led"]=OFF;
  }

/*Toggle door led on switch press*/
  if (IO.count("door_switch_binnen")>0){
    IO["door_led"]=toggle("door_led");
  }

/*Log sleep pattern*/
  if (IO.count("bed_pressure")>0){
    logSleep(IO["bed_pressure"]);
    // wand aan
    IO["wall_window"]=ON;
  }
  
  else{
  	IO["wall_window"]=OFF;
  }

/*Check if fridge door is open if so, set timer, log status*/
  if (IO.count("fridge_door_switch")>0){
    if (!IO["fridge_door_switch"] && !fridgeOpen){
      IO["fridge_cooling"] = 0;
      logSwitch("fridge", "open");
      fridgeOpen = 1;
      fridgeOpeningTime = time(0);
      
      // deur open als koelkast open is
      IO["door_servo"]=ON;
      
      
    } else if (IO["fridge_door_switch"]){
      IO["fridge_cooling"] = 1;
      logSwitch("fridge", "closed");
      fridgeOpen = 0;
      tooLong = 0;
      IO["column_led"]=OFF;
      
      //deur dicht
      IO["door_servo"]=OFF;
    }
    // state deur doorgeven
    if (IO["door_servo"]){
      logSwitch("door", "open");
    } else {
      logSwitch("door", "closed");
    }
  }

/*If fridge door is open for more than 5 minutes start buzzer*/
  if (!tooLong && fridgeOpen && ((time(0) - fridgeOpeningTime) > (5 ))){
    tooLong=1;
    IO["column_led"]=ON;
  }

/*If LDR output is too high than close curtains. If LDR output is too low than power led*/
  if (IO.count("wall_LDR")>0){
    if (flagLDRwindow){
      if (IO["wall_LDR"] < 8){
        flagLDRwindow = 0;
        IO["wall_window"]=OFF;
      }
    } else if (IO["wall_LDR"] >= 8){
        IO["wall_window"]=ON;
        flagLDRwindow = 1;
    }
    if (flagLDRled){
      if (IO["wall_LDR"] > 3){
        flagLDRled = 0;
        IO["wall_led"]=OFF;
      }
    } else if (IO["wall_LDR"] <= 3){
        IO["wall_led"]=7;
        flagLDRled = 1;
    }
  }

/*Set light intensity of wall led strip based on dimmer*/
  if (IO.count("wall_dimmer")>0 && IO["wall_dimmer"]!=1){
    IO["wall_led"] = IO["wall_dimmer"];
  }
  


  return IO;
}
