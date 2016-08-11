/* Arduino PIR Motion Sensor basic with alarms (led, buzzer)
 * 
 * Electronics:
 * 1. Grove protoshield:
 *    PIR_SENSOR HC-SR505 (S0) -> D7
 *    LED (S1) -> D8
 * 2. Grove Buzzer op pin D5
 * 
 * 2016-0811 PePo new
 * Original with relay: 
 *     by Dejan Nedelkovski, www.HowToMechatronics.com
 */

//* Grove protoshield: pins for PIR_SENSOR and LED
#define PIR_SENSOR_PIN 7 // D7
#define LED_PIN 8  // D8

#define BUZZER_PIN 5  // D5

void setup() {
  Serial.begin(115200) ; // voor debugging/testing
  
  // zet pin configuratie als INPUT of OUTPUT
  pinMode(PIR_SENSOR_PIN, INPUT); // Sensor #1
  pinMode(LED_PIN, OUTPUT);  // LED
  pinMode(BUZZER_PIN, OUTPUT); // buzzer
  
  // zet alle actuators OFF
  digitalWrite(LED_PIN, LOW); // led off
  digitalWrite(BUZZER_PIN, LOW); // no noise
}

void loop() {
  // lees PIR sensordata
  int sensorValue = digitalRead(PIR_SENSOR_PIN);
  Serial.println(sensorValue); // test

  // als detectie, dan actie...
  if ( sensorValue == 1 ) {
    digitalWrite(LED_PIN, HIGH); // led on
    digitalWrite(BUZZER_PIN, HIGH); // noise
  } else {
    digitalWrite(LED_PIN, LOW); // led off
    digitalWrite(BUZZER_PIN, LOW); // noise off
  }

  delay(2000); // add some delay
}

