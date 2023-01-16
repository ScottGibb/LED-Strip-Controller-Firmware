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
// Library Includes
#include <Arduino.h>
#include <vector>
using namespace std;
//Project Includes
#include "ICommunicator.h"
#include "SerialCommunicator.h"
#include "CommsParser.h"
#include "ButtonsDriver.h"
#include "ButtonHandler.h"
#include "FanController.h"
#include "PowerMonitor.h"
#include "PowerSensors.h"
#include "Channels.h"
#include "Buttons.h"
#include "StatusIndicator.h"

// Method Prototypes
static void setupDrivers(void);
static void setupLED(uint8_t index, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

// Global Variables
vector<LEDDriver *> leds;
vector<RGBColourDriver *> stripDrivers;
vector<FadeDriver *> fadeDrivers;
vector<HueDriver *> hueDrivers;

ButtonsDriver *buttonsDriver;

PowerMonitor *powerMonitor;
FanController *fanController;
StatusIndicator *statusIndicator;

CommsParser *commsParser;

/**
 * @brief setup function for firmware intialisation
 *
 */
void setup(void) {

  statusIndicator = new StatusIndicator(STATUS_LED_PIN);
  // powerMonitor = new PowerMonitor(CURRENT_SENSOR_PIN, VOLTAGE_SENSOR_PIN, POWER_SENSOR_UPDATE_PERIOD);
  //fanController = new FanController();
  setupDrivers();

  // Setup Comms
  vector<ICommunicator *> comms;
  comms.push_back(new SerialCommunicator(115200));
  commsParser = new CommsParser(comms, 500, 1000);

  fadeDrivers[0]->startFade(COLOUR_CHANGE, 1000, 100);
  stripDrivers[2]->setColour(MAGENTA, 100);
  fadeDrivers[2]->startFade(SINE, 1000, 100);

  HSV_t hsv = {
    .hue = 120,
    .saturation = 100,
    .value = 100
  };
  hueDrivers[1]->setHue(hsv);
}
/**
 * @brief Main Arduino Loop
 * Consiting of soft timer application loops for LED Strip Drivers, comms and buttons
 *
 */
void loop(void) {
  statusIndicator->loop();
  for (uint8_t i = 0; i < fadeDrivers.size(); i++) {
    fadeDrivers[i]->fadeLoop();
  }
  commsParser->loop();
  buttonsDriver->loop();
  // powerMonitor->loop();
}

/**
 * @brief Main Setup function for fimrware, calling all driver initialisation functions and creating all objects
 *
 */
void setupDrivers(void) {

  // led One
  setupLED(0, CHANNEL_1_R_PIN, CHANNEL_1_G_PIN, CHANNEL_1_B_PIN);

  // Led Two
  setupLED(1, CHANNEL_2_R_PIN, CHANNEL_2_G_PIN, CHANNEL_2_B_PIN);

  // Led Three
  setupLED(2, CHANNEL_3_R_PIN, CHANNEL_3_G_PIN, CHANNEL_3_B_PIN);

  // Add a way to check if all LEDS have been initialised

  buttonsDriver = new ButtonsDriver(buttonPins, NUM_BUTTONS, functions);
}

/**
 * @brief Setups individual led channel drivers
 *
 * @param index where the led object will be stored
 * @param redPin the pin number associated with the red part of the RGB led
 * @param greenPin the pin number associated with the green pin of the RGB led
 * @param bluePin the pin number associated with the blue pin of the RGB led
 */
void setupLED(uint8_t index, uint32_t redPin, uint32_t greenPin, uint32_t bluePin) {
  LEDDriver *led = new LEDDriver(redPin, greenPin, bluePin);
  leds.push_back(led);
  RGBColourDriver *colDriver = new RGBColourDriver(led);
  stripDrivers.push_back(colDriver);

  fadeDrivers.push_back(new FadeDriver(colDriver));
  hueDrivers.push_back(new HueDriver(led));
}