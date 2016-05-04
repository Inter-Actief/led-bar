#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 90
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t pixels[NUMPIXELS*3];

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
}

void loop() {
  Serial.write(255);
  Serial.readBytes(pixels, NUMPIXELS*3);
  for (int i = 0; i < NUMPIXELS; ++i) {
    strip.setPixelColor(i, strip.Color(pixels[i*3], pixels[i*3+1], pixels[i*3+2]));
  }
  strip.show();
}
