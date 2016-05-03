#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDS 90

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
int8_t position = 0;
uint16_t delayed = 50;
int8_t direction = 1;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // Setup serial conn for 115200 baud
  
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  position += direction;
  Serial.println(position);
  Serial.println(direction);
  if(position >= LEDS && direction == 1) {
    direction = -1;
  }
  if(position <= 0 && direction == -1) {
    direction = 1;
  }
  setWurm(position);
  
  //whiteBullet(50,30);
  
}

void setWurm(uint8_t pos) {

  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
  }
  
  uint16_t i=0; 
  while(i<20) {
      uint32_t c = strip.Color(0,0,(float(i)/20)*255);
      strip.setPixelColor((pos-i)%LEDS, c);
      i += 1;
  }
  strip.show();
  delay(delayed);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t hslToRgb(uint16_t h, float s, float l) {
    float c = (l - abs(2 * l -1)) *s;
    uint16_t hPrime = h / 60;

    float x = c * (1 - abs(hPrime % 2 - 1));

    if (hPrime <= 1) {
        return strip.Color(c * 255, x * 255, 0);
    } else if (hPrime <= 2) {
        return strip.Color(x * 255, c * 255, 0);
    } else if (hPrime <= 3) {
        return strip.Color(0, c * 255, x * 255);
    } else if (hPrime <= 4) {
        return strip.Color(0, x * 255, c * 255);
    } else if (hPrime <= 5) {
        return strip.Color(x * 255, 0, c * 255);
    } else if (hPrime < 6) {
        return strip.Color(c * 255, 0, x * 255);
    } else {
        return strip.Color(0, 0, 0);
    }
}

void whiteBullet(uint8_t wait, int len) {
    uint8_t currPos = 0;

    for (uint8_t i = 0; i < strip.numPixels(); i++) {
        // override first color to be white
        for (uint8_t p = 0; p < len - 1; p++) {
            uint16_t step = 360 - (((float) p / len) * 360);
            strip.setPixelColor((i + p) % strip.numPixels(), hslToRgb(step, 1.0, 1.0));
        }

        strip.setPixelColor((i + len) % strip.numPixels(), strip.Color(255, 255, 255));
        strip.show();

        delay(wait);

    }

}

