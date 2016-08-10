/*
 * HC-SR04 ultrasonic sensor, using NewPing library
 * 
 * 2016-0810 PePo - NewPing v1.8
 * Based upon http://randomnerdtutorials.com
 * created by http://playground.arduino.cc/Code/NewPing
 * 
 * Potentiele uitbreiding: 
 * Een I2C interface-kaart dat meerdere HC-SR04's aankan en 
 * toch maar 4 pinnen kost voor aansluiting op een Arduino (incl.Vcc en GND).
 * bron: http://redhunter.com/blog/2016/04/28/sonari2c-multiple-hc-sr04-sensors-on-arduino-i2c/
*/

#include <NewPing.h>
 
#define TRIGGER_PIN 6  // D6, 2016_0810 changed: 12
#define ECHO_PIN 5   // D5, 2016_0810 changed: 11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
 
void setup() {
   Serial.begin(115200); // 2016_0810 changed: 9600
}
 
void loop() {
   delay(1000); // 2016_0810 changed: 50
   // neem metingen...
   int cm = sonar.ping_cm();
   int inches = sonar.ping_in();
   
   // 2016_0810 changed output format
   Serial.print("Afstand: ");
   Serial.print(cm);      Serial.print(" cm, ");
   Serial.print(inches);  Serial.print(" inch");
   Serial.println(); // nieuwe regel
}

