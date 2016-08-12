/*
 * Cylon - aangepast voorbeeld uit de FastLED library...
 * 
 * FastLED library: https://github.com/FastLED/FastLED
 * 2016-0812 PePo works as long as Vcc (stick) > 5V!
 * 
 */
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 8  // 2016-0812

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6 // 2016-0812 - D6
#define CLOCK_PIN 13 // 2016-0812 - not used

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(115200);
	Serial.println("resetting...");
 
  //FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS); // 2016-0812 WS2812
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS); // 2016-0812 WS2812
	FastLED.setBrightness(84);
}

// 2016-0812 changed value 250 into 220 - better effect
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(220); } } // 250

void loop() { 
	static uint8_t hue = 0;

	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
    // 2016-0812 led remains lit when not going to black.
		//leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(50);//(10);
	}

	// Now go in the other direction.  
  hue = 0;
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		//leds[i] = CRGB::Black;
    FastLED.show(); //
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(50);//(10);
	}
}

