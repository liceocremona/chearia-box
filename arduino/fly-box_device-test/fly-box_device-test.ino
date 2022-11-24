#include <SFE_BMP180.h>
#include <MQ7.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio;  
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Serial.println("Testing radio:");
  if (!radio.begin(7,8))// CE, CSN 
  {
    Serial.println("Radio hardware not responding");
  }
  else 
  {
    Serial.println("Radio hardware responding");
    radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  if (radio.isChipConnected()){
    if (!radio.failureDetected) {
      Serial.println("Worka tutto");
    }
  }
  radio.stopListening();

  
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:
}
