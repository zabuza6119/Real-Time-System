#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

void testTask(void *parameter){
  while(1){
    int a = 1;
    int b[100];

    for (int i=0; i < 100; i++){
      b[i] = a + 1;
    }
    Serial.println(b[0]);
    Serial.print("High water mark (words):");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    Serial.print("Heap before malloc (bytes):");
    Serial.println(xPortGetFreeHeapSize());
    int *ptr = (int*)pvPortMalloc(1024*sizeof(int));

    for (int i=0; i < 1024; i++){
      ptr[i] = 3;
    }

    Serial.print("High after malloc (bytes):");
    Serial.println(xPortGetFreeHeapSize());

    vPortFree(ptr);
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  
  }
}

void setup() {
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("----FreeRTOS Memory Demo---");
  
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            testTask,      // Function to be called
            "Test Task",   // Name of task
            1500,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
            
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
