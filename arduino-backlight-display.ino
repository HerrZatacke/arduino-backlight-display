#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB);
uint16_t i, j;
byte mode;
byte color = 0;

char pattern[] = {
// pattern a 
  B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000, B10000001, B10000010, B10000100, B10001000, B10010000, B10100000, B11000000, B11000001, B11000010, B11000100, B11001000, B11010000, B11100000, B11100001, B11100010, B11100100, B11101000, B11110000, B11110001, B11110010, B11110100, B11111000, B11111001, B11111010, B11111100, B11111101, B11111110, B11111111,
// pattern -b
  B01111111, B10111111, B11011111, B11101111, B11110111, B11111011, B11111101, B11111110, B01111110, B10111110, B11011110, B11101110, B11110110, B11111010, B11111100, B01111100, B10111100, B11011100, B11101100, B11110100, B11111000, B01111000, B10111000, B11011000, B11101000, B11110000, B01110000, B10110000, B11010000, B11100000, B01100000, B10100000, B11000000, B01000000, B10000000, B00000000,
// pattern b
  B10000000, B01000000, B00100000, B00010000, B00001000, B00000100, B00000010, B00000001, B10000001, B01000001, B00100001, B00010001, B00001001, B00000101, B00000011, B10000011, B01000011, B00100011, B00010011, B00001011, B00000111, B10000111, B01000111, B00100111, B00010111, B00001111, B10001111, B01001111, B00101111, B00011111, B10011111, B01011111, B00111111, B10111111, B01111111, B11111111,
// pattern -a 
  B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111, B01111110, B01111101, B01111011, B01110111, B01101111, B01011111, B00111111, B00111110, B00111101, B00111011, B00110111, B00101111, B00011111, B00011110, B00011101, B00011011, B00010111, B00001111, B00001110, B00001101, B00001011, B00000111, B00000110, B00000101, B00000011, B00000010, B00000001, B00000000,
};

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(255);
}

void loop() {
  for (mode = 0; mode < 16; mode++) {
    rainbow(4);
  }

  for (mode = 0; mode < 255; mode++) {    
    flash(24);
  }
  
  for (mode = 0; mode < 8; mode++) {
    showPattern(16);
  }
}

void rainbow(uint8_t wait) {
  for(j = 0; j < 256; j++) {
    for(i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, Wheel(color + (i * 32)));
    }
    color = (color + 1) & 255;
    strip.show();
    delay(wait);
  }
}

void flash(uint8_t wait) {
  uint32_t currentColor = getNextColor();
  for(i=0; i<LED_COUNT; i++) {
    if (random(24) == 0) {
      strip.setPixelColor(i, currentColor);
    } else {
      strip.setPixelColor(i, 0);
    }
      
  }
  strip.show();
  delay(wait);
}


void showPattern(uint8_t wait) {
  for(j=0; j < sizeof(pattern); j++) {
    uint32_t currentColor = getNextColor();
    for(i=0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, bitRead(pattern[j], i) * currentColor);
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

uint32_t getNextColor() {
  color = (color + 1) & 255;
  return Wheel(color);
}
