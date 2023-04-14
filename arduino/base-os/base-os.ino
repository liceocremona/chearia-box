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

#include "secret.h"//WiFi Password and API Key
#include "constant.h"//Constanti non importanti per la sicurezza

/*
Costanti presenti nei file ".h":
API_SERVER: Il dominio dove sono presente le api usate per caricare i dati sul db
SSL_CERTIFICATE: Chiave pubblica del certificato ssl del server, necessario per la connessione con https
KEY: Token per autenticare le richieste alle api, da inserire nel body della richiesta
WIFI_SSID: Nome della WiFi a cui connettersi
WIFI_PASSWORD: Password della WiFi

*/


#define ARDUINOJSON_USE_DOUBLE 0 //arduinojson setting

String key = KEY;

const char *rootSSLCertificate = SSL_CERTIFICATE;

String api_server_url = "https://" + API_SERVER

QueueHandle_t xDatasQueue; //queue usata per passare i dati attraverso i task

WiFiMulti WiFiMulti;

//led indicativi CORE0
#define LED_CORE0a 32
#define LED_CORE0b 33


//led indicativi CORE1
#define LED_CORE1a 34
#define LED_CORE1b 35



//INPUT TASK 
//questi task devono girare sul core 0

void radioTask(void *pvParameters){
  //Controlla constantemente se arrivano dati dal modulo radio e li inserisce nella queue
}


//OUTPUT TASK
//questi task devono girare sul core 1
void uploadTask(void *pvParameters){
  //Prende i dati dalla queue e li li inserisce sul DB con una richiesta alle API
  
}

void sdcardTask(void *pvParameters) {
  //TO DO in future
  //Prende i dati dalla queue e li salva su una scheda SD
}


void setup() {
  Serial.begin(115200);

}
