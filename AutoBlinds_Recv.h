#include <esp_now.h>
#include <WiFi.h>
#include <Quadrant.h>

struct Packet {
  uint8_t blindsID; 
  Opperation command1;
  Opperation command2;
  Opperation command3;
  Opperation command4;
};

class AutoBlinds_Recv {
  public: 
    AutoBlinds_Recv();
    void setDataFromIncoming(const uint8_t *incomingData);
    uint8_t getID();
    Opperation getCommand1();
    Opperation getCommand2();
    Opperation getCommand3();
    Opperation getCommand4();
  private:
    Packet packet;
};