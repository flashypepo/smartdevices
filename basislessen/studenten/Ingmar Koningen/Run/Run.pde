 import processing.serial.*;
 Serial port;
 
 void setup()  { 
    port = new Serial(this, Serial.list()[0], 9600);  // Open the port that the Arduino board is connected to, at 9600 baud
 
}
 void draw() {
 
    String onoroff[] = loadStrings("http://localhost/Led/LEDstate.txt"); // Insert the location of your .txt file
    print(onoroff[0]);  
   
    if (onoroff[0].equals("1") == true) {
      println(" - TELLING ARDUINO TO TURN LED ON");
      port.write('R');
    } 
    else if (onoroff[0].equals("2") == true) {
      println(" - TELLING ARDUINO TO TURN LED ON");
      port.write('G');
    } 
    else if (onoroff[0].equals("3") == true) {
      println(" - TELLING ARDUINO TO TURN LED ON");
      port.write('B');
    } 
    else {
      println(" - TELLING ARDUINO TO TURN LED OFF");
      port.write('L');
   }
 
  delay(2000);
 }