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

//Global Variables
ColourDriver *stripOneDriver;
FadeDriver *stripOneFadeDriver;
ColourDriver *stripTwoDriver;
FadeDriver *stripTwoFadeDriver;
ColourDriver *stripThreeDriver;
FadeDriver *stripThreeFadeDriver;

//Buttons
uint8_t NUM_BUTTONS = 4;
uint32_t buttonPins[4] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN};
func_type functions[4]={buttonOneFunction,buttonTwoFunction, buttonThreeFunction, buttonFourFunction};
ButtonsDriver * buttonsDriver;


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

void setupLEDDrivers(void){
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

  buttonsDriver = new ButtonsDriver(buttonPins,NUM_BUTTONS,functions);
}

void buttonOneFunction(void){ 
    
stripOneDriver->setBrightness(0);
stripOneFadeDriver->stopFade();
}


void buttonTwoFunction(void){
stripTwoDriver->setBrightness(0);
stripTwoFadeDriver->stopFade();
}

void buttonThreeFunction(void){
stripThreeDriver->setBrightness(0);
stripThreeFadeDriver->stopFade();
}

void buttonFourFunction(void){

}

