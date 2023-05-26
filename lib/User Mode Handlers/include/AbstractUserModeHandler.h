#ifndef ABSTRACT_USER_MODE_HANDLER_H
#define ABSTRACT_USER_MODE_HANDLER_H

// Project Includes
#include "IModeHandler.h"
#include "LEDDriver.h"

// Library Includes
#include <stdint.h>


/**
 * @brief AbstractUserModeHandler
 *
 */
class AbstractUserModeHandler : public IModeHandler
{

public:
    /**
     * @brief Construct a new Abstract User Mode Handler object
     *
     * @param driverIn the ledDriver to be controlled
     * @param bufferIn the buffer containing the user mode sequence
     * @param bufferLength the length of the buffer
     */
    AbstractUserModeHandler(LEDDriver *driverIn, uint8_t *bufferIn, uint32_t bufferLength);
    /**
     * @brief Destroy the Abstract User Mode Handler object
     *
     */
    virtual ~AbstractUserModeHandler();
    /**
     * @brief the software timed loop used to make the sequence
     *
     */
    virtual void loop() = 0;

    AbstractUserModeHandler(const AbstractUserModeHandler &) = delete;
    AbstractUserModeHandler &operator=(const AbstractUserModeHandler &) = delete;
private:
    uint8_t *buffer;
    uint8_t length;
    LEDDriver *driver;
};

#endif//ABSTRACT_USER_MODE_HANDLER_H