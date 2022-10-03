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

//Button Variables
uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = { BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN };
func_type functions[4] = { buttonOneFunction, buttonTwoFunction, buttonThreeFunction, buttonFourFunction };

//Internal Button Functions
void buttonOneFunction(void);
void buttonTwoFunction(void);
void buttonThreeFunction(void);
void buttonFourFunction(void);
void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver);


/**
 * @brief Button One Logic
 * 
 */
void buttonOneFunction(void) {
  toggleButtonLogic(&prevBrightness[0], &prevStates[0], stripOneDriver, stripOneFadeDriver);
}

/**
 * @brief Button Two Logic
 * 
 */
void buttonTwoFunction(void) {

  toggleButtonLogic(&prevBrightness[1], &prevStates[1], stripTwoDriver, stripTwoFadeDriver);
}

/**
 * @brief Button Three Logic
 * 
 */
void buttonThreeFunction(void) {

  toggleButtonLogic(&prevBrightness[2], &prevStates[2], stripThreeDriver, stripThreeFadeDriver);
}

/**
 * @brief Button Four Logic
 * 
 */
void buttonFourFunction(void) {
  //TODO: Add Fourth function
}

/**
 * @brief Turns on and off the selected channels LED, pauses the Fade loop as well.
 * 
 * @param[out] brightness the brightness of the led to be set
 * @param[out] state the state of the Fade 
 * @param[out] colDriver the colourDriver associated with the state
 * @param[out] fadeDriver the fadeDriver associated with state
 */
void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver) {

  if (colDriver->getBrightness() != 0) {
    Serial.println("Option One Pressed!");
    *brightness = colDriver->getBrightness();
    colDriver->setBrightness(0);
    *state = fadeDriver->getFade();
    fadeDriver->stopFade();
  } else {
    Serial.println("Option Two Pressed!");
    colDriver->setBrightness(*brightness);
    *brightness = colDriver->getBrightness();
    fadeDriver->startFade(*state);
    *state = fadeDriver->getFade();
  }
}