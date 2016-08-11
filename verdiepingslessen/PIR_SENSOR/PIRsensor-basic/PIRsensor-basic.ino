/* Arduini PIR Motion Sensor basic
 * Grove protoshield:
 *  PIR_SENSOR (S0) -> D7
 *  LED (S1) -> D8
 *  
 * Original with relay: 
 *     by Dejan Nedelkovski, www.HowToMechatronics.com
 */

//* 2016-0811 Grove protoshield: pins for PIR_SENSOR and LED
//int pirSensor = 8;
//int relayInput = 7;
#define PIR_SENSOR_PIN 7 // D7
#define LED_PIN 8  // D8

#define BUZZER_PIN 5  // of 5

void setup() {
  Serial.begin(115200) ; // voor debugging/testing
  
  // zet pin configuratie als INPUT of OUTPUT
  pinMode(PIR_SENSOR_PIN, INPUT); // Sensor
  pinMode(LED_PIN, OUTPUT);  // LED
  pinMode(BUZZER_PIN, OUTPUT); // buzzer
  
  // zet alle actuators OFF
  digitalWrite(LED_PIN, LOW); // led off
  digitalWrite(BUZZER_PIN, LOW); // no noise
}

void loop() {
  // lees PIR sensordata
  int sensorValue = digitalRead(PIR_SENSOR_PIN);
  Serial.println(sensorValue);

  // als detectie, dan actie...
  if (sensorValue == 1) {
    digitalWrite(LED_PIN, HIGH); // led on
    digitalWrite(BUZZER_PIN, HIGH); // noise
  } else {
    digitalWrite(LED_PIN, LOW); // led off
    digitalWrite(BUZZER_PIN, LOW); // noise off
  }

  delay(2000); // add some delay
}
