/*
 * Sketch for temperature measurement, using TMP36
 * 
 * Note: Serial Plotter can be used instead of Serial Monitor, 
 * result: a graphic of temperature
 * 
 * 2016_0810 PePo nieuw
 * based upon: http://ardx.org/CODE10
 * 
 *  A simple program to output the current temperature to the IDE's debug window 
 *  For more details on this circuit: http://tinyurl.com/c89tvd 
 */

// TMP36 Pin Variables
int temperaturePin = 0; // A0
    //the analog pin the TMP36's Vout (sense) pin is connected to
    //the resolution is 10 mV / degree centigrade 
    //(500 mV offset) to make negative temperatures an option

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  Serial.begin(115200);
}
  
 
void loop()
{
 float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
 temperature = (temperature - .5) * 100;          //converting from 10 mv per degree wit 500 mV offset
                                                  //to degrees ((volatge - 500mV) times 100)
 Serial.println(temperature);                     //printing the result
 delay(1000);                                     //waiting a second
}

/*
 * getVoltage() - returns the voltage on the analog input defined by
 * pin
 */
float getVoltage(int pin){
  return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

