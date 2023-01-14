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
#include <stdint.h>
#include <math.h>

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
  // https://www.rapidtables.com/convert/color/hsv-to-rgb.html
  convertLimits(&hsv);
  float C = hsv.value * hsv.saturation;
  float X = C * (1.0 - (fmodf(hsv.hue / 60, 2.0) - 1.0));
  float m = hsv.value - C;
  uint8_t rgb[3] = {0};
  if (0 <= hsv.hue && hsv.hue < 60)
  {
    rgb[0] = (C + m) * 255.0;
    rgb[1] = (X + m) * 255.0;
    rgb[2] = (0.0 + m) * 255.0;
  }
  else if (60 <= hsv.hue && hsv.hue < 120)
  {
    rgb[0] = (X + m) * 255.0;
    rgb[1] = (C + m) * 255.0;
    rgb[2] = (0.0 + m) * 255.0;
  }
  else if (120 <= hsv.hue && hsv.hue < 180)
  {
    rgb[0] = (0.0 + m) * 255.0;
    rgb[1] = (C + m) * 255.0;
    rgb[2] = (X + m) * 255.0;
  }
  else if (180 <= hsv.hue && hsv.hue < 240)
  {
    rgb[0] = (0.0 + m) * 255.0;
    rgb[1] = (X + m) * 255.0;
    rgb[2] = (C + m) * 255.0;
  }
  else if (240 <= hsv.hue && hsv.hue < 300)
  {
    rgb[0] = (X + m) * 255.0;
    rgb[1] = (0.0 + m) * 255.0;
    rgb[2] = (C + m) * 255.0;
  }
  else if (300 <= hsv.hue && hsv.hue < 360)
  {
    rgb[0] = (C + m) * 255.0;
    rgb[1] = (0.0 + m) * 255.0;
    rgb[2] = (X + m) * 255.0;
  }
  currentHSV = hsv;
  ledDriver->setPWMS(rgb);
}
void HueDriver::convertLimits(HSV_t *hsv)
{
  limiter(&hsv->hue, 0, 360);
  limiter(&hsv->saturation, 0, 1);
  limiter(&hsv->value, 0, 1);
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
HSV_t HueDriver::getHue(void)
{
  return currentHSV;
}
