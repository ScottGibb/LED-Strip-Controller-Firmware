#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H

#include <stdint.h>

class ICommunicator{

    public:
    virtual bool loop(uint8_t* buff, uint8_t len) =0;
    virtual void transmit(uint8_t *buff, uint8_t len) =0;
};

#endif