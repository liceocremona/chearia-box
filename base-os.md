## Nomi

- #### CheOS 
  Sembra un os cinese, anzi probabiblmente esiste
  
- #### base-os
  banale
  
  
## Struttura
Task divisibili in due categorie: 
- Task di Input:
  questi ricevono i dati da:
    - Sensori
    - Sistemi di comunicazione (es i2c, radio 2.4)
    - Eventuali input fisici (es pulsanti)
    
  dopo aver ricevuto il dato lo elaborano e lo inseriscono all'interno di una queue o un'altra struttura dati che ne permetta il trasferimento ad altri task
- Task di Output
  questi prendono il dato dalla queue, lo valutano e ne restituiscono le eventuali conseguenze:
  - Invio del dato(es via radio, via http)
  - Esecuzione di un azione in base a quel dato (es acensione di un led, azione di un motore)
  


## Description
Lo scopo sarebbe creare una "framework/os" usabile nei progetti legati alla raccolta dati e dove e necessario gestire diversi input di diverso tipo e rispondere con un output in tempi brevi, quindi in pratica l'idea è di usarlo sui seguenti sistemi:
- Pallone aerostatici, sia per la box attaccata sul pallone, sia per un eventuale ricevente situata a terra.
- Razzi sonda, per il computer di volo, situazione più complessa poichè è necessario gestire un input e un clock con una frequenza veramente alta 

