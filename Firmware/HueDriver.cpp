#include "HueDriver.h"
//Project Includes
#include "LEDDriver.h"
//System Includes
#include <stdint.h>
#include <math.h>

HueDriver::HueDriver(LEDDriver *ledDriver) {
  this->ledDriver = ledDriver;
  currentHSB.brightness = 0;
  currentHSB.hue = 0;
  currentHSB.saturation = 0;
}

HueDriver::~HueDriver() {
}

void HueDriver::setHue(HSB_t hsb) {
  //https://www.rapidtables.com/convert/color/hsv-to-rgb.html
  convertLimits(&hsb);
  float C = hsb.brightness * hsb.saturation;
  float X = C * (1 - (fmodf(hsb.hue / 60, 2.0) - 1));
  float m = hsb.brightness - C;
  uint8_t rgb[3] = { 0 };
  if (0 <= hsb.hue && hsb.hue < 60) {
    rgb[0] = (C + m) * 255;
    rgb[1] = (X + m) * 255;
    rgb[2] = (0 + m) * 255;

  } else if (60 <= hsb.hue && hsb.hue < 120) {
    rgb[0] = (X + m) * 255;
    rgb[1] = (C + m) * 255;
    rgb[2] = (0 + m) * 255;
  } else if (120 <= hsb.hue && hsb.hue < 180) {
    rgb[0] = (0 + m) * 255;
    rgb[1] = (C + m) * 255;
    rgb[2] = (X + m) * 255;
  } else if (180 <= hsb.hue && hsb.hue < 240) {
    rgb[0] = (0 + m) * 255;
    rgb[1] = (X + m) * 255;
    rgb[2] = (C + m) * 255;
  } else if (240 <= hsb.hue && hsb.hue < 300) {
    rgb[0] = (X + m) * 255;
    rgb[1] = (0 + m) * 255;
    rgb[2] = (C + m) * 255;
  } else if (300 <= hsb.hue && hsb.hue < 360) {
    rgb[0] = (C + m) * 255;
    rgb[1] = (0 + m) * 255;
    rgb[2] = (X + m) * 255;
  }
  ledDriver->setPWMS(rgb);
}
void HueDriver::convertLimits(HSB_t *hsb) {
  limiter(&hsb->hue, 0, 360);
  limiter(&hsb->saturation, 0, 1);
  limiter(&hsb->brightness, 0, 1);
}
void HueDriver::limiter(float *value, float minValue, float maxValue) {
  if (*value > maxValue) {
    *value = maxValue;
  } else if (*value < minValue) {
    *value = minValue;
  }
}
HSB_t HueDriver::getHue(void) {
  return currentHSB;
}
