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

// System Includes
#include <Arduino.h>
#include <stdint.h>

/**
 * @brief Sets up Status Indicator LED Pin
 *
 */
StatusIndicator::StatusIndicator(const uint32_t pin) : LED_PIN(pin)
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, pinState);
}

/**
 * @brief Status Indicator loop responsible for calling the software timer to update the status indicator
 *
 */
void StatusIndicator::loop()
{

  if (millis() - lastUpdateTime > REFRESH_PERIOD)
  {
    digitalWrite(LED_PIN, !pinState);
    pinState = !pinState;
    lastUpdateTime = millis();
  }
}