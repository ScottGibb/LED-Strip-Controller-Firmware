/**

**/

#include "Main.h"

//Method Prototypes
void setupLEDDrivers(void);

//Button Functions
void buttonOneFunction(void);
void buttonTwoFunction(void);
void buttonThreeFunction(void);
void buttonFourFunction(void);
void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver);

//Global Variables
ColourDriver *stripOneDriver;
FadeDriver *stripOneFadeDriver;
ColourDriver *stripTwoDriver;
FadeDriver *stripTwoFadeDriver;
ColourDriver *stripThreeDriver;
FadeDriver *stripThreeFadeDriver;

//Buttons
uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = { BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN };
func_type functions[4] = { buttonOneFunction, buttonTwoFunction, buttonThreeFunction, buttonFourFunction };
ButtonsDriver *buttonsDriver;


void setup(void) {
  setupStatusIndicator();
  setupComms();
  setupLEDDrivers();

  //Test Functions
}

void loop(void) {
  // put your main code here, to run repeatedly
  statusIndicatorLoop();
  stripOneFadeDriver->fadeLoop();
  stripTwoFadeDriver->fadeLoop();
  stripThreeFadeDriver->fadeLoop();
  commsLoop();
  buttonsDriver->loop();
}

void setupLEDDrivers(void) {
  LEDDriver *ledOne;
  ledOne = new LEDDriver(CHANNEL_1_R_PIN, CHANNEL_1_G_PIN, CHANNEL_1_B_PIN);
  stripOneDriver = new ColourDriver(ledOne);
  stripOneFadeDriver = new FadeDriver(stripOneDriver);

  LEDDriver *ledTwo;
  ledTwo = new LEDDriver(CHANNEL_2_R_PIN, CHANNEL_2_G_PIN, CHANNEL_2_B_PIN);
  stripTwoDriver = new ColourDriver(ledTwo);
  stripTwoFadeDriver = new FadeDriver(stripTwoDriver);

  LEDDriver *ledThree;
  ledThree = new LEDDriver(CHANNEL_3_R_PIN, CHANNEL_3_G_PIN, CHANNEL_3_B_PIN);
  stripThreeDriver = new ColourDriver(ledThree);
  stripThreeFadeDriver = new FadeDriver(stripThreeDriver);

  buttonsDriver = new ButtonsDriver(buttonPins, NUM_BUTTONS, functions);
}

void buttonOneFunction(void) {
  static uint8_t prevBrightness;
  static FadeState prevFadeState;

  if(stripOneDriver->getBrightness()!=0){
    Serial.println("Option One Pressed!");
    prevBrightness =stripOneDriver->getBrightness();
    stripOneDriver->setBrightness(0);
    prevFadeState = stripOneFadeDriver->getFade();
    stripOneFadeDriver->stopFade();
  }else{
    Serial.println("Option Two Pressed!");
    stripOneDriver->setBrightness(prevBrightness);
    prevBrightness =stripOneDriver->getBrightness();
    stripOneFadeDriver->startFade(prevFadeState);
    prevFadeState = stripOneFadeDriver->getFade();

  }
}


void buttonTwoFunction(void) {
  static uint8_t prevBrightness;
  static FadeState prevFadeState;
  toggleButtonLogic(&prevBrightness, &prevFadeState,stripTwoDriver, stripTwoFadeDriver);

}

void buttonThreeFunction(void) {
 static uint8_t prevBrightness;
  static FadeState prevFadeState;
  toggleButtonLogic(&prevBrightness, &prevFadeState,stripThreeDriver, stripThreeFadeDriver);
}

void buttonFourFunction(void) {
}

void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver){
  
  if(colDriver->getBrightness()!=0){
    Serial.println("Option One Pressed!");
    *brightness =colDriver->getBrightness();
    colDriver->setBrightness(0);
    *state = fadeDriver->getFade();
    fadeDriver->stopFade();
  }else{
    Serial.println("Option Two Pressed!");
    colDriver->setBrightness(*brightness);
    *brightness =colDriver->getBrightness();
    fadeDriver->startFade(*state);
    *state = fadeDriver->getFade();

  }  

}
