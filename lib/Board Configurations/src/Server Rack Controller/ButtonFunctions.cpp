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
#include "Server Rack Controller/ButtonFunctions.h"
// Library Includes
#include "Server Rack Controller/Buttons.h"
#include "Server Rack Controller/Channels.h"

// Project Includes
#include "Main.h"

#include "ButtonsDriver.h"
// System Includes
#include <stdint.h>
#include <vector>

// Internal Variables
static uint8_t prevBrightness[NUM_LEDS];
static FadeState_t prevStates[NUM_LEDS];

// External Variables
uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN};
func_type functions[4] = {buttonOneFunction, buttonTwoFunction, buttonThreeFunction, buttonFourFunction};

// Internal Function Prototypes
static void toggleButtonLogic(uint8_t *brightness, FadeState_t *state, RGBColourDriver *colDriver, HueDriver *hueDriver, FadeDriver *fadeDriver);

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
  toggleButtonLogic(&prevBrightness[0], &prevStates[0], stripDrivers[0], hueDrivers[0], fadeDrivers[0]);
}

/**
 * @brief Button Two Logic
 *
 */
void buttonTwoFunction(void)
{

  toggleButtonLogic(&prevBrightness[1], &prevStates[1], stripDrivers[1], hueDrivers[1], fadeDrivers[1]);
}

/**
 * @brief Button Three Logic
 *
 */
void buttonThreeFunction(void)
{

  toggleButtonLogic(&prevBrightness[2], &prevStates[2], stripDrivers[2], hueDrivers[2], fadeDrivers[2]);
}

/**
 * @brief Button Four Logic
 *
 */
void buttonFourFunction(void)
{
  static bool onOff = false;

  if (onOff)
  {
    uint8_t minBrightness = 0;
    for (uint8_t i = 0; i < stripDrivers.size(); i++)
    {
      fadeDrivers[i]->stopFade();
      stripDrivers[i]->setColour(WHITE, minBrightness);
    }
    onOff = false;
  }
  else
  {
    uint8_t maxBrightness = 100;
    for (uint8_t i = 0; i < stripDrivers.size(); i++)
    {
      stripDrivers[i]->setColour(WHITE, maxBrightness);
    }
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
void toggleButtonLogic(uint8_t *brightness, FadeState_t *state, RGBColourDriver *colDriver, HueDriver *hueDriver, FadeDriver *fadeDriver)
{

  if (colDriver->getBrightness() != 0)
  {
    *brightness = colDriver->getBrightness();
    colDriver->setBrightness(0);
    *state = fadeDriver->getFade();

    fadeDriver->stopFade();
  }
  else
  {
    colDriver->setBrightness(*brightness);
    *brightness = colDriver->getBrightness();
    fadeDriver->startFade(*state);
    *state = fadeDriver->getFade();
  }
}
