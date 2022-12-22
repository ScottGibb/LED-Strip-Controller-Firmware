#include "StateSaver.h"

#include <EEPROM.h>

StateSaver::StateSaver(){

}

StateSaver::~StateSaver(){

}

bool StateSaver::loadState(uint8_t channel){
  return false;
}

bool StateSaver::loadStates(){
  return false;
}

void StateSaver::saveState(uint8_t channel, uint8_t *message, uint8_t msgLen){
    if(msgLen> DATA_PACKET_SIZE){
        return; //Better Method for this?
    }
    uint8_t addressOffset = channel * DATA_PACKET_SIZE;
    for(uint8_t i =0; i < msgLen;i++){
        EEPROM.update(EEPROM_START_ADDRESS+addressOffset+i, message[i]);
    }
    for(uint8_t i = msgLen; i < DATA_PACKET_SIZE;i++){
        EEPROM.update(EEPROM_START_ADDRESS+addressOffset+i, 0);//pad rest of memory
    }

}