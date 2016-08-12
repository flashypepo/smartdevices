/*
 * Blink using FastLED library.
 * 2016-0812 PePo new, changed so a random pixel is blinking
 * Note: Vcc neopixels > 5V, LiPo 7.7V rechtstreeks op voeding!
 */
#include "FastLED.h"
#include <Math.h> // 2016_0812 PePo added 

// How many leds in your strip?
#define NUM_LEDS 8

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6   // 2016_0812 PePO: D6
#define CLOCK_PIN 13 // 2016_0812 PePO: not used

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() 
{ 
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() 
{ 
  int i = random(NUM_LEDS); // / 2016_0812 PePo added
  
  // Turn the LED on, then pause
  leds[i] = CRGB::Green; //CRGB::Red;
  FastLED.show();
  delay(500);
  
  // Now turn the LED off, then pause
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(500);
}
