#ifndef __FADE_DRIVER__H_
#define __FADE_DRIVER__H_

#include <stdint.h>
#include <arduino.h>
#include <math.h>

#include "ColourDriver.h"

enum FADE_TYPE {
  SINE = 0,
  SQUARE = 1,
  TRIANGLE = 2,
  SAWTOOTH = 3,
  NONE =4,

};
const uint32_t NUM_MODES = 5;

typedef struct FadeState{
      enum FADE_TYPE fade= SINE;
      uint32_t period=0;
      uint32_t halfPeriod=0;
      uint8_t maxBrightness =0;
};


const uint32_t STEP_SIZE = 1;//ms
class FadeDriver {

public:
  FadeDriver(ColourDriver *driver);
  void startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness);
  void startFade(struct FadeState fadeState);
  FadeState getFade(void);
  void fadeLoop(void);
  void stopFade(void);
  
  private:
  ColourDriver *driver;
  struct FadeState currentState;
  uint32_t lastFadeUpdateTime;
  uint32_t currentStep;
  void squareWave(void);
  void sawToothWave(void);
  void triangleWave(void);
  void sineWave(void);
  bool getOverride(void);
  void setOverride(bool override);

};





#endif