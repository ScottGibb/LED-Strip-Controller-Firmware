#include "UserModeSelector.h"

// Library Includes
#include <stdint.h>

// Project Includes
#include "StaticPeriodHandler.h"
#include "LEDDriver.h"

UserModeSelector::UserModeSelector(LEDDriver *driver)
    : driver(driver)
{
    controlFlag = false;
    handler = nullptr;
    mode = MEMORY_MODE::NOT_SELECTED;
}
UserModeSelector::~UserModeSelector()
{
    delete handler;
}
void UserModeSelector::loop()
{
    if (controlFlag)
    {
        handler->loop();
    }
}
bool UserModeSelector::start()
{
    if (mode != MEMORY_MODE::NOT_SELECTED && handler != nullptr)
    {
        controlFlag = false;
        return true;
    }
    return false;
}
void UserModeSelector::stop()
{
    controlFlag = false;
}

void UserModeSelector::setMode(MEMORY_MODE memMode, uint8_t *buffer, uint32_t length)
{
    // Kill existing handler
    delete handler;
    handler = nullptr;
    controlFlag = false; // Stop Loop from running
    mode = memMode;

    // Create new Handler
    switch (mode)
    {
    case MEMORY_MODE::STATIC_MODE:
        handler = new StaticPeriodHandler(driver, buffer, length);
        break;
    case MEMORY_MODE::DYNAMIC_MODE:
        break;
    default:
        mode = MEMORY_MODE::NOT_SELECTED;
        delete handler;
        handler = nullptr;
    }
}
