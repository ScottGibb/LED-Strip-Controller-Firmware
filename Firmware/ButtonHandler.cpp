#include "ButtonHandler.h"


//Button Functions
void buttonOneFunction(void);
void buttonTwoFunction(void);
void buttonThreeFunction(void);
void buttonFourFunction(void);
void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver);


//Buttons

uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = { BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN };
func_type functions[4] = { buttonOneFunction, buttonTwoFunction, buttonThreeFunction, buttonFourFunction };

const uint8_t NUM_CHANNELS = 3;
uint8_t prevBrightness[NUM_CHANNELS];
FadeState prevStates[NUM_CHANNELS];

void buttonOneFunction(void) {
  toggleButtonLogic(&prevBrightness[0], &prevStates[0], stripOneDriver, stripOneFadeDriver);
}


void buttonTwoFunction(void) {

  toggleButtonLogic(&prevBrightness[1], &prevStates[1], stripTwoDriver, stripTwoFadeDriver);
}

void buttonThreeFunction(void) {

  toggleButtonLogic(&prevBrightness[2], &prevStates[2], stripThreeDriver, stripThreeFadeDriver);
}

void buttonFourFunction(void) {
}

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