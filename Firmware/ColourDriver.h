/**
 * @file ColourDriver.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Colour Driver Header file
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __COLOUR_DRIVER__H__
#define __COLOUR_DRIVER__H__

// Library Includes
#include <stdint.h>
// Project Includes
#include "LEDDriver.h"
// External Constants
const uint8_t NUM_COLOURS = 13;

/**
 * @brief Colour Enum, representing all possible colours that the ColourDriver can do
 *
 */
enum COLOUR
{
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  WHITE = 3,
  ROSE = 4,
  MAGENTA = 5,
  VIOLET = 6,
  AZURE = 7,
  CYAN = 8,
  AQUAMARINE = 9,
  CHARTREUSE = 10,
  YELLOW = 11,
  ORANGE = 12

};

/**
 * @brief
 *
 */
typedef struct
{
  uint8_t redPWM = 0;
  uint8_t greenPWM = 0;
  uint8_t bluePWM = 0;
  uint8_t brightness = 0;
  enum COLOUR colour = WHITE;
} ColourRGBState_t;

/**
 * @brief Colour Driver Class Interface
 * Responsible for controlling the RGB LED Driver, producing the colours in the enum COLOUR
 */
class RGBColourDriver
{
public:
  /**
   * @brief Construct a new Colour Driver:: Colour Driver object
   * Initialisation of the Colour Driver Object
   * @param driver
   */
  RGBColourDriver(LEDDriver *driver);
  /**
   * @brief Destroy the Colour Driver:: Colour Driver object
   *
   */
  ~RGBColourDriver();
  /**
   * @brief Sets the colour ant brightness of the RGB LED
   *
   * @param[in] colour the new colour
   * @param[in] brightness the new brightness
   */
  void setColour(enum COLOUR colour, float brightness);
  /**
   * @brief Sets the colour of the RGB LED
   *
   * @param[in] colour the colour to be set
   */
  void setColour(enum COLOUR colour);
  /**
   * @brief Returns the current colour
   *
   * @return enum COLOUR
   */
  enum COLOUR getColour();
  /**
   * @brief Sets the brighness of the RGB light
   * @param brightness the new brightness
   */
  void setBrightness(uint8_t brightness);
  /**
   * @brief Returns the current brightness of the LED strip
   *
   * @return uint8_t colourState.brightness
   */
  uint8_t getBrightness();

private:
  ColourRGBState_t colourState;
  LEDDriver *driver;
  /**
   * @brief Sets the PWM signals for each element in the RGB LED
   *
   * @param colourPWMS the PWM signals to be applied
   * @param brightness the brightness to be applied
   */
  void setPWMSignals(uint8_t *colourPWMS, float brightness);
};

#endif