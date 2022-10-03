/**
 * @file Firmware.ino
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief LED Light Strip Controller firmware based on the STM32F103C8T6 microcontroller utilising the Arduino framework. The
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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


/**
 * @brief setup function for firmware intialisation
 * 
 */
void setup(void) {
  setupStatusIndicator();
  setupComms();
  setupDrivers();

}
/**
 * @brief Main Arduino Loop
 * Consiting of soft timer application loops for LED Strip Drivers, comms and buttons
 * 
 */
void loop(void) {
  statusIndicatorLoop();
  stripOneFadeDriver->fadeLoop();
  stripTwoFadeDriver->fadeLoop();
  stripThreeFadeDriver->fadeLoop();
  commsLoop();
  buttonsDriver->loop();
}

/**
 * @brief Main Setup function for fimrware, calling all driver initialisation functions and creating all objects
 * 
 */
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


