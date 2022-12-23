/**
 * @file StatusIndicator.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Header file associated with Status Indicator logic
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __STATUS_INDICATOR_H__
#define __STATUS_INDICATOR_H__

#include <stdint.h>

// External Function Prototypes
class StatusIndicator
{
public:
    StatusIndicator(uint32_t pin);
    void loop(void);

private:
    const uint32_t REFRESH_PERIOD = 200;
    uint32_t lastUpdateTime = {0};
    bool pinState = {false};
    uint32_t pin;
};

#endif