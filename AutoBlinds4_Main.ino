#include <Quadrant.h>
#include <AutoBlinds_Recv.h>
#define QUEUE_SIZE 1
// Create an handle for the queue
QueueHandle_t command1 = NULL;
QueueHandle_t command3 = NULL;

Quadrant Q1(19, 4); 
Quadrant Q3(5, 18);
AutoBlinds_Recv Reciver(1);

bool Open1 = false;
bool Open3 = false;

void Q1_Handler(void *parameter) {
  while (1) {
    uint16_t commandType = 0; 
    xQueueReceive(command1, &commandType, 0);
    Serial.print("commandType: "); 
    Serial.println(commandType); 
    if (commandType == 1) {
      if (Open1) {
        Q1.moveTo(CLOSE);
      }
      else {
        Q1.moveTo(OPEN90);
      }
      Open1 = !Open1;
      Q1.setManual();
    }
    else if (commandType == 2) {
      Q1.moveTo(CLOSE45);
      Open1 = true;
      Q1.setManual();
    }
    else if (commandType == 3) {
      Q1.moveTo(OPEN);
      Open1 = true;
      Q1.setManual();
    }
    vTaskDelay(15);
  }
}

void Q3_Handler(void *parameter) {
  while (1) {
    uint16_t commandType = 0;
    xQueueReceive(command3, &commandType, 0);
    if (commandType == 1) {
      if (Open3) {
        Q3.moveTo(CLOSE);
      }
      else {
        Q3.moveTo(OPEN90);
      }
      Open3 = !Open3;
      Q3.setManual();
    }
    else if (commandType == 2) {
      Q3.moveTo(CLOSE45);
      Open3 = true;
      Q3.setManual();
    }
    else if (commandType == 3) {
      Q3.moveTo(OPEN);
      Open3 = true;
      Q3.setManual();
    }
    vTaskDelay(15);
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Reciver.setDataFromIncoming(incomingData);
  if (Reciver.getID() == Reciver.getButtonNum()) {
    int clicks = Reciver.getNumClicks();
    xQueueSend(command1, &clicks, 0);
    xQueueSend(command3, &clicks, 0);
    Serial.print("setting click: ");
    Serial.println(clicks);
  }
}

void ESPNOW_Handler(void *parameter) {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  Serial.println("ESP-NOW ready");
  while (1) {
    vTaskDelay(100);
  }
}

void setup() {
  Serial.begin(115200);
  command1 = xQueueCreate(QUEUE_SIZE, sizeof(uint16_t));
  command3 = xQueueCreate(QUEUE_SIZE, sizeof(uint16_t));
  if (command1 == NULL || command3 == NULL) {
    Serial.println("Failed to create queue!");
    while (1);
  }
  // Create threads
  xTaskCreatePinnedToCore(
    ESPNOW_Handler,
    "ESPNOWThread",
    2000,  // Task stack
    NULL,
    1,
    NULL,
    0  // Core 0
  );

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