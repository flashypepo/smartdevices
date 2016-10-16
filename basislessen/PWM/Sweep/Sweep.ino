/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 n2016_1006 PePo - servo op PWM pin 11

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int speed = 50; // 2016_1006 PePo added to control speed of rotation

void setup() {
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(speed);                       // waits 15ms for the servo to reach the position
  }
  //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(speed);                       // waits 15ms for the servo to reach the position
  }
}

