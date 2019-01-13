#include <Servo.h>
#include <Wire.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(D5);  // attaches the servo on pin 9 to the servo object
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  myservo.write(82);                              // deur normaal gesproken dicht
  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38);                   // kijken of knop wordt ingedrukt
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  Serial.print("Digital in: ");
  Serial.println(inputs & 0x0F);

  if ((inputs & 0x0F) == 13) {                    
    for (pos = 82; pos >= -30; pos -= 1) {        // deur openen als knop aan de buitenkant wordt ingedrukt
      // in steps of 1 degree
      myservo.write(pos);                        
      delay(10);
    }
    delay(5000);
    for (pos = -30; pos <= 82; pos += 1) {        // deur sluiten na 5s
      // in steps of 1 degree
      myservo.write(pos);
      delay(10);
    }
  }
}
