#include <esp_now.h>
#include <WiFi.h>

struct Packet {
  int buttonNum;
  int numClicks;
  // add alarm infomation later
};

class AutoBlinds_Recv {
  public: 
    AutoBlinds_Recv(int blindsID);
    void setData(Packet Packet);
    void setDataFromIncoming(const uint8_t *incomingData);
    int getNumClicks(); 
    int getButtonNum();
    int getID();
  private:
    int blindsID; 
    Packet packet;
};