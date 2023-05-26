/**
 * @file LEDDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief This LED Driver source file is used to outline the LEDDriver class through a set of setter and getter methods. A Non blocking PWM implementation is used.
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "LEDDriver.h"

// Library Includes
#include <Arduino.h>
#include <stdint.h>

LEDDriver::LEDDriver(const uint8_t redPin, const uint8_t greenPin, const uint8_t bluePin) : LED_PINS{redPin, greenPin, bluePin}
{
  for (uint8_t index = 0; index < LED_COLOUR_ENUM_LEN; index++)
  {
    pinMode(LED_PINS[index], OUTPUT);
  }
}

LEDDriver::~LEDDriver()
{
  for (uint8_t index = 0; index < LED_COLOUR_ENUM_LEN; index++)
  {
    pinMode(LED_PINS[index], INPUT);
  }
}

void LEDDriver::setPWM(enum LED_COLOUR colour, uint8_t pwm)
{
  analogWrite(LED_PINS[colour], pwm);
}

void LEDDriver::setPWMS(uint8_t *pwms)
{
  for (uint8_t i = 0; i < LED_COLOUR_ENUM_LEN; i++)
  {
    analogWrite(LED_PINS[i], pwms[i]);
  }
}

uint8_t LEDDriver::getPWM(enum LED_COLOUR colour)
{
  return LED_PINS[colour];
}