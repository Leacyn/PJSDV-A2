/*-----------------------------------
  Logic definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/



using namespace std;


map<string, int> logic(map<string, int> IO){


  if (IO.count("bed_switch")>0){
    clog << "toggleled "<< IO["bed_switch"]<<endl;

    IO["bed_led"]=toggle("bed_led");

  }


  if (IO.count("lamp_motion")>0){
    IO["lamp_led"]=IO["lamp_motion"];
  }


  if (IO.count("column_smoke")>0){
    IO["column_buzzer"]=IO["column_smoke"];
  }


  if (IO.count("door_switch_binnen")>0, IO.count("door_switch_buiten")>0){
    IO["door_led"]=toggle("door_led");
  }

  if (IO.count("bed_pressure")>0){
    logSleep(IO["bed_pressure"]);
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
