#ifndef __IMODEHANDLER__H
#define __IMODEHANDLER__H

#include <stdint.h>

#include "LEDDriver.h"
class IModeHandler
{
public:
    virtual void loop() = 0;
};

#endif