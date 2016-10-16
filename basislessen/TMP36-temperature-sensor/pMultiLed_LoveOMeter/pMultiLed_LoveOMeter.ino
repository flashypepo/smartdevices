/*
  Arduino Starter Kit example
 Project 3  - Love-O-Meter

 2016-1008 PePo changed using (1) Grove-LedBar, (2) Digit Display en TMP36 op protoshield
  * Digit display: Clock-pin=9, Data-pin=8,
  * LedBar: Clock-pin=9, Data-pin=8,
  * TMP36 aangesloten op A1

 This sketch is written to accompany Project 3 in the Arduino Starter Kit

 Parts required:
 1 TMP36 temperature sensor
 1 Grove LedBar
 1 Grove Digit 7-segment Display
 
 Original created 13 September 2012
 by Scott Fitzgerald

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
 */
#include <Math.h>
// include Grove LedBar library
#include <Grove_LED_Bar.h>
// include Grove Digit-Display library
#include <TM1637.h>
#include <TimerOne.h> // Timer for updating Digit-Display

//* named constant for the pin the sensor is connected to
//const int sensorPin = A1; // breadboard, Starterskit
#define TEMPERATURE_PIN A0 // TMP36 op analoge pin A0
#define CLOCK_PIN 8 // LedBar: clock-pin op D8
#define DATA_PIN 9 // LedBar: data-pin op D9
#define ORIENTATION 1 // =0:start with red-LED, =1 start with green-LED

//pins definitions for TM1637 and can be changed to other ports
#define CLK 2 
#define DIO 3
//#define BRIGHTNESS BRIGHTEST
#define BRIGHTNESS BRIGHT_TYPICAL
//#define BRIGHTNESS BRIGHT_DARKEST
TM1637 tm1637(CLK,DIO); // TM1637 object to control digits
int8_t tempDisp[] = {0x00,0x00,0x00,0x00}; // temperature digits

// baseline temperature: room temperature in Celcius
const float baselineTemp = 20.0;

// define a LedBar object, based upon Clock pin, Data pin, Orientation
Grove_LED_Bar bar(DATA_PIN, CLOCK_PIN, ORIENTATION);

void setup() {
  // open a serial connection to display values
  Serial.begin(115200);
  
  // initialize the LedBar
  bar.begin();
  
  // initialize the TM1637
  tm1637.set(BRIGHTNESS);
  tm1637.init();
  //Timer1.initialize(500000);//timing for 500ms
  //Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
}

void loop() {
  // read the 10-bit sensor value on sensor pin,
  // value in range [0..1024], 1024=2**10
  // and store it in a variable
  int sensorVal = analogRead(TEMPERATURE_PIN);

  // debug: send the 10-bit sensor value out the serial port
  Serial.print("sensor Value: ");
  Serial.print(sensorVal);

  // convert the ADC reading to voltage
  // voltage in range [0.. 5]
  float voltage = (sensorVal / 1024.0) * 5.0;

  // debug: send the voltage level out the Serial port
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((voltage - 500mV) times 100)
  float temperature = (voltage - .5) * 100;
  Serial.print(", ");
  Serial.print("*");
  Serial.print("C: ");
  Serial.println(temperature);

  // if the current temperature is lower than the baseline
  // turn off all LEDs
  int count = 0;
  if (temperature < baselineTemp) {
    Serial.print(".... 0 ");
    count = 0;
  } // if the temperature rises 1 degrees, turn i=on another LEDs on
  else if (temperature < baselineTemp + 1) {
    Serial.print(".... 1 ");
    count = 1;
  } // if the temperature rises 2-4 degrees, turn 6 LEDs on
  else if (temperature < baselineTemp + 2) {
    Serial.print(".... 2 ");
    count = 2;
  } // if the temperature rises 2-4 degrees, turn 6 LEDs on
  else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    Serial.print(".... 5 ");
    count = 5;
  } // if the temperature rises 4-6 degrees, turn 8 LEDs on
  else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
    Serial.print(".... 6 ");
    count = 6;
  } // if the temperature rises more than 6 degrees, turn all LEDs on
  else if (temperature >= baselineTemp + 6 && temperature < baselineTemp + 8) {
    Serial.print(".... 8 ");
    count = 8;
  }
  else if (temperature >= baselineTemp + 8 && temperature < baselineTemp + 10) {
    Serial.print(".... 9 ");
    count = 9;
  }
  else if (temperature >= baselineTemp + 10) {
    Serial.print(".... 10 ");
    count = 10;
  }
  // turn on 'count' LEDs...
  turnLedsOnTo(count);
  // update digit-display
  digitDisplayUpdate(temperature);
  
  delay(500);
}

// turn leds on until n, other leds are off
void turnLedsOnTo(int n) 
{
  // turn all LEDs off
  //turnAllLedsOff();
  // Turn n LEDs on until n-th 
  for (int i = 1; i <= n; i++) {
    bar.setLed(i, 1);
    //delay(5);
  }
  // Turn off LEDs n+1 .. 10 
  for (int i = n+1; i <= 10; i++) {
    bar.setLed(i, 0);
    //delay(5);
  }
}
// Turn all LEDs off
void turnAllLedsOff()
{
  for (int i = 1; i <= 10; i++) {
    bar.setLed(i, 0);
    //delay(5);
  }
}

/* 2016-1009 how to dislay a '.' ??
void digitDisplayUpdate(float temp)
{
  int t = floor(temp * 100);       // 1934
  Serial.print(", t="); Serial.println(t);
  tempDisp[0] = floor(t  / 1000);      // 1 
  t = t - 1000;   // 934
  tempDisp[1] = floor(t  / 100);       // 9
  t = t - (floor(t/100) * 100);  // 34
  tempDisp[2] = floor(t / 10);         // 3
  tempDisp[3] = t % 10;                // 4
  // put on display
  tm1637.display(tempDisp);
} */
void digitDisplayUpdate(float temp)
{
  int t = round(temp); // afronden op 2 cijfers
  tempDisp[0] = 0x7f; // see TM1637.cpp - Cleardisplay()
  tempDisp[1] = 0x7f;
  tempDisp[2] = floor(t / 10);      // 1
  tempDisp[3] = t % 10;             // 9
  // put on display
  tm1637.display(tempDisp);
}
