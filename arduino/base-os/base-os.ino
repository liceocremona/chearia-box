#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
//INPUT TASK
void radioTask(void *pvParameters){
  //This fucntion receive datas from radio and insert them in a queue
}
//OUTPUT TASK
void uploadTask(void *pvParameters){
  //This function take data from queue and send them to api server
  
}

void sdcardTask(void *pvParameters) {
  //This function take data from queue and save them on sdcard
}
