#include "StateSaver.h"

#include <EEPROM.h>

StateSaver::StateSaver()
{
}

StateSaver::~StateSaver()
{
}

void StateSaver::saveBytes(uint8_t address, uint8_t *data, uint8_t dataLen){
    for (uint8_t i = 0; i < dataLen; i++) {
      EEPROM.write(address + i, data[i]);
    } 
}

 void StateSaver::loadBytes(uint8_t address, uint8_t* data, uint8_t dataLen) {
    for (uint8_t i = 0; i < dataLen; i++) {
      data[i] = EEPROM.read(address + i);
    }
 }