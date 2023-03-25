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

LEDDriver::LEDDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
{

  ledPins[0] = redPin;
  ledPins[1] = bluePin;
  ledPins[2] = greenPin;

  for (uint8_t index = 0; index < LED_COLOUR_ENUM_LEN; index++)
  {
    pinMode(ledPins[index], OUTPUT);
  }
}

LEDDriver::~LEDDriver()
{
  for (uint8_t index = 0; index < LED_COLOUR_ENUM_LEN; index++)
  {
    pinMode(ledPins[index], INPUT);
  }
}

void LEDDriver::setPWM(enum LED_COLOUR colour, uint8_t pwm)
{
  analogWrite(ledPins[colour], pwm);
}

void LEDDriver::setPWMS(uint8_t *pwms)
{
  for (uint8_t i = 0; i < LED_COLOUR_ENUM_LEN; i++)
  {
    analogWrite(ledPins[i], pwms[i]);
  }
}

uint8_t LEDDriver::getPWM(enum LED_COLOUR colour)
{
  return ledPins[colour];
}