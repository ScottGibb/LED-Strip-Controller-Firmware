#ifndef __STATE_SAVER_H__
#define __STATE_SAVER_H__

#include "STM32F103C8T6MemoryMap.h"
#include <stdint.h>

enum class Segment{
    SYSTEM_INFO = 0,
    CHANNEL_CMDS =1,
    USER_MODES =2

};

class MemoryHandler{
public:
    MemoryHandler();
    ~MemoryHandler();
    bool saveData(Segment seg, uint8_t pos,uint8_t *data, uint8_t dataLen);
    bool loadData(Segment seg, uint8_t pos,uint8_t *data, uint8_t dataLen);

private:
};

#endif