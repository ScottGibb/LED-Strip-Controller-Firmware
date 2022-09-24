/**

**/

#include "Main.h"
//Test Headers
void testLoop();
const uint32_t COLOUR_SWAP_TIME = 5000;
uint32_t lastcolourSwapTime = 0;
uint8_t colourNumber = 0;

const uint32_t MODE_SWAP_TIME = COLOUR_SWAP_TIME * NUM_COLOURS;
uint32_t lastModeSwapTime = 0;
uint8_t modeNumber = 0;



ColourDriver *stripOneDriver;
FadeDriver *stripOneFadeDriver;

ColourDriver *stripTwoDriver;
ColourDriver *stripThreeDriver;


void setup() {
  setupStatusIndicator();
  LEDDriver *ledOne;
  ledOne = new LEDDriver(CONN_1_R_PIN, CONN_1_G_PIN, CONN_1_B_PIN);
  stripOneDriver = new ColourDriver(ledOne);
  stripOneFadeDriver = new FadeDriver(stripOneDriver);

  LEDDriver ledTwo(CONN_2_R_PIN, CONN_2_G_PIN, CONN_2_B_PIN);
  stripTwoDriver = new ColourDriver(&ledTwo);

  LEDDriver ledThree(CONN_3_R_PIN, CONN_3_G_PIN, CONN_3_B_PIN);
  stripThreeDriver = new ColourDriver(&ledThree);



  //Test Functions
}

void loop() {
  // put your main code here, to run repeatedly
  statusIndicatorLoop();
  stripOneFadeDriver->fadeLoop();
  testLoop();

    
  Serial.print("Mode: "); Serial.println(modeNumber);
  Serial.print("Colour: "); Serial.println(colourNumber);
}

void testLoop() {
  if (millis() - lastModeSwapTime > MODE_SWAP_TIME) {

    modeNumber++;
    if (modeNumber == NUM_MODES) {
      modeNumber = 0;
    }
    stripOneFadeDriver->startFade(FADE_TYPE(modeNumber),1000,100);
    lastModeSwapTime = millis();
  }

  if (millis() - lastcolourSwapTime > COLOUR_SWAP_TIME) {
    colourNumber++;
    if (colourNumber == NUM_COLOURS) {
      colourNumber = 0;
    }
       stripOneDriver->setColour(COLOUR(colourNumber));
    lastcolourSwapTime = millis();
  }
}