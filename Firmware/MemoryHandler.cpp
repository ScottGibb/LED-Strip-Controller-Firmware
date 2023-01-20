#include "MemoryHandler.h"

#include <EEPROM.h>
#include <stdbool.h>


MemoryHandler::MemoryHandler(){

}
MemoryHandler::~MemoryHandler(){
  
}
bool MemoryHandler::saveData(Segment seg, uint8_t pos, uint8_t *data, uint8_t dataLen) {
    return false;
}

bool MemoryHandler::loadData(Segment seg, uint8_t pos, uint8_t *data, uint8_t dataLen)
{
  return false;
}