/*
 * HC-SR04 ultrasonic sensor - on top of servo 
 * 
 * Hardware:
 * 1. servo on pin D9 (PMW)
 * 2. Grove Ultrasonic sensor 
 *    Echo: Echo (OUTPUT) - S0 / Pin D5
 *    Trig : Trigger (INPUT) - S1 / Pin D6 
 *
 * 2016_1029 PePo new
 */
#include <Servo.h>
#include <NewPing.h>

#define ECHO_PIN 5 
#define TRIGGER_PIN 6 
#define MAX_DISTANCE 200

// look position parameters
// 2016_1029 PePo updated with servo on bracket
#define LOOK_FORWARD 145//115
#define LOOK_LEFT 190 //180
#define LOOK_RIGHT 85 //50

// create HSR04 object sonar...
// using NewPing using pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
int distance = 100;

#define SERVO_PIN 9
// create servo object ...
Servo sonarServo;

void setup() 
{
  Serial.begin (115200);
  sonarServo.attach(SERVO_PIN);
  sonarServo.write(115);
  delay(2000);
  
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{
  int distanceR = 0;
  int distanceL = 0;
  delay (500);//(40);
 
  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if ( distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}

int lookRight()
{
    Serial.print("look right...");
    sonarServo.write(LOOK_RIGHT); 
    delay(500);
    int distance = readPing();
    delay(100);
    sonarServo.write(LOOK_FORWARD); 
    return distance;
}

int lookLeft()
{
    Serial.print("look left...");
    sonarServo.write(LOOK_LEFT); 
    delay(500);
    int distance = readPing();
    delay(100);
    sonarServo.write(LOOK_FORWARD); 
    return distance;
    delay(100);
}

int readPing() 
{ 
  //delay(70);
  int cm = sonar.ping_cm();
  delay(70);
  if (cm == 0)  { cm = 250;  }
  // debugging
  Serial.print("Afstand: "); Serial.print(cm); 
  Serial.println(" cm");
  return cm;
}

void moveStop() {
  Serial.println("stop...");
} 
  
void moveForward() {
  Serial.println("move forward...");
}

void moveBackward() {
  Serial.println("move backward...");
}  

void turnRight() {
  Serial.println("turn right...");
} 
 
void turnLeft() {
  Serial.println("turn left...");
}  


