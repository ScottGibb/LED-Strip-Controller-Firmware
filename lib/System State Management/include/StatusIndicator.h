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
#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

#include <stdint.h>

// External Function Prototypes
class StatusIndicator
{
public:
    StatusIndicator(const uint32_t pin);
    void loop(void);

private:
    const uint32_t LED_PIN;
    const uint32_t REFRESH_PERIOD = 500;
    uint32_t lastUpdateTime = {0};
    bool pinState = {false};
};

#endif