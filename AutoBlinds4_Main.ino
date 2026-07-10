#include <AutoBlinds_Recv.h>
#define QUEUE_SIZE 1
// Create an handle for the queue
QueueHandle_t command1 = NULL;
QueueHandle_t command2 = NULL;
QueueHandle_t command3 = NULL;
QueueHandle_t command4 = NULL;

const uint8_t ID = 1;

Quadrant Q1(25, 26); 
Quadrant Q2(27, 16); 
Quadrant Q3(23, 19);
Quadrant Q4(18, 17);
AutoBlinds_Recv Reciver; 

bool Open1 = false;
bool Open2 = false;
bool Open3 = false;
bool Open4 = false;

void Q1_Handler(void *parameter) {
  while (1) {
    Opperation commandType = IDLE; ; 
    xQueueReceive(command1, &commandType, 0);
    Serial.print("commandType1: "); 
    Serial.println(commandType);

    if (commandType == CLOSE) {
      Q1.moveTo(CLOSE);
      Open1 = false;
    }
    else if (commandType == OPEN90) {
      Q1.moveTo(OPEN90);
      Open1 = true;
    }
    else if (commandType == CLOSE45) {
      Q1.moveTo(CLOSE45);
      Open1 = true;
    }
    else if (commandType == OPEN) {
      Q1.moveTo(OPEN);
      Open1 = true;
    }
    vTaskDelay(15);
    Q1.setManual();
  }
}

void Q2_Handler(void *parameter) {
  while (1) {
    Opperation commandType = IDLE; 
    xQueueReceive(command2, &commandType, 0);
    Serial.print("commandType2: "); 
    Serial.println(commandType);
     
    if (commandType == CLOSE) {
      Q2.moveTo(CLOSE);
      Open1 = false;
    }
    else if (commandType == OPEN90) {
      Q2.moveTo(OPEN90);
      Open1 = true;
    }
    else if (commandType == CLOSE45) {
      Q2.moveTo(CLOSE45);
      Open1 = true;
    }
    else if (commandType == OPEN) {
      Q2.moveTo(OPEN);
      Open1 = true;
    }
    vTaskDelay(15);
    Q3.setManual();
  }
}

void Q3_Handler(void *parameter) {
  while (1) {
    Opperation commandType = IDLE;  
    xQueueReceive(command3, &commandType, 0);
    Serial.print("commandType3: "); 
    Serial.println(commandType);
     
    if (commandType == CLOSE) {
      Q3.moveTo(CLOSE);
      Open1 = false;
    }
    else if (commandType == OPEN90) {
      Q3.moveTo(OPEN90);
      Open1 = true;
    }
    else if (commandType == CLOSE45) {
      Q3.moveTo(CLOSE45);
      Open1 = true;
    }
    else if (commandType == OPEN) {
      Q3.moveTo(OPEN);
      Open1 = true;
    }
    vTaskDelay(15);
    Q3.setManual();
  }
}

void Q4_Handler(void *parameter) {
  while (1) {
    Opperation commandType = IDLE; ; 
    xQueueReceive(command4, &commandType, 0);
    Serial.print("commandType4: "); 
    Serial.println(commandType);
     
    if (commandType == CLOSE) {
      Q4.moveTo(CLOSE);
      Open1 = false;
    }
    else if (commandType == OPEN90) {
      Q4.moveTo(OPEN90);
      Open1 = true;
    }
    else if (commandType == CLOSE45) {
      Q4.moveTo(CLOSE45);
      Open1 = true;
    }
    else if (commandType == OPEN) {
      Q3.moveTo(OPEN);
      Open1 = true;
    }
    vTaskDelay(15);
    Q4.setManual();
  }
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Reciver.setDataFromIncoming(incomingData);
  if (Reciver.getID() == ID) {
    Opperation opperation1 = Reciver.getCommand1();
    Opperation opperation2 = Reciver.getCommand2();
    Opperation opperation3 = Reciver.getCommand3();
    Opperation opperation4 = Reciver.getCommand4();
    xQueueSend(command1, &opperation1, 0);
    xQueueSend(command2, &opperation2, 0);
    xQueueSend(command3, &opperation3, 0);
    xQueueSend(command4, &opperation4, 0);
  }
}

void ESPNOW_Handler(void *parameter) {
  WiFi.mode(WIFI_STA);
  Serial.print("STA MAC: ");
  Serial.println(WiFi.macAddress());
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
  command2 = xQueueCreate(QUEUE_SIZE, sizeof(uint16_t));
  command3 = xQueueCreate(QUEUE_SIZE, sizeof(uint16_t));
  command4 = xQueueCreate(QUEUE_SIZE, sizeof(uint16_t));
  if (command1 == NULL || command2 == NULL || command3 == NULL || command4 == NULL) {
    Serial.println("Failed to create queue!");
    while (1);
  }
  // Create threads
  xTaskCreatePinnedToCore(
    ESPNOW_Handler,
    "ESPNOWThread",
    4096,  // Task stack
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
    Q2_Handler,
    "Q2Thread",
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

  xTaskCreatePinnedToCore(
    Q4_Handler,
    "Q4Thread",
    2000,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  
}