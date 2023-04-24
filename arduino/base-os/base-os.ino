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

#define ARDUINOJSON_USE_DOUBLE 0  // arduinojson setting

String key = KEY;  // Chiave autenticazione API

const char *rootCACertificate =  // certificato publico ssl
  "-----BEGIN CERTIFICATE-----\n"
  \ 
"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\n"
  \ 
"-----END CERTIFICATE-----\n";

String api_server = API_SERVER;
String api_server_url = String("https://" + api_server);  // URl del server delle API

QueueHandle_t xQueueDatas;  // queue usata per passare i dati attraverso i task

WiFiMulti WiFiMulti;  // oggetto per la gestione delle connessioni wifi

RF24 radio;                       // modulo radio
const byte address[6] = "00001";  // indirizzo del canale radio usato per la comunicazione

// led info CORE0
#define LED_CORE0a 32
#define LED_CORE0b 33

// led info CORE1
#define LED_CORE1a 34
#define LED_CORE1b 35

// CE e CSN del modulo Nrf24l01 per la radio
#define CE 4
#define CSN 5

bool wifi_conn = false;
bool radio_init = false;

// Struttura dati per i dati ricevuti dal modulo radio
struct receiveDataStruct {
  String data_name;
  float data_value;
};

receiveDataStruct parseData(String data) {
  receiveDataStruct data_structure;
  // Qesta funzione ottiene la String dalla funzione precedente e separa il valore dal nome del dato
  // Es. 22.8-temperature --> valore: 22.8 nome dato: temperature
  int char_len = data.length() + 1;                 // Lunghezza String
  char coded_data[char_len];                        // Creazione di un array di char pari alla lunghezza della String
  data.toCharArray(coded_data, char_len);           // Conversione della Strin in un array di char
  char *ch_measurement = strtok(coded_data, "-");   // Array di char contenente il valore
  char *data_name_ch = strtok(NULL, "-");           // Array di char contenente il nome del dato
  String str_measurement = String(ch_measurement);  // COnversione in Float
  float measurement = str_measurement.toFloat();
  String data_name = String(data_name_ch);
  data_structure.data_name = data_name;  // Inserimento dei dati nella struct
  data_structure.data_value = measurement;
  return data_structure;  // Ritorno della struct
}

// INPUT TASK
// questi task devono girare sul core 0

void radioTask(void *pvParameters);
// Controlla constantemente se arrivano dati dal modulo radio e li inserisce nella queue

// OUTPUT TASK
// questi task devono girare sul core 1
void uploadTask(void *pvParameters);
// Prende i dati dalla queue e li li inserisce sul DB con una richiesta alle API

void sdcardTask(void *pvParameters);
// TO DO in future
// Prende i dati dalla queue e li salva su una scheda SD

void setup() {
  Serial.begin(115200);

  while (!wifi_conn) {  // connessione alla rete WiFi
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    // wait for WiFi connection
    Serial.print("Waiting for WiFi to connect...");
    while ((WiFiMulti.run() != WL_CONNECTED)) {
      Serial.print(".");
    }
    Serial.println(" connected");
    wifi_conn = true;
  }

  if (!radio_init) {              // inizializzazione del modulo radio
    if (!radio.begin(CE, CSN)) {  // CE, CSN
      Serial.println("La radio non funziona");
      while (1) {
        Serial.println("La radio non funziona");
      }  // hold program in infinite loop to prevent subsequent errors
    }
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
    radio_init = true;
  }

  xQueueDatas = xQueueCreate(6, 20);  // creazione di Queue di 6 elementi di 20 byte ciascuno

  // creazione dei task radio
  xTaskCreatePinnedToCore(
    radioTask, "radioTask"  // Nome del task
    ,
    1024 * 10  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL, 1);

  // creazione dei task upload
  xTaskCreatePinnedToCore(
    uploadTask, "uploadTask", 1024 * 64  // Stack size
    ,
    NULL, 3  // Priority
    ,
    NULL, 0);
}

void loop() {  // Non viene usato da RTOS
}

void radioTask(void *pvParameters) {
  (void)pvParameters;

  for (;;) {

    if (radio.available())  //Quando è diasponibile un pacchetto
    {
      Serial.print("Radio task running on core ");
      Serial.println(xPortGetCoreID());
      char data[20];
      radio.read(&data, sizeof(data));  //riceve il dato nel formato valore-nome
      Serial.println(data);
      xQueueSendToBack(xQueueDatas, &data, 0);  // Inserisce il dato nella queue
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void uploadTask(void *pvParameters) {

  (void)pvParameters;

  WiFiClientSecure *client = new WiFiClientSecure;
  if (client) {
    client->setCACert(rootCACertificate);

    HTTPClient https;  //crea il client http
    https.setReuse(true);

    if (https.begin(*client, api_server_url))  //connessione permanente server delle API
    {
      for (;;) {
        Serial.print("uploadTask running on core ");
        Serial.println(xPortGetCoreID());
        int queue_items = uxQueueMessagesWaiting(xQueueDatas);  //numero di elementi nella queue

        if (queue_items > 0)  //se maggiore di 0 è arrivato un dato
        {
          char data_string[20];
          xQueueReceive(xQueueDatas, &data_string, 0);  //prende il dato dalla queue
          String data_string_Str = String(data_string);
          receiveDataStruct data_parsed;
          data_parsed = parseData(data_string_Str);  //conversione del dato nella struct

          StaticJsonDocument<120> doc;              // creazione doc json per body  della richiesta http
          String contentType = "application/json";  // formato body http
          String body;
          doc["key"] = key;  // aggiunta dati al doc json
          doc["datavalue"] = data_parsed.data_value;
          serializeJson(doc, body);  // conversione del doc json in String
          String req_path = "/v1/board/putdata/" + data_parsed.data_name;
          Serial.println(body);
          Serial.print("faccio una richiesta a: ");
          Serial.println(req_path);

          https.setURL(req_path);          //import l'url sul nome del dato
          int httpCode = https.PUT(body);  //invio dato al server
          Serial.println(httpCode);
          vTaskDelay(50 / portTICK_PERIOD_MS);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
    }
  }
}