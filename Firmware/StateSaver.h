#ifndef __STATE_SAVER_H__
#define __STATE_SAVER_H__

#include <stdint.h>

class StateSaver{
public:
    StateSaver();
    ~StateSaver();
    bool loadState(uint8_t channel);
    bool loadStates();
    void saveState(uint8_t chanel, uint8_t *message,uint8_t msgLen);
private:
    const uint8_t DATA_PACKET_SIZE =20;
    const uint8_t EEPROM_START_ADDRESS = 0;
};

#endif