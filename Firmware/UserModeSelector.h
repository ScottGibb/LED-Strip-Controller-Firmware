#ifndef __USERMODESELECTOR__H
#define __USERMODESELECTOR__H

// Library Includes
#include <stdint.h>

// Project Includes
#include "LEDDriver.h"
#include "IModeHandler.h"

/**
 * @brief MEMORY_MODE enum outlining the different ways the memory for user mode can be interpreted
 *
 */
enum class MEMORY_MODE
{
    STATIC_MODE = 0,
    DYNAMIC_MODE = 1,
    NOT_SELECTED = 2
};

/**
 * @brief UserModeSelector class responsible for calling the apropriate handler at a time to interpret the memory block and subsequently make the correct user defined pattern
 *
 */
class UserModeSelector
{
public:
    /**
     * @brief Construct a new User Mode Selector object
     *
     * @param driver the led channel for the user mode to be applied too
     */
    UserModeSelector(LEDDriver *driver);
    /**
     * @brief Destroy the User Mode Selector object
     *
     */
    ~UserModeSelector();
    /**
     * @brief Should be called in the main loop of the application
     *
     */
    void loop();
    /**
     * @brief Starts the user mode sequence, the user must call setMode before this for the system to work
     *
     * @return true if user mode sequence can be started
     * @return false if user mode sequence cant be started
     */
    bool start();
    /**
     * @brief Stops the User mode, system can be restarted by calling start again
     *
     */
    void stop();
    /**
     * @brief Sets the mode that the channel will then display the pattern outlined in the buffer
     *
     * @param memMode the mode that the memory is saved in
     * @param buffer the buffer containing the user memory
     * @param length the length of the buffer
     */
    void setMode(MEMORY_MODE memMode, uint8_t *buffer, uint32_t length);

private:
    LEDDriver *driver;
    IModeHandler *handler;
    bool controlFlag;
    MEMORY_MODE mode;
};

#endif