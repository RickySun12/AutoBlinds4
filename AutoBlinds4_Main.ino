#include <Quadrant.h>
#define QUEUE_SIZE 2
// Create an handle for the queue
QueueHandle_t commandQueue = NULL;

Quadrant Q1(2, 4); 
Quadrant Q3(5, 18);

void Q1_Handler(void *command) {
 while (1) {
    Q1.moveTo(CLOSE45); 
    vTaskDelay(1000);
  }
}

void Q3_Handler(void *command) {
  while (1) {
    Q3.moveTo(OPEN90);
    vTaskDelay(1000); 
  }
}

void setup() {
  Serial.begin(115200);
  // Create threads
  xTaskCreatePinnedToCore(
    Q1_Handler,
    "Q1Thread",
    2000,  // Task stack
    NULL,
    1,
    NULL,
    1  // Core 1
  );

  xTaskCreatePinnedToCore(
    Q3_Handler,
    "Q3Thread",
    2000,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  
}