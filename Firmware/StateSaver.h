#ifndef __STATE_SAVER_H__
#define __STATE_SAVER_H__

#include <stdint.h>

class StateSaver{
public:
    void saveBytes(uint8_t address, uint8_t *data, uint8_t dataLen);
   void loadBytes(uint8_t address, uint8_t* data, uint8_t dataLen);
private:
};

#endif