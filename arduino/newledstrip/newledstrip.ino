#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 90
#define NUMBYTES NUMPIXELS*3

#define IA_RED 29
#define IA_GREEN 66
#define IA_BLUE 138

#define OFFSET_BLUE   40
#define OFFSET_RED    (OFFSET_BLUE * IA_RED   / IA_BLUE)
#define OFFSET_GREEN  (OFFSET_BLUE * IA_GREEN / IA_BLUE)

// Moet 2**n - 1 zijn
#define INTERVAL 255

#define CORRECTEDINTERVAL (PI * 2 / (INTERVAL+1))

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t pixels[NUMBYTES];
uint8_t sine[(INTERVAL + 1)*3];
boolean local_animate = false;
uint8_t counter = 0;

void setup() {
  for (int i = 0; i < INTERVAL + 1; ++i) {
    sine[i*3]   = IA_RED   - OFFSET_RED   * cos(i * CORRECTEDINTERVAL);
    sine[i*3+1] = IA_GREEN - OFFSET_GREEN * cos(i * CORRECTEDINTERVAL);
    sine[i*3+2] = IA_BLUE  - OFFSET_BLUE  * cos(i * CORRECTEDINTERVAL);
  }
  Serial.begin(115200);
  Serial.setTimeout(50);
  strip.begin();
  strip.show();
}

void loop() {
  Serial.write(counter);
  if(Serial.readBytes(pixels, NUMBYTES) == NUMBYTES) {
    local_animate = false;
    for (int i = 0; i < NUMPIXELS; ++i) {
      strip.setPixelColor(i, strip.Color(pixels[i*3], pixels[i*3+1], pixels[i*3+2]));
    }
  } else if (local_animate) {
    counter = (counter + 1) & INTERVAL;
    for (int i = 0; i < NUMPIXELS; ++i) {
      int j = ((i+counter) & INTERVAL) * 3;
      strip.setPixelColor(i, strip.Color(sine[j], sine[j+1], sine[j+2]));
    }
  } else {
    local_animate = true;
    for (int i = 0; i < NUMPIXELS; ++i) {
      uint8_t& r = pixels[i*3];
      uint8_t& g = pixels[i*3+1];
      uint8_t& b = pixels[i*3+2];
      int j = ((i+counter) & INTERVAL) * 3;
      uint8_t& rn = sine[j];
      uint8_t& gn = sine[j+1];
      uint8_t& bn = sine[j+2];

      if (r != rn) {
        r += ((rn - r) >> 8) | 1;
        local_animate = false;
      }
      if (g != gn) {
        g += ((gn - g) >> 8) | 1;
        local_animate = false;
      }
      if (b != bn) {
        b += ((bn - b) >> 8) | 1;
        local_animate = false;
      }
      
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
  }
  strip.show();
}
