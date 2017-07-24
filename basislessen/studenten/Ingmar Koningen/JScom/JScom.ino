#include <LiquidCrystal.h>

const int ledPin1 = 7;
const int ledPin2 = 8;
const int ledPin3 = 10;
int incomingByte;      // a variable to read incoming serial data into
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}
 
void loop() {

  
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'R') {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Rood!");
    }
    if (incomingByte == 'G') {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Groen!");
    }
    if (incomingByte == 'B') {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Blauw!");
    }
    
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      lcd.begin(16, 2);
      lcd.print("lampje uit!");
    }
  }
}
