/**
 * @file ColourDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Colour Driver Class Implementation Source File
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ColourDriver.h"

// Library Includes
#include <stdint.h>
// Project Includes
#include "LEDDriver.h"

RGBColourDriver::RGBColourDriver(LEDDriver *driver)
{
  this->driver = driver;
  uint8_t zeroPWM[NUM_LEDS] = {0};
  this->driver->setPWMS(zeroPWM);
  colourState.bluePWM = 0;
  colourState.redPWM = 0;
  colourState.greenPWM = 0;
  colourState.brightness = 0;
}

RGBColourDriver::~RGBColourDriver()
{
}

void RGBColourDriver::setColour(enum COLOUR colour)
{
  setColour(colour, colourState.brightness);
}

void RGBColourDriver::setColour(enum COLOUR colour, float brightness)
{
  uint8_t colourPWMS[NUM_LEDS] = {0};
  switch (colour)
  {

  case RED:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    break;
  case GREEN:
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    break;
  case BLUE:
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case WHITE:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case ROSE:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[2] = (brightness / 200.0) * MAX_PWM; // Only goes to half PWM on Blue LED
    break;
  case MAGENTA:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case VIOLET:
    colourPWMS[0] = (brightness / 200.0) * MAX_PWM; // Only goes to half PWM on Red LED
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case AZURE:
    colourPWMS[1] = (brightness / 200.0) * MAX_PWM; // Only goes to half PWM on Green LED
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case CYAN:
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
    break;
  case AQUAMARINE:
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[2] = (brightness / 200.0) * MAX_PWM; // Only goes to half PWM on Blue LED
    break;
  case CHARTREUSE:
    colourPWMS[0] = (brightness / 200.0) * MAX_PWM; // Only goes to half PWM on Green LED
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    break;
  case YELLOW:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
    break;
  case ORANGE:
    colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
    colourPWMS[1] = (brightness / 200.0) * MAX_PWM;
    break;
  }
  colourState.colour = colour;
  setPWMSignals(colourPWMS, brightness);
}

enum COLOUR RGBColourDriver::getColour()
{
  return colourState.colour;
}

void RGBColourDriver::setPWMSignals(uint8_t *colourPWMS, float brightness)
{
  colourState.redPWM = colourPWMS[0];
  colourState.greenPWM = colourPWMS[1];
  colourState.bluePWM = colourPWMS[2];
  colourState.brightness = brightness;
  driver->setPWMS(colourPWMS);
}

void RGBColourDriver::setBrightness(uint8_t brightness)
{
  setColour(colourState.colour, brightness);
}

uint8_t RGBColourDriver::getBrightness()
{
  return colourState.brightness;
}