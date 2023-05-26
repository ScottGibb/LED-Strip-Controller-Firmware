/**
 * @file HueDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief The corresponding source file, outlining the source implementation  of the Hue Driver class
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "HueDriver.h"
// Project Includes
#include "LEDDriver.h"

// System Includes
#include <math.h>
#include <stdint.h>

HueDriver::HueDriver(LEDDriver *ledDriver)
{
  this->ledDriver = ledDriver;
  currentHSV.value = 0;
  currentHSV.hue = 0;
  currentHSV.saturation = 0;
}

HueDriver::~HueDriver()
{
}

void HueDriver::setHue(HSV_t hsv)
{
  convertLimits(&hsv);
  //-------------------------------------------------------------
  // https://www.codespeedy.com/hsv-to-rgb-in-cpp/

  float saturation = hsv.saturation / 100;
  float value = hsv.value / 100;
  float C = saturation * value;
  float X = C * (1 - abs(fmod(hsv.hue / 60.0, 2) - 1));
  float m = value - C;
  float red, green, blue = {0};
  if (hsv.hue >= 0 && hsv.hue < 60)
  {
    red = C, green = X, blue = 0;
  }
  else if (hsv.hue >= 60 && hsv.hue < 120)
  {
    red = X, green = C, blue = 0;
  }
  else if (hsv.hue >= 120 && hsv.hue < 180)
  {
    red = 0, green = C, blue = X;
  }
  else if (hsv.hue >= 180 && hsv.hue < 240)
  {
    red = 0, green = X, blue = C;
  }
  else if (hsv.hue >= 240 && hsv.hue < 300)
  {
    red = X, green = 0, blue = C;
  }
  else
  {
    red = C, green = 0, blue = X;
  }
  uint8_t rgb[NUM_LEDS];
  rgb[0] = static_cast<uint8_t>((red + m) * LEDDriver::MAX_PWM);
  rgb[1] = static_cast<uint8_t>((green + m) * LEDDriver::MAX_PWM);
  rgb[2] = static_cast<uint8_t>((blue + m) * LEDDriver::MAX_PWM);
  //------------------------------------------------------------
  ledDriver->setPWMS(rgb);
}
void HueDriver::convertLimits(HSV_t *hsv)
{
  limiter(&hsv->hue, 0.0, 360.0);
  limiter(&hsv->saturation, 0.0, 100.0);
  limiter(&hsv->value, 0.0, 100.0);
}
void HueDriver::limiter(float *value, float minValue, float maxValue)
{
  if (*value > maxValue)
  {
    *value = maxValue;
  }
  else if (*value < minValue)
  {
    *value = minValue;
  }
}
HSV_t HueDriver::getHue()
{
  return currentHSV;
}
