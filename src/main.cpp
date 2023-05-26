/**
 * @file Firmware.ino
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief A modular LED Light Strip Controller firmware which is using the arduino framework.
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Main.h"

// Project Includes
#include "Buttons.h"
#include "ButtonsDriver.h"
#include "Channels.h"
#include "CommsParser.h"
#include "FanController.h"
#include "ICommunicator.h"
#include "MemoryHandler.h"
#include "MemoryMap.h"
#include "PowerMonitor.h"
#include "PowerSensors.h"
#include "SerialCommunicator.h"
#include "StatusIndicator.h"

// Library Includes
#include <Arduino.h>
#include <map>
#include <vector>

// Function Prototypes
static void setupDrivers();
static void setupMemory();
static void setupLED(uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

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
MemoryHandler *memoryHandler;

/**
 * @brief setup function for firmware intialisation
 *
 */
void setup()
{
  setupMemory();
  statusIndicator = new StatusIndicator(STATUS_LED_PIN);
  // powerMonitor = new PowerMonitor(CURRENT_SENSOR_PIN, VOLTAGE_SENSOR_PIN, POWER_SENSOR_UPDATE_PERIOD);
  // fanController = new FanController();
  setupDrivers();

  // Setup Comms
  vector<ICommunicator *> comms;
  comms.push_back(new SerialCommunicator(115200));
  commsParser = new CommsParser(comms, 500, 1000);
}
/**
 * @brief Main Arduino Loop
 * Consisting of soft timer application loops for LED Strip Drivers, comms and buttons
 *
 */
void loop()
{
  statusIndicator->loop();
  for (uint8_t i = 0; i < fadeDrivers.size(); i++)
  {
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
void setupDrivers()
{

  // led One
  setupLED(CHANNEL_1_R_PIN, CHANNEL_1_G_PIN, CHANNEL_1_B_PIN);

  // Led Two
  setupLED(CHANNEL_2_R_PIN, CHANNEL_2_G_PIN, CHANNEL_2_B_PIN);

  // Led Three
  setupLED(CHANNEL_3_R_PIN, CHANNEL_3_G_PIN, CHANNEL_3_B_PIN);

  // Add a way to check if all LEDS have been initialised

  buttonsDriver = new ButtonsDriver(buttonPins, NUM_BUTTONS, functions);
}

/**
 * @brief Setups individual led channel drivers
 * @param redPin the pin number associated with the red part of the RGB led
 * @param greenPin the pin number associated with the green pin of the RGB led
 * @param bluePin the pin number associated with the blue pin of the RGB led
 */
void setupLED(uint32_t redPin, uint32_t greenPin, uint32_t bluePin)
{
  LEDDriver *led = new LEDDriver(redPin, greenPin, bluePin);
  leds.push_back(led);
  RGBColourDriver *colDriver = new RGBColourDriver(led);
  stripDrivers.push_back(colDriver);

  fadeDrivers.push_back(new FadeDriver(colDriver));
  hueDrivers.push_back(new HueDriver(led));
}

/**
 * @brief Sets up the memory structs for each segment of EEPROM memory
 *
 */
void setupMemory()
{

  const MemoryMap_t systemInfoMap = {
      .MEMORY_START = SYSTEM_INFO_START,
      .MEMORY_END = SYSTEM_INFO_END,
      .MEMORY_SIZE = SYSTEM_INFO_MEM_SIZE,
      .SLOT_SIZE = SYSTEM_INFO_SLOT_SIZE,
      .NUM_SLOTS = NUM_SYSTEM_INFO

  };

  const MemoryMap_t channelControlMap = {
      .MEMORY_START = CHANNEL_CONTROL_START,
      .MEMORY_END = CHANNEL_CONTROL_END,
      .MEMORY_SIZE = CHANNEL_CONTROL_MEM_SIZE,
      .SLOT_SIZE = CHANNEL_CONTROL_SLOT_SIZE,
      .NUM_SLOTS = NUM_CHANNEL_CONTROLS

  };

  const MemoryMap_t userModeMap = {
      .MEMORY_START = USER_MODE_START,
      .MEMORY_END = USER_MODE_END,
      .MEMORY_SIZE = USER_MODE_MEM_SIZE,
      .SLOT_SIZE = USER_MODE_SLOT_SIZE,
      .NUM_SLOTS = NUM_USER_MODES

  };
  std::map<SEGMENT, MemoryMap_t> memMap{{SEGMENT::SYSTEM_INFO, systemInfoMap}, {SEGMENT::CHANNEL_CMDS, channelControlMap}, {SEGMENT::USER_MODES, userModeMap}};
  memoryHandler = MemoryHandler::getInstance(memMap);
}