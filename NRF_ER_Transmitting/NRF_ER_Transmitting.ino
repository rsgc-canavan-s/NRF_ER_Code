#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

uint8_t inputCharacter;
byte addresses[][6] = {"Node1", "Node2"};

RF24 radio(7, 8);

const byte numCharacters = 16;
char arrayChar[numCharacters];

void setup() {
 radio.begin();
 Serial.begin(9600);

 radio.setPALevel(RF24_PA_LOW);
 radio.setChannel(106);

 radio.openWritingPipe(addresses[0]);
 radio.openReadingPipe(1, addresses[1]);
 
 radio.startListening();
}

void loop() {
 while (Serial.available()) {
   Serial.readBytes(arrayChar, numCharacters);
 }
 radio.stopListening();
 if (!radio.write( &arrayChar, sizeof(uint32_t))) {
   Serial.println("Failed");
 }
 radio.startListening();
}
