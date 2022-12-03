#ifndef __HUE_DRIVER_H__
#define __HUE_DRIVER_H__

#include "LEDDriver.h"

typedef struct HSB_t{
  float hue;
  float saturation;
  float brightness;
}HSB_t;

class HueDriver{

  public:
  HueDriver(LEDDriver* ledDriver);
  ~HueDriver();
  void setHue(HSB_t hsb);
  HSB_t getHue(void);

  private:
  LEDDriver *ledDriver;
  HSB_t currentHSB;
  void convertLimits(HSB_t *hsb);
  void limiter(float *value, float minValue, float maxValue);

};

#endif