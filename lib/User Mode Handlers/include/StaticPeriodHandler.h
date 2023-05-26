#ifndef STATIC_PERIOD_HANDLER_H
#define STATIC_PERIOD_HANDLER_H

// Project Includes
#include "AbstractUserModeHandler.h"
#include "LEDDriver.h"
// System Includes
#include <stdint.h>



/**
 * @brief StaticPeriodHandler is used to interpet the user mode sequence for a static period sequence in which all the data points are spread out equally
 *
 */
class StaticPeriodHandler : public AbstractUserModeHandler
{

public:
    /**
     * @brief Construct a new Static Period Handler object
     *
     * @param driver the LEDDriver to be controlled
     * @param bufferIn the buffer containing the user mode sequence
     * @param bufferLength thje length of the user mode sequence
     */
    StaticPeriodHandler(LEDDriver *driver, uint8_t *bufferIn, uint32_t bufferLength);
    /**
     * @brief Destroy the Static Period Handler object
     *
     */
    ~StaticPeriodHandler() final;
    /**
     * @brief the sofware timed loop controlling the sequence, must be called as quickly as possible
     *
     */
    void loop() final;

private:
};

#endif//STATIC_PERIOD_HANDLER_H