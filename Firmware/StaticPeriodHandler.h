#ifndef __STATICPERIODHANDLER__H
#define __STATICPERIODHANDLER__H


//Library Includes
#include <stdint.h>

//Project Includes
#include "AbstractUserModeHandler.h"
#include "LEDDriver.h"

class StaticPeriodHandler : AbstractUserModeHandler
{

public:
    StaticPeriodHandler(LEDDriver *driver, uint8_t *bufferIn, uint8_t bufferLength);
    ~StaticPeriodHandler() final;
    void loop() final;

private:
    
};

#endif