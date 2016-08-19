/*
 * readcard - basic program to read Card Number
 * 
 * 2016-0819 PePo new
 *     based upon Project 23 from 'Arduino Projects Handbook'
 *     https://www.nostarch.com/arduinohandbook/
 * 
 * pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino      Arduino
 * SPI         Reader/PCD   Uno          Nano v3
 * Signal      Pin          Pin          Pin 
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9            D5 
 * SPI SS      SDA(SS)      10           D10
 * IRQ         ?            ?            not used  
 * SPI MOSI    MOSI         11 / ICSP-4  D11
 * SPI MISO    MISO         12 / ICSP-1  D12
 * SPI SCK     SCK          13 / ICSP-3  D13  
 */
#include <SPI.h>
//* using library provided by the obok
#include <RFID.h>
/*/
// GitHub: RFID Library by Miquel Balboa
//         https://github.com/miguelbalboa/rfid
#include <MFRC522.h>
//*/

// RFID reader configuration
#define SS_PIN 10  // Nano D10
#define RST_PIN 5  // Nano D5
RFID rfid(SS_PIN, RST_PIN);

// Setup variables
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void setup() 
{
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
}

void loop() 
{
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      if (rfid.serNum[0] != serNum0
          && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2
          && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4
         ) {
        // When a card is found, the following code will run
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        // Print the card ID to the Serial Monitor of the IDE
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");
        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");

      } else {
        // If the ID matches, write a dot to the Serial Monitor
        Serial.print(".");
      }
    }
  }
  rfid.halt();
}
