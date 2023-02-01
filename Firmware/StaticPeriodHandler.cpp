#include "StaticPeriodHandler.h"

#include <stdint.h>

#include "LEDDriver.h"

StaticPeriodHandler::StaticPeriodHandler(LEDDriver *driver, uint8_t *bufferIn, uint8_t bufferLength)
: AbstractUserModeHandler(driver, bufferIn, bufferLength)
{

}
StaticPeriodHandler::~StaticPeriodHandler()
{
}
void StaticPeriodHandler:: loop()
{
}