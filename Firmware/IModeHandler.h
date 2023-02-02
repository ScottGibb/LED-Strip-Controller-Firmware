#ifndef __IMODEHANDLER__H
#define __IMODEHANDLER__H

// Library Includes
#include <stdint.h>
// Project Includes
#include "LEDDriver.h"

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

#endif