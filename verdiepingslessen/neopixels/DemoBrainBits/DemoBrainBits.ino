/*
 * Demo sketch from BrainBits.com using FastLED library
 * 2016-0812 PEPo new, adoptions for WS2812 RGB Pixel stick (8 LEDS) on port D6
 *  Note: Vcc neopixels > 5V, LiPo 7.7V rechtstreeks op voeding!
 */
#include "FastLED.h"

// How many leds are connected?
#define NUM_LEDS 8 //2016-0812 PePo changed from 32

// Define the Pins
#define DATA_PIN 6 //2016-0812 PePo changed from 2

// Define the array of leds
CRGB leds[NUM_LEDS];

// Put color values in arrays
long invader1a[] =
{
   0x008000, 0x000000, 0x000000,0x000000,0x000000,0x000000,0x000000, 0x008000,
0x008000, 0xFFFF00, 0x0000FF, 0xFFFF00, 0xFFFF00, 0x0000FF, 0xFFFF00, 0x008000,
0x008000, 0x000000, 0xFFFF00, 0x800080, 0x800080, 0xFFFF00, 0x000000, 0x008000,
0x000000, 0x000000, 0x000000, 0xFF0000, 0xFF0000, 0x000000, 0x000000, 0x000000
};

long invader1b[] =
{
   0x000000, 0x000000, 0x0000FF, 0xFFFF00, 0xFFFF00, 0x0000FF, 0x000000, 0x000000,
0x000000, 0x008000, 0xFFFF00, 0x800080, 0x800080, 0xFFFF00, 0x008000, 0x000000,
0x008000, 0x000000, 0x000000, 0xFFFF00, 0xFFFF00, 0x000000, 0x000000, 0x008000,
0x000000, 0x008000, 0x000000, 0xFF0000, 0xFF0000, 0x000000, 0x008000, 0x000000
};


void setup() { 
  Serial.begin(115200);
  
  //2016-0812 PePo changed from: 
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812,DATA_PIN>(leds, NUM_LEDS);
}

void loop() {  

  //2016-0812 PePo changed: instead of potentiometer, a random value
  //int val = analogRead(1);
  int val = random(950);
  Serial.print(" val="); Serial.print(val);
  
  if (val < 1000) {

    // Map the pot values to 0 - Number of Leds
    int numLedsToLight = map(val, 0, 950, 0, NUM_LEDS);
    Serial.print(" numLedsToLight="); Serial.println(numLedsToLight);

    // Clear the existing led values
    FastLED.clear();

    // Change led colors
    for(int led = 0; led < numLedsToLight; led++) { 
      /* 2016-0812 PePo changed, numLedsToLight < 8
      if(led < 12)leds[led] = CRGB::Green;
      if(led >=12 & led < 24)leds[led] = CRGB::Orange;
      if(led >=24)leds[led] = CRGB::Red;
      /*/
      if(led < 2) leds[led] = CRGB::Green;
      if(led >=2 & led < 4) leds[led] = CRGB::Orange;
      if(led >=4) leds[led] = CRGB::Red;
      //*/
     }
     FastLED.setBrightness(50);
     FastLED.show();
   }
   else {

//    Loop for the Matrix example
  
     FastLED.clear();
     for(int i = 0; i < NUM_LEDS; i++) {
       leds[i] = invader1a[i];
   }
   FastLED.setBrightness(50);
   FastLED.show();
   delay(500);
  
   for(int i = 0; i < NUM_LEDS; i++) {
     leds[i] = invader1b[i];
   }

   FastLED.setBrightness(50);
   FastLED.show();
   delay(500);
  
 }
 delay(5000);
}
