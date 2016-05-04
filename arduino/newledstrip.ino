#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 90
#define NUMBYTES NUMPIXELS*3

#define IA_RED 29
#define IA_GREEN 66
#define IA_BLUE 138

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t pixels[NUMPIXELS*3];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  strip.begin();
  strip.show();
}

void loop() {
  Serial.write(255);
  if(Serial.readBytes(pixels, NUMBYTES) == NUMBYTES) {
    for (int i = 0; i < NUMPIXELS; ++i) {
      strip.setPixelColor(i, strip.Color(pixels[i*3], pixels[i*3+1], pixels[i*3+2]));
    }
  } else {
    for (int i = 0; i < NUMPIXELS; ++i) {
      int8_t r = pixels[i*3];
      int8_t g = pixels[i*3+1];
      int8_t b = pixels[i*3+2];

      if (r != IA_RED)
        r = pixels[i*3]   = r + ((IA_RED - r) >> 8) | 1;
      if (g != IA_GREEN)
        g = pixels[i*3+1] = g + ((IA_GREEN - g) >> 8) | 1;
      if (b != IA_BLUE)
        b = pixels[i*3+2] = b + ((IA_BLUE - b) >> 8) | 1;
      
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
  }
  strip.show();
}
