/*
 * BlinkLed13 = sketch 03_02_interrupt_flash
 * from Simon Monk - Progrmaming Arduino - Next Step, ch3
 * 
 * 2016-0812 PePo
 */
int ledPin = 13;
volatile boolean flashFast = false;
volatile boolean isPrint = false;

void setup()
{
  Serial.begin(115200); //
  
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0, stuffHapenned, FALLING);

  Serial.println("stuff will happen...");

}

void loop()
{
  int period = 5000;
  if (flashFast) period = 100;
  digitalWrite(ledPin, HIGH);
  delay(period);
  digitalWrite(ledPin, LOW);
  delay(period);

  // 2016-0812 added
  if (isPrint) {
    Serial.println("stuff had hapenned");
    isPrint = false; // reset
  }
}

void stuffHapenned()
{
  flashFast = ! flashFast;
  isPrint = true; //
}
