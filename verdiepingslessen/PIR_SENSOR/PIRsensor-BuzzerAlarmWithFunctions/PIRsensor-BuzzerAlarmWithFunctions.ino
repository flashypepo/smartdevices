/* Arduino PIR Motion Sensor basic with alarms (led, buzzer)
 * 
 * Electronics:
 * 1. Grove protoshield:
 *    PIR_SENSOR HC-SR505 (S0) -> D7
 *    LED (S1) -> D8
 * 2. Grove Buzzer op pin D5
 * 3. PIR Sensor HC-SR501 op D6
 * 
 * Using functions increases semantics of code for 
 * better understanding what's going on:
 * in loop: (user)functional talk (person/object detection, alarm)
 * in functions: technical stuff (led/buzzer-pin, HIGH/LOW..)
 * 
 * Question: read careful the printouts in the Serial Monitor.
 * Do you notice something peculiar? Explain!
 * Hint: check output with conditional statement (r36-37)
 * if ( isObjectDetected(PIR_SENSOR2_PIN) ....
 * 
 * 2016-0811 PePo new
 * Original with relay: 
 *     by Dejan Nedelkovski, www.HowToMechatronics.com
 */

//* Grove protoshield: pins for PIR_SENSOR and LED
//int pirSensor = 8;
//int relayInput = 7;
// Question: why is a #define a better way?
#define PIR_SENSOR_PIN 7 // D7
#define LED_PIN 8  // D8

#define BUZZER_PIN 5  // D5
#define PIR_SENSOR2_PIN 6 // D6

void setup() {
  Serial.begin(115200) ; // voor debugging/testing
  
  // configure the actuators and sensors
  initLED(LED_PIN); //  LED
  initPIRsensor(PIR_SENSOR_PIN); // PIR SR505 sensor
  initPIRsensor(PIR_SENSOR2_PIN); // PIR SR501 sensor
  initBuzzer(BUZZER_PIN); // buzzer
 }

void loop() {
  // is object detected?
  if ( isObjectDetected(PIR_SENSOR2_PIN) 
        || isObjectDetected(PIR_SENSOR_PIN) ) {
    // alarm!!!
    ledOn(LED_PIN);
    buzzerOn(BUZZER_PIN);
  } else {
    // stop alarms
    ledOff(LED_PIN);
    buzzerOff(BUZZER_PIN);
  }
  // wait a little while before next measurement
  delay(1000); 
  }


/* -----------------------------------------------------
 * Helper functions
 */

// configure LED on pin...
void initLED(int pin) 
{
  pinMode(pin, OUTPUT); // led is output
  digitalWrite(pin, LOW); // led is off
}
// turning light LED on pin 
void ledOn(int pin) 
{
  digitalWrite(LED_PIN, HIGH);
}
// off light LED on pin 
void ledOff(int pin) 
{
  digitalWrite(LED_PIN, LOW); 
}

// setup Buzzer...
void initBuzzer(int pin) 
{
  pinMode(pin, OUTPUT); // buzzer
  digitalWrite(pin, LOW); // no noise
}
// sound buzzer on pin
void buzzerOn(int pin) 
{
  digitalWrite(BUZZER_PIN, HIGH); 
}
// sound off buzzer on pin
void buzzerOff(int pin) 
{
  digitalWrite(BUZZER_PIN, LOW); 
}

// setup PIR sensor...
void initPIRsensor(int pin) 
{
  pinMode(pin, INPUT); // sensor gives data
}

// is an object/person detected?
// if yes returns true, else returns false
// Question: why not make a function 'int readPIRSensor(pin)' ?
bool isObjectDetected(int pin) 
{
  // get sensor value from pin
  int s = digitalRead(pin);
  
  // print sensor value only for developer
  Serial.print("Sensor (pin ");
  Serial.print(pin);
  Serial.print("): "); 
  Serial.println(s); // sensor value and close line

  // specify the value to return to caller
  /*
  if (s == 1) {
    return true;
  } else {
    return false;
  } */
  // advanced statement:
  return (s==1) ? true : false;
}

