#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <LiquidCrystal.h>

uint8_t inputCharacter;
byte addresses[][6] = {"Node1", "Node2"};

RF24 radio(7, 8);

uint32_t recieved[16];

LiquidCrystal lcd (8, 9, 10, 11, 12, 13);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();

  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(110);

  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(16, addresses[0]);

  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (radio.available()) {
    radio.read( &recieved, sizeof(recieved));
  }
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(1, 0);
    lcd.print(recieved[i]);
  }
}
