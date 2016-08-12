// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// 2016-0812 PePo - minor changes, added next-var to iterate through colors

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6 // 2016-0812 D6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8 // 2016-0812 8 pixels on the stick

// When we setup the NeoPixel library, we tell it 
// how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(10); // 2016-0812 added to dim brightness
  pixels.clear(); // 2016-0812 added to clear pixels
}

void loop() {
  executeSimple();
}

int next = 0; // 2016-0812 added counter for pattern

void executeSimple()
{
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if (next == 0) pixels.setPixelColor(i, pixels.Color(150,0,0)); // Moderately bright red color.
    if (next == 1) pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
    if (next == 2) pixels.setPixelColor(i, pixels.Color(0,0,150)); // Moderately bright blue color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  next = (next + 1) % 3; // counter, turnaround
}


