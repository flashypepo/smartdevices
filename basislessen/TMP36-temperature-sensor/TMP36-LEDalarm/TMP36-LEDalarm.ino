/*
   Sketch for temperature measurement, using TMP36

   if T>THRESHOLD: Led on
   TMP36 - data: connect to Analog port (A0).
   LED - D7

   2016_0810 PePo added LED
   based upon: http://ardx.org/CODE10

    A simple program to output the current temperature to the IDE's debug window
    For more details on this circuit: http://tinyurl.com/c89tvd
*/

int LEDPin = 7; // D7

// TMP36 Pin Variables
int temperaturePin = 0; // A0
//the analog pin the TMP36's Vout (sense) pin is connected to
//the resolution is 10 mV / degree centigrade
//(500 mV offset) to make negative temperatures an option

// specificeer de THRESHOLD temperatuur voor alarm
const int THRESHOLD = 25;

/*
   setup() - this function runs once when you turn your Arduino on
   We initialize the serial connection with the computer
*/
void setup()
{
  Serial.begin(115200);
  // initialize LED pin as output
  pinMode(LEDPin, OUTPUT);
}


void loop()
{
  //getting the voltage reading from the temperature sensor
  float temperature = getVoltage(temperaturePin);

  // converting from 10 mv per degree wit 500 mV offset
  // to degrees ((voltage - 500mV) times 100)
  // zie datasheet!
  temperature = (temperature - .5) * 100;

  //printing the result
  Serial.print("Temperatuur: "); Serial.println(temperature);

  // set alarm if temperature is above the threshold
  if (temperature > THRESHOLD) {
    // turn the LED on by making the voltage HIGH
    digitalWrite(LEDPin, HIGH);
  } else {
    // turn the LED off by making the voltage LOW
    digitalWrite(LEDPin, LOW);
  }

  //waiting a second before next measurement
  delay(1000);
}

/*
   getVoltage() - returns the voltage on the analog input defined by
   pin
*/
float getVoltage(int pin) {
  return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
  // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}
