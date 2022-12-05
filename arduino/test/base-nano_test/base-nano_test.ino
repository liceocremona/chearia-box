//Codice ricevitore base


#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio; // CE, CSN
#define DELAY 2000
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
//    if (!radio.begin(7, 8)) {
//   Serial.println("La radio non funziona");
//   while (1) {Serial.println("La radio non funziona");} // hold program in infinite loop to prevent subsequent errors
// }
// radio.openReadingPipe(0, address);
//   radio.setPALevel(RF24_PA_HIGH);
//   radio.startListening();
}

void loop() {
  Serial.println("testo itwork");
  char data_itwork[32] = "90.90-itwork";
  Serial.println(data_itwork);
  Wire.beginTransmission(8); // transmit to device
  Wire.write(data_itwork);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

  Serial.println("testo pressure");
  char data_pressure[32] = "9997.384-pressure";
  Serial.println(data_pressure);
  Wire.beginTransmission(8); // transmit to device 
  Wire.write(data_pressure);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

  Serial.println("testo altitudine");
  char data_altitude[32] = "20.23-altitude";
  Serial.println(data_altitude);
  Wire.beginTransmission(8); // transmit to device
  Wire.write(data_altitude);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

  Serial.println("testo CO");
  char data_CO[32] = "15.00-CO";
  Serial.println(data_CO);
  Wire.beginTransmission(8); // transmit to device 
  Wire.write(data_CO);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

  Serial.println("testo humidity");
  char data_humidity[32] = "78.399-humidity";
  Serial.println(data_humidity);
  Wire.beginTransmission(8); // transmit to device 
  Wire.write(data_humidity);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

  Serial.println("testo ozone");
  char data_ozone[32] = "50.00-ozone";
  Serial.println(data_ozone);
  Wire.beginTransmission(8); // transmit to device 
  Wire.write(data_ozone);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(DELAY);

}
