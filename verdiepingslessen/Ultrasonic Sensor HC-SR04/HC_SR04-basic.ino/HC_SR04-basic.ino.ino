/*
 * HC-SR04 ultrasonic sensor - basis operation
 * 
 * 2016_0810 PePo - changes
 * 
 * created by Rui Santos, http://randomnerdtutorials.com
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin D5 // 2016_0810 changed: 11
        Echo: Echo (OUTPUT) - Pin D6 // 2016_0810 changed: 12
        GND: GND
 */
 
int trigPin = 6; // 2016_0810 changed: 11;    //Trig - green Jumper
int echoPin = 5; // 2016_0810 changed: 12;    //Echo - yellow Jumper
long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (115200); //2016_0810 changed: 9600
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74; 

   // 2016_0810 changed output format
  Serial.print("Afstand: ");
  Serial.print(cm);
  Serial.print(" cm, ");
  Serial.print(inches);  
  Serial.println(" inch");
  //Serial.println();
  
  delay(1000); // 2016_0810 changed: 250
}

