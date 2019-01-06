std::map<std::string, int> logic(std::map<std::string, int> IO){
  

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
