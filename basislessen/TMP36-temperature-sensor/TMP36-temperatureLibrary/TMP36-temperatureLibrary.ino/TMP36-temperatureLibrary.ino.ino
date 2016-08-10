/*
   Sketch for temperature measurement, using TMP36
   using a Temperature Library
   https://github.com/jeroendoggen/Arduino-temperature-sensor-library

   Notes: 
   1. temperatuur komt lager uit dan via basic sketch ???
   2. above THRESHOLD temperatuur: de TMP36 meet afwisselend 
   hoge en lage temperaturen. Reden: onbekend.

   alarm:
   if T>THRESHOLD: Led on
   TMP36 - data: connect to Analog port (A0).
   LED - D7

   2016_0810 PePo using Temperature Library

*/

#include "TemperatureTMP.h"

// LED
int LEDPin = 6; // D6


TemperatureTMP Temperature;
float temperature;

void setup()
{
  Serial.begin(115200);
  Temperature.begin(A0);

  // 2016-0810: initialize LED pin as output
  pinMode(LEDPin, OUTPUT);
}

void loop()
{
  temperature = Temperature.getTemperatureCelcius();
  Serial.print("Temperature: ");
  Serial.println(temperature,1);

  // check for alarm
  if (temperature > 22.9) {
    digitalWrite(LEDPin, HIGH);  
  } else { 
    digitalWrite(LEDPin, LOW);  
  }
  
  delay(500);
}
