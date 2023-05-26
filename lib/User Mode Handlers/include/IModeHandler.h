#ifndef I_MODE_HANDLER_H
#define I_MODE_HANDLER_H

// Project Includes
#include "LEDDriver.h"
// Library Includes
#include <stdint.h>
/**
 * @brief IModeHandler Interface
 *
 */
class IModeHandler
{
public:
    /**
     * @brief Loop Function
     *
     */
    virtual void loop() = 0;
};

#endif // I_MODE_HANDLER_H