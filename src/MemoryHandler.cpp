#include "MemoryHandler.h"

// Library Includes
#include <EEPROM.h>
#include <stdint.h>
#include <stdbool.h>
#include <map>

// Declaring an instance of Memory Handler
MemoryHandler *MemoryHandler::instance = nullptr;

MemoryHandler::MemoryHandler(std::map<SEGMENT, MemoryMap_t> memory)
    : MEMORY_MAP(memory)
{
}
MemoryHandler::~MemoryHandler()
{
}
MEMORY_ERR MemoryHandler::saveData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen)
{
  uint16_t saveAddress = MEMORY_MAP[seg].MEMORY_START + MEMORY_MAP[seg].SLOT_SIZE * pos;
  MEMORY_ERR error = checkValidity(seg, pos, dataLen);
  if (error == MEMORY_ERR::OK)
  {
    for (uint16_t i = 0; i < dataLen; i++)
    {
      if (i > static_cast<uint16_t>(MEMORY_MAP[seg].MEMORY_END))
      {
        return MEMORY_ERR::SEGMENT_OUT_OF_BOUNDS;
      }
      EEPROM.update(saveAddress + i, data[i]);
    }
  }

  return error;
}

MEMORY_ERR MemoryHandler::loadData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen)
{

  uint16_t loadAddress = MEMORY_MAP[seg].MEMORY_START + MEMORY_MAP[seg].SLOT_SIZE * pos;
  MEMORY_ERR error = checkValidity(seg, pos, dataLen);

  if (error == MEMORY_ERR::OK)
  {
    for (uint16_t i = 0; i < dataLen; i++)
    {
      if (i > static_cast<uint16_t>(MEMORY_MAP[seg].MEMORY_END))
      {
        return MEMORY_ERR::SEGMENT_OUT_OF_BOUNDS;
      }
      EEPROM.get(loadAddress + i, data[i]);
    }
  }
  return error;
}

MEMORY_ERR MemoryHandler ::checkValidity(SEGMENT seg, uint16_t pos, uint16_t dataLen)
{
  if (pos > MEMORY_MAP[seg].NUM_SLOTS)
  {
    return MEMORY_ERR::OUT_OF_SLOTS;
  }
  else if (dataLen > MEMORY_MAP[seg].SLOT_SIZE)
  {
    return MEMORY_ERR::SLOT_OUT_OF_BOUNDS;
  }
  return MEMORY_ERR::OK;
}

MemoryHandler *MemoryHandler::getInstance(std::map<SEGMENT, MemoryMap_t> memory)
{
  if (MemoryHandler::instance == nullptr)
  {
    MemoryHandler::instance = new MemoryHandler(memory);
  }
  return instance;
}

MemoryHandler *MemoryHandler::getInstance()
{

  if (MemoryHandler::instance == nullptr)
  {
    return nullptr;
  }
  return instance;
}
