#include "StaticPeriodHandler.h"

// Project Includes
#include "LEDDriver.h"

// System Includes
#include <stdint.h>

StaticPeriodHandler::StaticPeriodHandler(LEDDriver *driver, uint8_t *bufferIn, uint32_t bufferLength)
    : AbstractUserModeHandler(driver, bufferIn, bufferLength)
{
}
StaticPeriodHandler::~StaticPeriodHandler()
{
}
void StaticPeriodHandler::loop()
{
}