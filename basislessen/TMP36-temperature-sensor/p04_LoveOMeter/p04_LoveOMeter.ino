/*
  Arduino Starter Kit example
 Project 3  - Love-O-Meter

 2016-0810 PePo changed
    * toegevoegd extra LED en TMP36 op protoshield: 
        * LED aangesloten op D6
        * TMP36 aangesloten op A1
    * LED1_PIN en AANTAL_LEDS (leesbaarheid code)

 This sketch is written to accompany Project 3 in the Arduino Starter Kit

 Parts required:
 1 TMP36 temperature sensor
 3 red LEDs
 3 220 ohm resistors

 Created 13 September 2012
 by Scott Fitzgerald

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
 */

//* named constant for the pin the sensor is connected to
const int sensorPin = A2; // breadboard, Starterskit
/*/
// 2016-0810 toegevoegd:
const int sensorPin = A1; // Grove-protoshield
//*/
// room temperature in Celcius
const float baselineTemp = 20.0;

// 2016-0810 toegevoegd:
const int LED1_PIN = 3;
const int AANTAL_LEDS = 4;

void setup() {
  // open a serial connection to display values
  Serial.begin(9600);
  // set the LED pins as outputs
  // the for() loop saves some extra coding
  // 2016-0810 veranderd:
  //for (int pinNumber = 3; pinNumber < 7; pinNumber++) {
  for (int pinNumber = LED1_PIN; pinNumber < AANTAL_LEDS; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // read the value on sensor pin
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // send the 10-bit sensor value out the serial port
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);

  // convert the ADC reading to voltage
  float voltage = (sensorVal / 1024.0) * 5.0;

  // Send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((voltage - 500mV) times 100)
  Serial.print(", ");
  Serial.print("*");
  Serial.print("C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);

  // if the current temperature is lower than the baseline
  // turn off all LEDs
  if (temperature < baselineTemp) {
    Serial.print(".... 0 ");
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED1_PIN+1, LOW);
    digitalWrite(LED1_PIN+2, LOW);
    digitalWrite(LED1_PIN+3, LOW); // extra LED
  } // if the temperature rises 2 degrees, turn an LED on
  else if (temperature < baselineTemp + 2) {
    Serial.print(".... 1 ");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED1_PIN+1, LOW);
    digitalWrite(LED1_PIN+2, LOW);
    digitalWrite(LED1_PIN+3, LOW);  // extra LED
  } // if the temperature rises 2-4 degrees, turn a second LED on
  else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    Serial.print(".... 2 ");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED1_PIN+1, HIGH);
    digitalWrite(LED1_PIN+2, LOW);
    digitalWrite(LED1_PIN+3, LOW);  // extra LED
  } // if the temperature rises 4-6 degrees, turn a third LED on
  else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
    Serial.print(".... 3 ");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED1_PIN+1, HIGH);
    digitalWrite(LED1_PIN+2, HIGH);
    digitalWrite(LED1_PIN+3, LOW);  // extra LED
  } // if the temperature rises more than 6 degrees, turn all LEDs on
  else if (temperature >= baselineTemp + 6) {
    Serial.print(".... 4 ");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED1_PIN+1, HIGH);
    digitalWrite(LED1_PIN+2, HIGH);
    digitalWrite(LED1_PIN+3, HIGH);  // extra LED
  }
  delay(1000);
}

