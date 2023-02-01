#ifndef __USERMODESELECTOR__H
#define __USERMODESELECTOR__H

#include "LEDDriver.h"
#include "IModeHandler.h"

enum class MEMORY_MODE{
    STATIC_MODE =0,
    DYNAMIC_MODE =1,
    NOT_SELECTED =2
};

class UserModeSelector{
    public:
    UserModeSelector(LEDDriver *driver);
    ~UserModeSelector();
    void loop();
    bool start();
    void stop();
    void setMode(MEMORY_MODE memMode, uint8_t *buffer, uint8_t length);

    private:
    LEDDriver * driver;
    IModeHandler *handler;
    bool controlFlag;
    MEMORY_MODE mode;
    

};


#endif