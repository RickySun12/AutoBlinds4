#include <AutoBlinds_Recv.h> 

AutoBlinds_Recv::AutoBlinds_Recv(int blindsID) {
  this->blindsID = blindsID;
}

void AutoBlinds_Recv::setData(Packet packet) {
  this->packet.buttonNum = packet.buttonNum;
  this->packet.numClicks = packet.numClicks;
}

void AutoBlinds_Recv::setDataFromIncoming(const uint8_t *incomingData) {
  memcpy(&packet, incomingData, sizeof(packet));
}

int AutoBlinds_Recv::getNumClicks() {
  return packet.numClicks;
}

int AutoBlinds_Recv::getButtonNum() {
  return packet.buttonNum;
}

int AutoBlinds_Recv::getID() {
  return blindsID;
}