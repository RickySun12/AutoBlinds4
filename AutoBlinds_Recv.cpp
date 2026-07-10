#include <AutoBlinds_Recv.h> 

AutoBlinds_Recv::AutoBlinds_Recv() {}

void AutoBlinds_Recv::setDataFromIncoming(const uint8_t *incomingData) {
  memcpy(&packet, incomingData, sizeof(packet));
}

Opperation AutoBlinds_Recv::getCommand1() {
  return  this->packet.command1;
}

Opperation AutoBlinds_Recv::getCommand2() {
  return this->packet.command2;
}

Opperation AutoBlinds_Recv::getCommand3() {
  return  this->packet.command3;
}

Opperation AutoBlinds_Recv::getCommand4() {
  return  this->packet.command4;
}

uint8_t AutoBlinds_Recv::getID() {
  return  this->packet.blindsID;
}