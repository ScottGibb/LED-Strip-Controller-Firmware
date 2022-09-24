/**

**/

#include "Main.h"
//Test Headers
void colourSwitchingLoop();

ColourDriver *stripOneDriver;
ColourDriver *stripTwoDriver;
ColourDriver *stripThreeDriver;


void setup() {
  setupStatusIndicator();
  LEDDriver *ledOne;
  ledOne = new LEDDriver(CONN_1_R_PIN, CONN_1_G_PIN, CONN_1_B_PIN);
  stripOneDriver = new ColourDriver(ledOne);

  LEDDriver ledTwo(CONN_2_R_PIN, CONN_2_G_PIN, CONN_2_B_PIN);
  stripTwoDriver = new ColourDriver(&ledTwo);

  LEDDriver ledThree(CONN_3_R_PIN, CONN_3_G_PIN, CONN_3_B_PIN);
  stripThreeDriver = new ColourDriver(&ledThree);
}

void loop() {
  // put your main code here, to run repeatedly
  statusIndicatorLoop();
  colourSwitchingLoop();
}

void colourSwitchingLoop(){
  for (uint8_t i1 = 0; i1 < NUM_COLOURS; i1++) {
    delay(2000);
    stripOneDriver->setColour(Colour(i1), 0);
    for (uint8_t i = 0; i < 100; i++) {
      stripOneDriver->setBrightness(i);
      delay(25);
    }
  }  
}