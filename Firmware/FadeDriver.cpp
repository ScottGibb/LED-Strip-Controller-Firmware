/**
 * @file FadeDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Fade Driver Object Implementation code, outlining all the fade Driver works.
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "FadeDriver.h"

//Library Includes
#include <arduino.h>
#include <math.h>
//Library Includes
#include "ColourDriver.h"

//Constansts
static const uint32_t STEP_SIZE = 1;  //ms

/**
 * @brief Construct a new Fade Driver:: Fade Driver object
 * @param[in] driver The colour Driver object used for the specific led channel
 */
FadeDriver::FadeDriver(RGBColourDriver *driver) {
  this->driver = driver;
  lastFadeUpdateTime = millis();
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
  currentState.maxBrightness = 0;
  currentStep = 0;
}
/**
 * @brief Starts the next fade cycle with the chosen paramaters
 * 
 * @param[in] fade the type of fade to be applied
 * @param[in] period the period of the fade signal
 * @param[in] maxBrightness the maximum brightness to be achieved during the cycle
 */
void FadeDriver::startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness) {
  stopFade();
  currentState.fade = fade;
  currentState.period = period;
  currentState.halfPeriod = period / 2.0;
  currentState.maxBrightness = maxBrightness;
}

/**
 * @brief Changes the current fade and all of its settings to the new fade provided
 * 
 * @param[in] fadeState the fade to be changed to
 */
void FadeDriver::startFade(FadeState_t fadeState) {
  currentState = fadeState;
}

/**
 * @brief The Fad Driver application loop
 * Call at frequency faster than 1/STEP_SIZE in order to maintain smooth fade transitions
 */
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

      case COLOUR_CHANGE:
        sineWave();  //TODO: Add Future Capability to swap out which waveform its colour changing
        break;

      case NONE:
      default:
        return;
    }
    currentStep = currentStep + STEP_SIZE;
    if (currentStep > currentState.period) {
      currentStep = 0;
      if (currentState.fade == COLOUR_CHANGE) {
        uint8_t col = (uint8_t)driver->getColour();
        col++;
        if (col == NUM_COLOURS) {
          col = 0;
        }
        driver->setColour(COLOUR(col));
      }
    }
    lastFadeUpdateTime = millis();
  }
}

/**
 * @brief Stops the current fade and resets all fade settings to default
 * 
 */
void FadeDriver::stopFade(void) {
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
}

/**
 * @brief Gets the current fade state
 * @return FadeState the current fade and its settings
 */
FadeState_t FadeDriver::getFade(void) {
  return currentState;
}

/**
 * @brief Soft timer implementation of the square wave signal
 * 
 */
void FadeDriver::squareWave(void) {
  if (currentStep < currentState.halfPeriod) {
    driver->setBrightness(currentState.maxBrightness);
  } else {
    driver->setBrightness(0);
  }
}

/**
 * @brief Soft timer implementation of the sawTooth Waveform
 * 
 */
void FadeDriver::sawToothWave(void) {
  driver->setBrightness(((1.0 * (currentStep) / currentState.period)) * currentState.maxBrightness);
}

/**
 * @brief Soft timer implementation of the triangular waveform
 * 
 */
void FadeDriver::triangleWave(void) {
  if (currentStep < currentState.halfPeriod) {
    driver->setBrightness(((1.0 * (currentStep) / currentState.halfPeriod)) * currentState.maxBrightness);
  } else {
    uint8_t brightness = (((currentState.period - currentStep) * 1.0) / currentState.halfPeriod) * currentState.maxBrightness;
    driver->setBrightness(brightness);
  }
}

/**
 * @brief Soft Timer implementation of the sine waveform
 * 
 */
void FadeDriver::sineWave(void) {

  float angle = (currentStep * 1.0 / currentState.halfPeriod);
  uint8_t brightness = (currentState.maxBrightness / 2) * sin(angle * PI) + (currentState.maxBrightness / 2.0);
  driver->setBrightness(brightness);
}