#ifndef __HUE_DRIVER_H__
#define __HUE_DRIVER_H__

#include "ColourDriver.h"

typedef struct HSB_t{
  float hue;
  float saturation;
  float brightness;
}HSB_t;

class HueDriver{

  public:
  HueDriver(RGBColourDriver* colDriver);
  ~HueDriver();
  void setHue(HSB_t hsb);
  HSB_t getHue(void);

  private:
  RGBColourDriver *colDriver;
  HSB_t currentHSB;
};

#endif