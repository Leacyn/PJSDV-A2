#include <FastLED.h>
#include <Wire.h>

#define LED_PIN     D5
#define NUM_LEDS    1

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(D5, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
}
void loop() {
  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  Serial.print("Digital in: ");
  Serial.println(inputs & 0x0F);

  
  if ((inputs & 0x0F) == 15) {            // lamp aan als er beweging is
    leds[0] = CRGB::Gray;
    FastLED.show();
  }
  else if ((inputs & 0x0F) == 14) {       // lamp uit als er geen beweging is
    leds[0] = CRGB::Black;
    FastLED.show();
  }
}
