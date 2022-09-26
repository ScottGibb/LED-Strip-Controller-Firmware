#include "FadeDriver.h"



FadeDriver::FadeDriver(ColourDriver *driver) {
  this->driver = driver;
  lastFadeUpdateTime = millis();
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
  currentState.maxBrightness = 0;
  currentStep =0;


}

void FadeDriver::startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness) {
  currentState.fade = fade;
  currentState.period = period;
  currentState.halfPeriod = period/2.0;
  currentState.maxBrightness = maxBrightness;
}

void FadeDriver::startFade(struct FadeState fadeState) {
  currentState = fadeState;
}
void FadeDriver::fadeLoop(void) {
  if ((millis() - lastFadeUpdateTime > STEP_SIZE)) {
    switch (currentState.fade) {
      case SINE:
          sineWave();
        break;

      case SQUARE:
          squareWave();
        break;

      case TRIANGLE:
          triangleWave();
        break;

      case SAWTOOTH:
          sawToothWave();
        break;

      case NONE:
      default:
        return;
        break;
    }
    currentStep = currentStep+STEP_SIZE;
    if(currentStep > currentState.period){
        currentStep =0;
    }
    lastFadeUpdateTime = millis();
  }

}

void FadeDriver::stopFade(void) {
    currentState.fade = NONE;
  currentState.period = 0;
  currentState.period = 0;
 
}


FadeState FadeDriver::getFade(void) {
  return currentState;
}

void FadeDriver:: squareWave(void){
      if(currentStep < currentState.halfPeriod){
          driver->setBrightness(currentState.maxBrightness);
        }else{
          driver->setBrightness(0);     
        }
}

void FadeDriver:: sawToothWave(void){
      driver->setBrightness(((1.0*(currentStep)/currentState.period))*currentState.maxBrightness);

}

void FadeDriver:: triangleWave(void){
  if(currentStep < currentState.halfPeriod){
        driver->setBrightness(((1.0*(currentStep)/currentState.halfPeriod))*currentState.maxBrightness);
        }else{
          uint8_t brightness =  (((currentState.period - currentStep)*1.0)/currentState.halfPeriod)*currentState.maxBrightness;
          driver->setBrightness(brightness);
        }
}
void FadeDriver:: sineWave(void){

    float angle = (currentStep*1.0/currentState.halfPeriod);
    uint8_t brightness = (currentState.maxBrightness/2) * sin(angle * PI) + (currentState.maxBrightness/2.0);
    driver->setBrightness(brightness);

}