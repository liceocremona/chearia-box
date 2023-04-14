#include <Arduino.h>
#include "secret.h"
#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define ARDUINOJSON_USE_DOUBLE 0
String key = KEY;



const char *rootCACertificate =
  "-----BEGIN CERTIFICATE-----\n"
  \ 
"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\n"
  \ 
"-----END CERTIFICATE-----\n";





#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// define two tasks for Blink & AnalogRead
void TaskBlink(void *pvParameters);
void TaskAnalogReadA3(void *pvParameters);
QueueHandle_t xQueue;

WiFiMulti WiFiMulti;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  ////////Serial.println();
  ////////Serial.println();
  ////////Serial.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  // wait for WiFi connection
  Serial.print("Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

  xQueue = xQueueCreate(6, 10);
  // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    TaskBlink, "TaskBlink"  // A name just for humans
    ,
    1024 * 10  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 200  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL, 0);

  xTaskCreatePinnedToCore(
    TaskAnalogReadA3, "AnalogReadA3", 1024 *64  // Stack size
    ,
    NULL, 200  // Priority
    ,
    NULL, 1);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void)pvParameters;

  /*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
    
  If you want to know what pin the on-board LED is connected to on your ESP32 model, check
  the Technical Specs of your board.
*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)  // A Task shall never return or exit.
  {
    Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());


    //Serial.println("task 1");
    char data_code[10] = "69-itwork";
    xQueueSendToBack(xQueue, &data_code, 0);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void TaskAnalogReadA3(void *pvParameters)  // This is a task.
{
  (void)pvParameters;

  /*
  AnalogReadSerial
  Reads an analog input on pin A3, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A3, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
  WiFiClientSecure *client2 = new WiFiClientSecure;
  if (client2) {
    client2->setCACert(rootCACertificate);


    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
    HTTPClient https;
    https.setReuse(true);
    //Serial.print("[HTTPS] begin...\n");

    if (https.begin(*client2, "https://api.progettochearia.it")) {  // HTTPS
      for (;;) {
        Serial.println("pass1");
        Serial.print("Task2 running on core ");
        Serial.println(xPortGetCoreID());
        int queue_item = uxQueueMessagesWaiting(xQueue);

        if (queue_item > 0) {
          Serial.println("var1");
          char r_value[10];
          xQueueReceive(xQueue, &r_value, 0);
          //Serial.print("receive: ");
          //Serial.println(r_value);

          String Data = "9069";
          String dataName = "itwork";

          StaticJsonDocument<120> doc;              //creazione doc json per body  della richiesta http
          String contentType = "application/json";  //formato body http
          String body;
          doc["key"] = key;  // aggiunta dati al doc json
          doc["datavalue"] = Data;
          serializeJson(doc, body);  //conversione del doc json in String
          String req_path = "/v1/board/putdata/" + dataName;
          //Serial.println(body);
          //Serial.print("faccio una richiesta a: ");
          //Serial.println(req_path);
          https.setURL(req_path);

          //Serial.print("[HTTPS] PUT...\n");
          // start connection and send HTTP header
          int httpCode = https.PUT(body);
          Serial.println("var2");

          // httpCode will be negative on error
          
        }

        Serial.println("pass2");
        vTaskDelay(15 / portTICK_PERIOD_MS);
        Serial.println("pass3");
      }
     
    } 

  }

  
}
