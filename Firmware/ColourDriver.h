#ifndef __COLOUR_DRIVER__H__
#define __COLOUR_DRIVER__H__

#include <stdint.h>
#include "LEDDriver.h"
enum Colour {
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
  CHARTREUSE =10,
  YELLOW = 11,
  ORANGE = 12
  
 
};

const uint8_t NUM_COLOURS = 13;

typedef struct ColourRGBState {
  uint8_t redPWM = 0;
  uint8_t greenPWM = 0;
  uint8_t bluePWM = 0;
  uint8_t brightness = 0;
  enum Colour colour = WHITE;
};


class ColourDriver {
public:
  ColourDriver(LEDDriver *driver);
  ~ColourDriver();
  void setColour(enum Colour colour, float brightness);
  void setColour(enum Colour colour);
  enum Colour getColour();
  void setBrightness(uint8_t brightness);
  uint8_t getBrightness();
private:
  struct ColourRGBState colourState;
  LEDDriver *driver;
  void setPWMSignals(uint8_t *colourPWMS, float brightness);

}
;



#endif