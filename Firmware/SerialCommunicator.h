
#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

//Library Includes
#include <stdint.h>

//Project Includes

#include "ICommunicator.h"

class SerialCommunicator: public ICommunicator{
    public:
    SerialCommunicator(uint32_t BAUDRATE);
    ~SerialCommunicator();
    bool loop(uint8_t* buff, uint8_t len);
    void transmit(uint8_t *buff, uint8_t len);
    private:
    const uint32_t BAUDRATE;

};
#endif