//Codice ricevitore base


#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio; // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
   if (!radio.begin(7, 8)) {
  Serial.println("La radio non funziona");
  while (1) {Serial.println("La radio non funziona");} // hold program in infinite loop to prevent subsequent errors
}
radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
  Serial.println("Ascoltando sul canale radio...");
  if (radio.available()) {
    char data[32] = "";
    radio.read(&data, sizeof(data));
    Serial.println(data);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(data);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    delay(1000);
  }
}
