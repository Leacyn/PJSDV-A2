#include <Wire.h>



#define I2C_SDL    D1
#define I2C_SDA    D2

void setup(void) {
  Wire.begin();
  Serial.begin(115200);
  pinMode(D0, INPUT);
}

int state = 1;
int currentState = 0;
int previousState = 0;M
int outputs = -1;

void loop(void) {
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();

  //Read analog 10bit inputs 0&1
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  unsigned int anin1 = Wire.read() & 0x03;		// druksensor uitlezen
  anin1 = anin1 << 8;
  anin1 = anin1 | Wire.read();
  Serial.print("analog in 0: ");
  Serial.println(anin0);

  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 4);
  unsigned int answer = Wire.read();

  currentState = answer % 2;  

  if (currentState != previousState) 	
  { if (currentState == 1)
    { state = state * -1;
    }
  }
  previousState = currentState;			// lamp uit
  if (state == 1) {
    outputs = 0;
  }
  else if (state == -1) {				// lamp aan
    outputs = 1;
  }
  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board).
  //IO0-IO3 as input, IO4-IO7 as output.
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  //Set PCA9554 outputs (IO44-IO7)		// lamp aan/uit
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(outputs << 4));
  Wire.endTransmission();
}
