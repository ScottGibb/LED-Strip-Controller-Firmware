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

HueDriver::HueDriver(LEDDriver *ledDriver) {
  this->ledDriver = ledDriver;
  currentHSV.value = 0;
  currentHSV.hue = 0;
  currentHSV.saturation = 0;
}

HueDriver::~HueDriver() {
}

void HueDriver::setHue(HSV_t hsv) {
  convertLimits(&hsv);
  //-------------------------------------------------------------
  //https://www.codespeedy.com/hsv-to-rgb-in-cpp/

  float s = hsv.saturation / 100;
  float v = hsv.value / 100;
  float C = s * v;
  float X = C * (1 - abs(fmod(hsv.hue / 60.0, 2) - 1));
  float m = v - C;
  float r, g, b;
  if (hsv.hue >= 0 && hsv.hue < 60) {
    r = C, g = X, b = 0;
  } else if (hsv.hue >= 60 && hsv.hue < 120) {
    r = X, g = C, b = 0;
  } else if (hsv.hue >= 120 && hsv.hue < 180) {
    r = 0, g = C, b = X;
  } else if (hsv.hue >= 180 && hsv.hue < 240) {
    r = 0, g = X, b = C;
  } else if (hsv.hue >= 240 && hsv.hue < 300) {
    r = X, g = 0, b = C;
  } else {
    r = C, g = 0, b = X;
  }
  uint8_t rgb[NUM_LEDS];
  rgb[0] = (r + m) * 255;
  rgb[1] = (g + m) * 255;
  rgb[2] = (b + m) * 255;
  //------------------------------------------------------------
  ledDriver->setPWMS(rgb);
}
void HueDriver::convertLimits(HSV_t *hsv) {
  limiter(&hsv->hue, 0.0, 360.0);
  limiter(&hsv->saturation, 0.0, 100.0);
  limiter(&hsv->value, 0.0, 100.0);
}
void HueDriver::limiter(float *value, float minValue, float maxValue) {
  if (*value > maxValue) {
    *value = maxValue;
  } else if (*value < minValue) {
    *value = minValue;
  }
}
HSV_t HueDriver::getHue(void) {
  return currentHSV;
}
