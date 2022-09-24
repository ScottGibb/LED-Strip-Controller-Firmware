#include "FadeDriver.h"



FadeDriver::FadeDriver(ColourDriver *driver) {
  this->driver = driver;
  lastFadeUpdateTime = millis();
  currentState.fade = NONE;
  currentState.period = 0;
  currentStep =0;
}

void FadeDriver::startFade(enum FADE_TYPE fade, uint32_t period) {
  currentState.fade = fade;
  currentState.period = period;
}

void FadeDriver::startFade(struct FadeState fadeState) {
  currentState = fadeState;
}
void FadeDriver::fadeLoop(void) {
  if (millis() - lastFadeUpdateTime > STEP_SIZE) {
    switch (currentState.fade) {
      case SINE:

        break;

      case SQUARE:
          squareWave();
        break;

      case TRIANGLE:

        break;

      case SAWTOOTH:

        break;

      case NONE:
      default:
        return;
        break;
    }
    currentStep = currentStep+STEP_SIZE;
    if(currentStep = currentState.period){
      currentStep =0;
    }
    lastFadeUpdateTime = millis();
  }
}

void FadeDriver::stopFade(void) {
  currentState.fade = NONE;
  currentState.period = 0;
}

FadeState FadeDriver::getFade(void) {
  return currentState;
}

void FadeDriver:: squareWave(void){
      if(currentStep < currentState.period/2.0){
          driver->setBrightness(0);
        }else{
          driver->setBrightness(100);     
        }
}