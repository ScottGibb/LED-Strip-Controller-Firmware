#ifndef __ABSTRACTUSERMODEHANDLER__H
#define __ABSTRACTUSERMODEHANDLER__H


#include <stdint.h>

#include "IModeHandler.h"
#include "LEDDriver.h"

class AbstractUserModeHandler : IModeHandler
{

public:
    AbstractUserModeHandler(LEDDriver *driverIn, uint8_t *bufferIn, uint8_t bufferLength);
    virtual ~AbstractUserModeHandler();
    virtual void loop() = 0;

private:
    uint8_t *buffer;
    uint8_t length;
    LEDDriver *driver;
};

#endif