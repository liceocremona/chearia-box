/*
Author: Nicolò Valenza, Carlo Incerti, Alessandro Finetti
Date of creation: 04-2023
LICENSE: GPL-3.0

*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "secret.h"    //WiFi Password and API Key
#include "constant.h"  //Constanti non importanti per la sicurezza

/*
Costanti presenti nei file ".h":
API_SERVER: Il dominio dove sono presente le api usate per caricare i dati sul db
SSL_CERTIFICATE: Chiave pubblica del certificato ssl del server, necessario per la connessione con https
KEY: Token per autenticare le richieste alle api, da inserire nel body della richiesta
WIFI_SSID: Nome della WiFi a cui connettersi
WIFI_PASSWORD: Password della WiFi

*/

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#define ARDUINOJSON_USE_DOUBLE 0  //arduinojson setting

String key = KEY;

const char *rootSSLCertificate = SSL_CERTIFICATE;

String api_server_url = "https://" + API_SERVER

                          QueueHandle_t xDatasQueue;  //queue usata per passare i dati attraverso i task

WiFiMulti WiFiMulti;

RF24 radio;  // CE, CSN
const byte address[6] = "00001";


//led indicativi CORE0
#define LED_CORE0a 32
#define LED_CORE0b 33


//led indicativi CORE1
#define LED_CORE1a 34
#define LED_CORE1b 35


//CE e CSN per la comunicazione radio

#define CE 26
#define CSN 25



//INPUT TASK
//questi task devono girare sul core 0

void radioTask(void *pvParameters);
//Controlla constantemente se arrivano dati dal modulo radio e li inserisce nella queue



//OUTPUT TASK
//questi task devono girare sul core 1
void uploadTask(void *pvParameters);
//Prende i dati dalla queue e li li inserisce sul DB con una richiesta alle API



void sdcardTask(void *pvParameters);
//TO DO in future
//Prende i dati dalla queue e li salva su una scheda SD



void setup() {
  Serial.begin(115200);

  if (!radio.begin(CE, CSN)) {
    Serial.println("La radio non funziona");
    while (1) { Serial.println("La radio non funziona"); }  // hold program in infinite loop to prevent subsequent errors
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();


  xQueueDatas = xQueueCreate(6, 10);

  xTaskCreatePinnedToCore(
    radioTask, "radioTask"  // A name just for humans
    ,
    1024 * 10  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 200  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL, 0);

  xTaskCreatePinnedToCore(
    uploadTask, "uploadTask", 1024 * 64  // Stack size
    ,
    NULL, 200  // Priority
    ,
    NULL, 1);
}

void loop() {
}

void radioTask(void *pvParameters) {

  (void)pvParameters;

  for ( ; ; ) {
    Serial.println("Ascoltando sul canale radio...");
   if (radio.available()) {
    char data[32] = "";
    radio.read(&data, sizeof(data));
    Serial.println(data);
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
   }
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}
