/* 
 *  joystick Controlled panning and tilting Servo 
 *  
 *  2016-0816 PePo re-written, no if-statements and different mappings.
 *  Note: servo's make noise, becasue they move a little. Reason unknown.
 *  
 *  made by Marcel C.
        mmc.mars@gmail.com  
 * simple code I wrote to control servos
 * using analog input like a joystick 
 * Two servo's one for each axis Z and X.
 * see instructables.com
*/

#include <Servo.h>
#include <Math.h>

Servo servoZ; // tilt movement (vertikaal)
Servo servoX; // pan movement (horizontaal)

#define joystickZ  A2 // tilt
#define joystickX A4 // pan

int sensorValueZ = 0;
int outputValueZ = 0;
int sensorValueX = 0;
int outputValueX = 0;
// 2016-0816 PePo: initial values, trial-and-error
int turnZ = 45; 
int turnX = 90;

void setup()
{
  Serial.begin(115200);
  servoX.attach(5); // pan servo
  servoZ.attach(6); // tilt servo
  
  servoX.write(turnX); // 2016-0816 PePo added
  servoZ.write(turnZ); // 2016-0816 PePo added

  // SW-signaal is niet de button-knop ??
  //pinMode(3, INPUT);
}

void loop()
{
  // read joystick for tilt-movement ...
  sensorValueZ = analogRead(joystickZ);            
  //outputValueZ = map(sensorValueZ, 0, 1023, 0, 180);
  outputValueZ = map(sensorValueZ, 0, 1023, 90, 0); 
  // do movement only when value is changed...
  // 2016-0816 PePo added
//OK:  if (outputValueZ != turnZ) {
  if ( abs(outputValueZ - turnZ) > 1) {
    Serial.print("sensorZ = " );
    Serial.print(sensorValueZ);      
    Serial.print("\t outputZ = ");      
    Serial.print(outputValueZ);
    Serial.print("\t turnZ = ");      
    Serial.println(turnZ);
    
    servoZ.write(outputValueZ); // 2016-0816 PePo added
    turnZ = outputValueZ; // remember new value
  }

  // read joystick for pan-movement ...
  sensorValueX = analogRead(joystickX);
  outputValueX = map(sensorValueX, 0, 1023, 0, 180);
  // do movement only when value is changed...
  // 2016-0816 PePo added
  //if (outputValueX != turnX) {
  if (abs(outputValueX - turnX) > 1) {
    Serial.print("sensorX = " );                       
    Serial.print(sensorValueX);      
    Serial.print("\t outputX = ");      
    Serial.print(outputValueX);
    Serial.print("\t turnX = ");      
    Serial.println(turnX);
    
    servoX.write(outputValueX);
    turnX = outputValueX; // remember new value
  }
  /* joystick button pressed?
  // 2016-0816: SW-signaal is niet de button-knop ??
  Serial.print("SW="); Serial.println(digitalRead(3));
  */
  delay(50); // 2016-0816 PePo added
}

/* -------------------------
// oorspronkelijke code...
// -------------------------
void loop_2()
{
  {
    if (outputValueZ > 90)
    {
      servoZ.write(turnZ += 1);
    }
  }
  {
    if (outputValueZ > 10)
    {
      servoZ.write(turnZ += 2);
    }
  }
  {
    if (outputValueZ < 160)
    {
      servoZ.write(turnZ -= 1);
    }
  }
  {
    if (outputValueZ < 245)
    {
      servoZ.write(turnZ -= 2);
    }
  }   
  sensorValueZ = analogRead(joystickZ);
  outputValueZ = map(sensorValueZ, 0, 1023, 0, 255); 
  Serial.print("sensorZ = " );                       
  Serial.print(sensorValueZ);      
  Serial.print("\t outputZ = ");      
  Serial.println(outputValueZ);  
  {
    if (outputValueX > 90)
    {
      servoX.write(turnX += 1);
    }
  }
  {
    if (outputValueX > 10)
    {
      servoX.write(turnX += 2);
    }
  }
  {
    if (outputValueX < 160)
    {
      servoX.write(turnX -= 1);
    }
  }
  {
    if (outputValueX < 245)
    {
      servoX.write(turnX -= 2);
    }
  }  
  sensorValueX = analogRead(joystickX);            
  outputValueX = map(sensorValueX, 0, 1023, 0, 255); 
  Serial.print("sensorX = " );                       
  Serial.print(sensorValueX);      
  Serial.print("\t outputX = ");      
  Serial.println(outputValueX);  
}
 ---------------------------------- */
   
