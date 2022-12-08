/**
 * @file ButtonHandler.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief ButtonHandler Source File. Contains all the functions for each button
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ButtonHandler.h"

// Project Includes
#include "Main.h"
#include "ButtonsDriver.h"
// System Includes
#include <stdint.h>

// Internal Variables
static uint8_t prevBrightness[4];
static FadeState_t prevStates[4];

// External Variables
uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN};
func_type functions[4] = {buttonOneFunction, buttonTwoFunction, buttonThreeFunction, buttonFourFunction};

// Internal Function Prototypes
static void toggleButtonLogic(uint8_t *brightness, FadeState_t *state, RGBColourDriver *colDriver, FadeDriver *fadeDriver);

// External Function Prototypes
void buttonOneFunction(void);
void buttonTwoFunction(void);
void buttonThreeFunction(void);
void buttonFourFunction(void);

/**
 * @brief Button One Logic
 *
 */
void buttonOneFunction(void)
{
  toggleButtonLogic(&prevBrightness[0], &prevStates[0], stripOneDriver, stripOneFadeDriver);
}

/**
 * @brief Button Two Logic
 *
 */
void buttonTwoFunction(void)
{

  toggleButtonLogic(&prevBrightness[1], &prevStates[1], stripTwoDriver, stripTwoFadeDriver);
}

/**
 * @brief Button Three Logic
 *
 */
void buttonThreeFunction(void)
{

  toggleButtonLogic(&prevBrightness[2], &prevStates[2], stripThreeDriver, stripThreeFadeDriver);
}

/**
 * @brief Button Four Logic
 *
 */
void buttonFourFunction(void)
{
  // TODO: Add Fourth function
  static bool onOff = false;

  if (onOff)
  {
    uint8_t minBrightness = 0;
    stripOneDriver->setColour(WHITE, minBrightness);
    stripTwoDriver->setColour(WHITE, minBrightness);
    stripThreeDriver->setColour(WHITE, minBrightness);
    onOff = false;
  }
  else
  {
    uint8_t maxBrightness = 0;
    stripOneDriver->setColour(WHITE, maxBrightness);
    stripTwoDriver->setColour(WHITE, maxBrightness);
    stripThreeDriver->setColour(WHITE, maxBrightness);
    onOff = true;
  }
}

/**
 * @brief Turns on and off the selected channels LED, pauses the Fade loop as well.
 *
 * @param[out] brightness the brightness of the led to be set
 * @param[out] state the state of the Fade
 * @param[out] colDriver the colourDriver associated with the state
 * @param[out] fadeDriver the fadeDriver associated with state
 */
void toggleButtonLogic(uint8_t *brightness, FadeState_t *state, RGBColourDriver *colDriver, FadeDriver *fadeDriver)
{

  if (colDriver->getBrightness() != 0)
  {
    Serial.println("Option One Pressed!");
    *brightness = colDriver->getBrightness();
    colDriver->setBrightness(0);
    *state = fadeDriver->getFade();
    fadeDriver->stopFade();
  }
  else
  {
    Serial.println("Option Two Pressed!");
    colDriver->setBrightness(*brightness);
    *brightness = colDriver->getBrightness();
    fadeDriver->startFade(*state);
    *state = fadeDriver->getFade();
  }
}