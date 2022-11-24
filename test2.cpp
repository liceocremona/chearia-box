//freertos test2
#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

int data1 = 0;
int data2 = 0;



void task1(void *pvParameters) {
  for (;;) {
    data1 = analogRead(A0);
    Serial.println(data1);
    vTaskDelay(1000);
  }
}

void task2(void *pvParameters) {
  for (;;) {
    data2 = analogRead(A1);
    Serial.println(data2);
    vTaskDelay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(task2, "task2", 128, NULL, 1, NULL);
}

void loop() {
  radio.write(&data1, sizeof(data1));
  radio.write(&data2, sizeof(data2));
  vTaskDelay(1000);
}


//example of freertos code with idle task









