#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(90, PIN, NEO_GRB + NEO_KHZ800);


int val = 0;
int inc = 2;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200); // Setup serial conn for 115200 baud
}

void loop () {
    bars(6, val, strip.Color(0, 0, 255));
    val = (val + inc);

    if (val >= 15 || val <= 0) {
       inc = -inc;
    }
}

void bars(int numBars, int val, uint32_t color) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
  
    int len = strip.numPixels();
    int barSize = len / numBars;

    Serial.println(val);

    for (int i = 0; i < numBars; i++) {
        int min = (barSize - val) / 2;
        
        for (int j = min; j <= val + min; j++) {
            strip.setPixelColor(i * barSize + j, color);
        }
    }
  delay(50);
    strip.show();
}
