//freertos test1
#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <MQUnifiedsensor.h>
#include <MQGas.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

Adafruit_BMP085 bmp;
MQGas mq7(MQ7);

int data1 = 0;
int data2 = 0;
int data3 = 0;
int data4 = 0;

void task1(void *pvParameters) {
  for (;;) {
    data1 = bmp.readTemperature();
    data2 = bmp.readPressure();
    Serial.println(data1);
    Serial.println(data2);
    vTaskSuspend(NULL);
  }
}

void task2(void *pvParameters) {
  for (;;) {
    data3 = mq7.readSensor();
    data4 = mq7.getPPM();
    Serial.println(data3);
    Serial.println(data4);
    vTaskSuspend(NULL);
  }
}


void idle(void *pvParameters) {
  for (;;) {
    radio.write(&data1, sizeof(data1));
    radio.write(&data2, sizeof(data2));
    radio.write(&data3, sizeof(data3));
    radio.write(&data4, sizeof(data4));
    vTaskDelay(5000);
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
  xTaskCreate(idle, "idle", 128, NULL, 1, NULL);
}

void loop() {
  vTaskResume(task1);
  vTaskResume(task2);
  vTaskDelay(1000);
}



