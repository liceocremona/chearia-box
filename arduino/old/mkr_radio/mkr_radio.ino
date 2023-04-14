



/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio; // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  if (!radio.begin(4, 5)) {
  Serial.println(F("radio hardware not responding!"));
  while (1) {Serial.println("radio hardware not responding!");} // hold program in infinite loop to prevent subsequent errors
}
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  uint8_t pipe;
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    delay(100);
   // if(text==0){Serial.println("testo vuoto");}
  }
}
