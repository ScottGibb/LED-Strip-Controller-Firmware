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

//Library Includes
#include <stdint.h>
//Project Includes
#include "LEDDriver.h"

/**
 * @brief Construct a new Colour Driver:: Colour Driver object
 * Initialisation of the Colour Driver Object
 * @param driver 
 */
ColourDriver::ColourDriver(LEDDriver *driver) {
  this->driver = driver;
  uint8_t zeroPWM[NUM_LEDS] = { 0 };
  this->driver->setPWMS(zeroPWM);
  colourState.bluePWM = 0;
  colourState.redPWM = 0;
  colourState.greenPWM = 0;
  colourState.brightness = 0;
}

/**
 * @brief Destroy the Colour Driver:: Colour Driver object
 * 
 */
ColourDriver::~ColourDriver() {
}

/**
 * @brief Sets the colour of the RGB LED
 * 
 * @param[in] colour the colour to be set
 */
void ColourDriver::setColour(enum COLOUR colour) {
  setColour(colour, colourState.brightness);
}

/**
 * @brief Sets the colour ant brightness of the RGB LED
 * 
 * @param[in] colour the new colour
 * @param[in] brightness the new brightness
 */
void ColourDriver::setColour(enum COLOUR colour, float brightness) {
  uint8_t colourPWMS[NUM_LEDS] = { 0 };
  switch (colour) {

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
      colourPWMS[2] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Blue LED
      break;
    case MAGENTA:
      colourPWMS[0] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case VIOLET:
      colourPWMS[0] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Red LED
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case AZURE:
      colourPWMS[1] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Green LED
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case CYAN:
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 100.0) * MAX_PWM;
      break;
    case AQUAMARINE:
      colourPWMS[1] = (brightness / 100.0) * MAX_PWM;
      colourPWMS[2] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Blue LED
      break;
    case CHARTREUSE:
      colourPWMS[0] = (brightness / 200.0) * MAX_PWM;  //Only goes to half PWM on Green LED
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
/**
 * @brief Returns the current colour
 * 
 * @return enum COLOUR 
 */
enum COLOUR ColourDriver::getColour() {
  return colourState.colour;
}

/**
 * @brief Sets the PWM signals for each element in the RGB LED
 * 
 * @param colourPWMS the PWM signals to be applied
 * @param brightness the brightness to be applied
 */
void ColourDriver::setPWMSignals(uint8_t *colourPWMS, float brightness) {
  colourState.redPWM = colourPWMS[0];
  colourState.greenPWM = colourPWMS[1];
  colourState.bluePWM = colourPWMS[2];
  colourState.brightness = brightness;
  driver->setPWMS(colourPWMS);
}

/**
 * @brief Sets the brighness of the RGB light
 * @param brightness the new brightness
 */
void ColourDriver::setBrightness(uint8_t brightness) {
  setColour(colourState.colour, brightness);
}

/**
 * @brief Returns the current brightness of the LED strip
 * 
 * @return uint8_t colourState.brightness
 */
uint8_t ColourDriver::getBrightness() {
  return colourState.brightness;
}