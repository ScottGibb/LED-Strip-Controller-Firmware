#include "UserModeSelector.h"

UserModeSelector::UserModeSelector(LEDDriver *driver)
:driver(driver)
{
    controlFlag =false;
    handler = nullptr;
    mode = MEMORY_MODE::NOT_SELECTED;

}
UserModeSelector::~UserModeSelector()
{
    delete handler;
}
void UserModeSelector:: loop()
{
    if(controlFlag){
        handler->loop();
    }
}
bool UserModeSelector:: start()
{
    if(mode != MEMORY_MODE::NOT_SELECTED && handler != nullptr){
        controlFlag = false;
        return true;
    }
    return false;
}
void UserModeSelector:: stop()
{
    controlFlag =false;

}

void UserModeSelector::setMode(MEMORY_MODE memMode, uint8_t *buffer, uint8_t length){
    mode = memMode;
    switch (mode)
    {
    case MEMORY_MODE::STATIC_MODE:
        break;
     case MEMORY_MODE::DYNAMIC_MODE:
        break;
    default:
        mode = MEMORY_MODE::NOT_SELECTED;
        delete handler;
        handler = nullptr;
    }
}
