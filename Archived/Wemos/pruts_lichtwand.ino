#include <Wire.h>
#include <FastLED.h>

#define LED_PIN     D5
#define NUM_LEDS    3
#define I2C_SDL    D1
#define I2C_SDA    D2

CRGB leds[NUM_LEDS];

void setup(void) {
  Wire.begin();
  Serial.begin(115200);
  pinMode(D0, INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(D5, OUTPUT);
}

void loop(void) {
  leds[0] = CRGB::White;                // alle leds aanzetten
  leds[1] = CRGB::White;
  leds[2] = CRGB::White;
  FastLED.show();


  //Set PCA9554 outputs (IO44-IO7)          //venster aan/uit zetten
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(0 << 4));
  Wire.endTransmission();
  Serial.print("Digital out: ");
  Serial.println(15 & 0x0F);

  //Config MAX11647
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();

  //Read analog 10bit inputs 0&1                   
  Wire.requestFrom(0x36, 4);                  // potmeter en ldr uitlezen
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  unsigned int anin1 = Wire.read() & 0x03;
  anin1 = anin1 << 8;
  anin1 = anin1 | Wire.read();
  Serial.print("analog in 0: ");
  Serial.println(anin0);
  Serial.println(anin1);
  delay(300);

}
