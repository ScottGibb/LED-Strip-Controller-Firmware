/**

**/

#include "Main.h"

//Method Prototypes
void setupDrivers(void);



//Global Variables
ColourDriver *stripOneDriver;
FadeDriver *stripOneFadeDriver;
ColourDriver *stripTwoDriver;
FadeDriver *stripTwoFadeDriver;
ColourDriver *stripThreeDriver;
FadeDriver *stripThreeFadeDriver;
ButtonsDriver *buttonsDriver;



void setup(void) {
  setupStatusIndicator();
  setupComms();
  setupDrivers();

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

void setupDrivers(void) {
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


