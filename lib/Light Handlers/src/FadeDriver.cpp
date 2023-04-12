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

// Library Includes
#include <Arduino.h>
#include <math.h>
// Library Includes
#include "ColourDriver.h"

// Constansts
static const uint32_t STEP_SIZE = 1; // ms

FadeDriver::FadeDriver(RGBColourDriver *driver)
{
  this->driver = driver;
  lastFadeUpdateTime = millis();
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
  currentState.maxBrightness = 0;
  currentStep = 0;
}

FadeDriver::~FadeDriver()
{
}

void FadeDriver::startFade(enum FADE_TYPE fade, uint32_t period, uint8_t maxBrightness)
{
  stopFade();
  currentState.fade = fade;
  currentState.period = period;
  currentState.halfPeriod = period / 2.0;
  currentState.maxBrightness = maxBrightness;
}

void FadeDriver::startFade(FadeState_t fadeState)
{
  currentState = fadeState;
}

void FadeDriver::fadeLoop(void)
{
  if ((millis() - lastFadeUpdateTime > STEP_SIZE))
  {
    switch (currentState.fade)
    {
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
      sineWave(); // TODO: Add Future Capability to swap out which waveform its colour changing
      break;

    case NONE:
    case RGB_CONTROL:
    case HUE_CONTROL:
    default:
      return;
    }
    currentStep = currentStep + STEP_SIZE;
    if (currentStep > currentState.period)
    {
      currentStep = 0;
      if (currentState.fade == COLOUR_CHANGE)
      {
        uint8_t col = (uint8_t)driver->getColour();
        col++;
        if (col == NUM_COLOURS)
        {
          col = 0;
        }
        driver->setColour(COLOUR(col));
      }
    }
    lastFadeUpdateTime = millis();
  }
}

void FadeDriver::stopFade(void)
{
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
}

FadeState_t FadeDriver::getFade(void)
{
  return currentState;
}

void FadeDriver::squareWave(void)
{
  if (currentStep < currentState.halfPeriod)
  {
    driver->setBrightness(currentState.maxBrightness);
  }
  else
  {
    driver->setBrightness(0);
  }
}

void FadeDriver::sawToothWave(void)
{
  driver->setBrightness(((1.0 * (currentStep) / currentState.period)) * currentState.maxBrightness);
}

void FadeDriver::triangleWave(void)
{
  if (currentStep < currentState.halfPeriod)
  {
    driver->setBrightness(((1.0 * (currentStep) / currentState.halfPeriod)) * currentState.maxBrightness);
  }
  else
  {
    uint8_t brightness = (((currentState.period - currentStep) * 1.0) / currentState.halfPeriod) * currentState.maxBrightness;
    driver->setBrightness(brightness);
  }
}

void FadeDriver::sineWave(void)
{

  float angle = (currentStep * 1.0 / currentState.halfPeriod);
  uint8_t brightness = (currentState.maxBrightness / 2) * sin(angle * PI) + (currentState.maxBrightness / 2.0);
  driver->setBrightness(brightness);
}