/**
 * @file StatusIndicator.cpp
 * @author Scott Gibb (smigbb@yahoo.com)
 * @brief Status Indicator logic source file containing soft timer implementatio  of the Status Indicator.
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "StatusIndicator.h"

// Library Includes
#include <stdint.h>
#include <Arduino.h>
// Project Includes

/**
 * @brief Sets up Status Indicator LED Pin
 *
 */
StatusIndicator::StatusIndicator(uint32_t pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, pinState);
}

/**
 * @brief Status Indicator loop responsible for calling the software timer to update the status indicator
 *
 */
void StatusIndicator::loop(void)
{

  if (millis() - lastUpdateTime > REFRESH_PERIOD)
  {
    digitalWrite(pin, !pinState);
    pinState = !pinState;
    lastUpdateTime = millis();
  }
}