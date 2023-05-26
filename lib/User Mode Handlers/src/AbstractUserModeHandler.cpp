#include "AbstractUserModeHandler.h"

// Project Includes
#include "LEDDriver.h"

// System Includes
#include <stdint.h>
#include <string.h>

AbstractUserModeHandler::AbstractUserModeHandler(LEDDriver *driverIn, uint8_t *bufferIn, uint32_t bufferLength) :length(bufferLength) driver(driverIn)
{
    buffer = new uint8_t[bufferLength];
    memcpy(buffer, bufferIn, bufferLength);
}
AbstractUserModeHandler::~AbstractUserModeHandler()
{
    delete[] buffer;
}