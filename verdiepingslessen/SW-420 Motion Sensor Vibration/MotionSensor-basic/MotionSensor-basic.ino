/* Arduino SW-420 Motion Sensor basic
 * 
 * Schematics:
 * 1. Grove protoshield:
 *    S0 - SENSOR-data (out)
 *    S1 - Not Connected
 *    Note:
 *    Shield white LED: on when sensor-data=HIGH, else off
 *    Sensor green LED: on when sensor-data=LOW, else off
 *    Sensor red LED = power on.
 *  
 * 2. Alarm object: either LED or Buzzer
 * 
 * 2016-0811 PePo new
 */

#define MOTION_SENSOR_PIN 2 // D2
#define ALARM_PIN 5 // D5
// for alarm object, either LED or Buzzer

void setup() {
  Serial.begin(115200) ; // voor debugging/testing
  
  // zet pin configuratie als INPUT of OUTPUT
  pinMode(MOTION_SENSOR_PIN, INPUT); // Sensor is input
  pinMode(ALARM_PIN, OUTPUT); // alarm is output
  
  // zet alle actuators OFF
  digitalWrite(ALARM_PIN, LOW); // no alarm
}

void loop() {
  // lees sensordata
  int sensorValue = digitalRead(MOTION_SENSOR_PIN);
  Serial.println(sensorValue);

  // als detectie, dan actie...
  if (sensorValue == 1) {
    digitalWrite(ALARM_PIN, HIGH); // alarm on
  } else {
    digitalWrite(ALARM_PIN, LOW); // alarm off
  }

  delay(100); // add some delay
}
