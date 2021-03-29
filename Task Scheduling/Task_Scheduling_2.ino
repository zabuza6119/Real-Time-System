

// Needed for atoi()
#include <stdlib.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

const char msg[] = "I Love Real Time System.";

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//Tasks

void startTask1(void *parameter){

  int msg_len = strlen(msg);

  while (1){
    Serial.println();
    for (int i = 0; i < msg_len; i++){
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void startTask2(void *parameter){

  while(1){
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup(){

  Serial.begin(300);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Task Demo---");
  Serial.print("Setup and loop task running on core");
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  xTaskCreatePinnedToCore(startTask1,
                          "Task 1",
                          1024,
                          NULL,
                          1,
                          &task_1,
                          app_cpu);

  xTaskCreatePinnedToCore(startTask2,
                          "Task 2",
                          1024,
                          NULL,
                          2,
                          &task_2,
                          app_cpu);
}

void loop(){

  for (int i = 0; i < 3 ; i++){
    vTaskSuspend(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  if (task_1 != NULL){
    vTaskDelete(task_1);
    task_1 = NULL;
    
  }

  
}
