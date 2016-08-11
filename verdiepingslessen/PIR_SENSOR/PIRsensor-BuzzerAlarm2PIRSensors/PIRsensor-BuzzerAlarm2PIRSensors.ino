/* Arduino PIR Motion Sensor basic with alarms (led, buzzer)
 * 
 * Electronics:
 * 1. Grove protoshield:
 *    PIR_SENSOR HC-SR505 (S0) -> D7
 *    LED (S1) -> D8
 * 2. Grove Buzzer op pin D5
 * 3. PIR Sensor HC-SR501 op D6
 * 
 * 2016-0811 PePo new
 * Original with relay: 
 *     by Dejan Nedelkovski, www.HowToMechatronics.com
 */

//* Grove protoshield: pins for PIR_SENSOR and LED
//int pirSensor = 8;
//int relayInput = 7;
#define PIR_SENSOR_PIN 7 // D7
#define LED_PIN 8  // D8

#define BUZZER_PIN 5  // D5
#define PIR_SENSOR2_PIN 6 // D6

void setup() {
  Serial.begin(115200) ; // voor debugging/testing
  
  // zet pin configuratie als INPUT of OUTPUT
  pinMode(PIR_SENSOR_PIN, INPUT); // Sensor #1
  pinMode(PIR_SENSOR2_PIN, INPUT); // Sensor #2
  pinMode(LED_PIN, OUTPUT);  // LED
  pinMode(BUZZER_PIN, OUTPUT); // buzzer
  
  // zet alle actuators OFF
  digitalWrite(LED_PIN, LOW); // led off
  digitalWrite(BUZZER_PIN, LOW); // no noise
}

void loop() {
  // lees PIR sensordata
  int sensorValue = digitalRead(PIR_SENSOR_PIN);
  int sensor2Value = digitalRead(PIR_SENSOR2_PIN);
  Serial.print("Sensor #1: "); Serial.print (sensorValue);
  Serial.print(", Sensor #2: "); Serial.print (sensor2Value);
  Serial.println();

  // als detectie, dan actie...
  if ( sensorValue == 1 && sensor2Value == 1 ) {
    digitalWrite(LED_PIN, HIGH); // led on
    //digitalWrite(BUZZER_PIN, HIGH); // noise
  } else {
    digitalWrite(LED_PIN, LOW); // led off
    //digitalWrite(BUZZER_PIN, LOW); // noise off
  }

  delay(2000); // add some delay
}

