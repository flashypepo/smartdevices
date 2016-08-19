/*
   project23 - ID program with Buzzer and LEDS

   2016-0819 PePo new
       based upon Project 23 from 'Arduino Projects Handbook'
       https://www.nostarch.com/arduinohandbook/

   pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino      Arduino
   SPI         Reader/PCD   Uno          Nano v3
   Signal      Pin          Pin          Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9            D5
   SPI SS      SDA(SS)      10           D10
   IRQ         ?            ?            not used
   SPI MOSI    MOSI         11 / ICSP-4  D11
   SPI MISO    MISO         12 / ICSP-1  D12
   SPI SCK     SCK          13 / ICSP-3  D13

   LED1        Cathode                   D2
   LED2        Cathode                   D3
   Buzzer      S                         D8
   Servo       S                         D9
*/
#include <SPI.h>
//* using library provided by the obok
#include <RFID.h>
/*/
  // GitHub: RFID Library by Miquel Balboa
  //         https://github.com/miguelbalboa/rfid
  #include <MFRC522.h>
  //*/
#include <Servo.h>
#include "pitches.h"
#include <Wire.h>

// RFID reader configuration
#define SS_PIN 10  // see pin configuration
#define RST_PIN 5  // see pin configuration
RFID rfid(SS_PIN, RST_PIN);

// Setup variables
byte card[5] = {0x53, 0x0A, 0x17, 0x01, 0x4F}; // the 'RED' card
byte serNum[5];
byte data[5];

// Define the melodies for successful access and denied access
int access_melody[] = {NOTE_G4, 0, NOTE_A4, 0, NOTE_B4, 0, NOTE_A4,   0, NOTE_B4, 0, NOTE_C5, 0};
int access_noteDurations[] = {8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4};
int fail_melody[] = {NOTE_G2, 0, NOTE_F2, 0, NOTE_D2, 0};
int fail_noteDurations[] = {8, 8, 8, 8, 8, 4};

int LED_access = 2;   // Pin connected to LED1
int LED_intruder = 3; // Pin connected to LED2
int speaker_pin = 8;  // Pin connected to piezo buzzer
int servoPin = 9;     // Pin connected to servo

Servo doorLock; // define servomotor

void setup()
{
  Serial.begin(115200);
  doorLock.attach(servoPin); // Set servo as a pin
  SPI.begin(); // Start serial communication between the RFID and PC
  rfid.init(); // Initialize the RFID
  Serial.println("Arduino kaartlezer");
  delay(1000);
  pinMode(LED_access, OUTPUT);
  pinMode(LED_intruder, OUTPUT);
  pinMode(speaker_pin, OUTPUT);
  pinMode(servoPin, OUTPUT);
}

void loop()
{
  boolean card_card = true; // Define your card
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      delay(1000);
      data[0] = rfid.serNum[0];
      data[1] = rfid.serNum[1];
      data[2] = rfid.serNum[2];
      data[3] = rfid.serNum[3];
      data[4] = rfid.serNum[4];
    }
    Serial.print("Card found - code:");
    for (int i = 0; i < 5; i++) {
      // If it is not your card, the card is considered false
      if (data[i] != card[i]) card_card = false;
    }
    Serial.println();
    if (card_card) { // A card with access permission is found
      Serial.println("Hello!"); // Print to Serial Monitor
      for (int i = 0; i < 12; i++) { // Play welcome music
        int access_noteDuration = 1000 / access_noteDurations[i];
        tone(speaker_pin, access_melody[i], access_noteDuration);
        int access_pauseBetweenNotes = access_noteDuration * 1.30;
        delay(access_pauseBetweenNotes);
        noTone(speaker_pin);
      }
    }
    else { // If the card is not recognized
      // Print message to Serial Monitor
      Serial.println("Card not recognized! Contact administrator!");
      digitalWrite(LED_intruder, HIGH); // Turn on red LED
      for (int i = 0; i < 6; i++) { // Play intruder melody
        int fail_noteDuration = 1000 / fail_noteDurations[i];
        tone(speaker_pin, fail_melody[i], fail_noteDuration);
        int fail_pauseBetweenNotes = fail_noteDuration * 1.30;
        delay(fail_pauseBetweenNotes);
        noTone(speaker_pin);
      }
      delay(1000);
      digitalWrite(LED_intruder, LOW); // Turn off red LED
    }

    if (card_card) { // Add other users with access here
      Serial.println("Access granted.......Welcome!");
      digitalWrite(LED_access, HIGH); // Turn on green LED
      doorLock.write(180); // Turn servo 180 degrees
      delay(5000); // Wait for 5 seconds
      doorLock.write(0); // Turn servo back to 0 degrees
      digitalWrite(LED_access, LOW); // Turn off green LED
    }
    Serial.println();
    delay(500);
    rfid.halt();
  }
}
