/*
 * Arduino For Beginners - Rui and Sara 2016-0903
 * chapter 4 Automatic Lights with light sensor
 * 
 * 2016_0918 pin LED en SensorPin changed
 * 2016-0910 new, experiments Serial Monitor/Serial plotter
 */

// pin configuratie
int ledPin = 3;  // LED
int ledBrightness = 0; // memory storage for LED brightness value
int sensorPin = A5; // lightsensor
int sensorValue = 0; // memory storage for lightsensor value

void setup() 
{
  // sets the LED as an output
  pinMode(ledPin, OUTPUT);
  // sets the photoresistor as an input
  pinMode(sensorPin, INPUT);
  // start serial communication with computer
  Serial.begin(9600);
}
//* Serial Monitor or Serial Plotter
void loop() 
{
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor reading: ");
  Serial.println(sensorValue);
  
  // led gets brighter the darker is it at the sensor
  // that means we have to invert the reading from 0-1023 to 1023-0
  // map 0-1023 to 0-255 (=range analogWrite)
  sensorValue = 1023 - sensorValue;
  // map(value, fromLow, fromHigh, toLow, toHigh)
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);
  delay(50);
}
/*/
// Serial Plotter
void loop() 
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  sensorValue = 1023 - sensorValue;
  ledBrightness = map(sensorValue, 0, 1023, 0, 255);
  //Serial.println(ledBrightness);
  analogWrite(ledPin, ledBrightness);
  delay(50);
}
//*/

