/*
   LoveOMeter with an 64 matrix/8-stick NeoPixels
   
   2016-1008 PePo new, adoptions for 64-pixel matrix - chinese
   2016-0812 PePo new, adoptions for WS2812 8-pixel stick - chinese
   Note: Vcc for neoixels miust be >5V, so connect LiPy (7.7V) directly
         on breadboard
*/

#include "FastLED.h"
#include <Math.h> // 2016-0812: instead of potentiometer value

// How many leds are connected?
#define NUM_LEDS 64//8

// Define the Pins
#define DATA_PIN 6 // D6

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200); // 2016-0812 PePo
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  int val = random(950); // 2016-0812 PePo LATER TEDOEN: analogRead(1);
  Serial.print(" val="); Serial.print(val);

  // Map the pot values to 0 - Number of Leds
  int numLedsToLight = map(val, 0, 950, 1, NUM_LEDS);
  Serial.print(",\t numLedsToLight="); Serial.println(numLedsToLight);

  // Clear the existing led values
  FastLED.clear();
  FastLED.setBrightness(10);
  // Change led colors
  for (int led = 0; led < numLedsToLight; led++) {
    if (led < numLedsToLight/4) leds[led] = CRGB::Green;
    if (led >= numLedsToLight/4 & led < numLedsToLight/2) leds[led] = CRGB::Blue;
    if (led >= numLedsToLight/2) leds[led] = CRGB::Red;
  } 
  //FastLED.setBrightness(10);
  FastLED.show();

  delay(500);
}

