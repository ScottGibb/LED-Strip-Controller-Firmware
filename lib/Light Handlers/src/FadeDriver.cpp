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
// Project Includes
#include "ColourDriver.h"
// Library Includes
#include <Arduino.h>
#include <math.h>

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
  currentState.halfPeriod = static_cast<uint32_t>(period / 2.0F);
  currentState.maxBrightness = maxBrightness;
}

void FadeDriver::startFade(FadeState_t fadeState)
{
  currentState = fadeState;
}

void FadeDriver::fadeLoop()
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

void FadeDriver::stopFade()
{
  currentState.fade = NONE;
  currentState.period = 0;
  currentState.halfPeriod = 0;
}

FadeState_t FadeDriver::getFade()
{
  return currentState;
}

void FadeDriver::squareWave()
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

void FadeDriver::sawToothWave()
{
  uint8_t brightness = static_cast<uint8_t>((((currentStep)*1.0) / currentState.period) * currentState.maxBrightness);
  driver->setBrightness(brightness);
}

void FadeDriver::triangleWave()
{
  if (currentStep < currentState.halfPeriod)
  {
    uint8_t brightness = static_cast<uint8_t>((((currentStep)*1.0) / currentState.halfPeriod) * currentState.maxBrightness);
    driver->setBrightness(brightness);
  }
  else
  {
    uint8_t brightness = (((currentState.period - currentStep) * 1.0) / currentState.halfPeriod) * currentState.maxBrightness;
    driver->setBrightness(brightness);
  }
}

void FadeDriver::sineWave()
{

  float angle = (currentStep * 1.0 / currentState.halfPeriod);
  uint8_t brightness = static_cast<uint8_t>((currentState.maxBrightness / 2) * sin(angle * PI) + (currentState.maxBrightness / 2.0));
  driver->setBrightness(brightness);
}