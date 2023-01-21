#ifndef __STATE_SAVER_H__
#define __STATE_SAVER_H__

#include <stdint.h>
#include <map>

enum class SEGMENT
{
    SYSTEM_INFO = 0,
    CHANNEL_CMDS = 1,
    USER_MODES = 2,
    NUM_MEMORY_SEGMENTS =3


};

enum class MEMORY_ERR{
    OK =0,
    SEGMENT_OUT_OF_BOUNDS =1,
    OUT_OF_SLOTS =2,
    SLOT_OUT_OF_BOUNDS =3
};

typedef struct
{
    uint16_t MEMORY_START;
    uint16_t MEMORY_END;
    uint16_t MEMORY_SIZE;
    uint16_t SLOT_SIZE;
    uint16_t NUM_SLOTS;
}MemoryMap_t;

class MemoryHandler
{
public:
   
    MEMORY_ERR saveData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen);
    MEMORY_ERR loadData(SEGMENT seg, uint16_t pos, uint8_t *data, uint16_t dataLen);
    static MemoryHandler * getInstance(std::map<SEGMENT, MemoryMap_t> memory);

private:
    static MemoryHandler* memoryHandler;
    std::map<SEGMENT, MemoryMap_t> MEMORY_MAP;
     MemoryHandler(std::map<SEGMENT, MemoryMap_t> MemoryMap);
    ~MemoryHandler();
    MEMORY_ERR checkValidity(SEGMENT seg, uint16_t pos, uint16_t dataLen);

};

#endif