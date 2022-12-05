## Arduino Test

Prima versione del firmware della scatola

Codici di test delle board progettate 

[**docs**](../docs/hardware/index.md)

- fly-box_device-test: Testa la voard posizionata nella scatola, inizializza tutti i sensori e controlla se la partenza va bene

- base_test: Inizialliza la base testando la comunicazione tra le due MCU e esegue delle richieste http in loop al server. 

- ## Configurazione

- Inserire le credenziali nei file `secret.h`
  
  ```
  #define WIFI_SSID ""  //inserire il nome della WiFi
  #define WIFI_PASSWORD ""  //inserire la password della WiFi
  #define KEY "" //inserire la chiave di autenticazione per le richieste HTTP alle API
  ```