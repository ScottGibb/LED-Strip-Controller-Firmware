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
#include <malloc.h>

using namespace std;

// Method Prototypes
static void setupDrivers(void);
static void setupLED(uint8_t index, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

// Global Variables

LEDDriver *leds;
RGBColourDriver *stripDrivers;
FadeDriver *fadeDrivers;
HueDriver *hueDrivers;

ButtonsDriver *buttonsDriver;
StatusIndicator *statusIndicator;

PowerMonitor *powerMonitor;
CommsParser *commsParser;

/**
 * @brief setup function for firmware intialisation
 *
 */
void setup(void)
{

  statusIndicator = new StatusIndicator(STATUS_LED_PIN);
  // powerMonitor = new PowerMonitor(CURRENT_SENSOR_PIN, VOLTAGE_SENSOR_PIN, POWER_SENSOR_UPDATE_PERIOD);
  setupArrays();
  setupDrivers();
  commsParser = new CommsParser(115200,500);
}
/**
 * @brief Main Arduino Loop
 * Consiting of soft timer application loops for LED Strip Drivers, comms and buttons
 *
 */
void loop(void)
{
  statusIndicator->loop();
  for (uint8_t i = 0; i < NUM_CHANNELS; i++)
  {
    fadeDrivers[i].fadeLoop();
  }
  commsParser->loop();
  buttonsDriver->loop();
  // powerMonitor->loop();
}
/**
 * @brief Sets up all the memory allocation for the arrays.
 *
 */
void setupArrays(void)
{
  leds = (LEDDriver *)malloc(sizeof(LEDDriver) * NUM_CHANNELS);
  stripDrivers = (RGBColourDriver *)malloc(sizeof(RGBColourDriver) * NUM_CHANNELS);
  fadeDrivers = (FadeDriver *)malloc(sizeof(FadeDriver) * NUM_CHANNELS);
  hueDrivers = (HueDriver *)malloc(sizeof(HueDriver) * NUM_CHANNELS);
  if (leds == NULL || stripDrivers == NULL || fadeDrivers == NULL || hueDrivers == NULL)
  {
    while (1)
      ;
  }
}
/**
 * @brief Main Setup function for fimrware, calling all driver initialisation functions and creating all objects
 *
 */
void setupDrivers(void)
{

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
void setupLED(uint8_t index, uint32_t redPin, uint32_t greenPin, uint32_t bluePin)
{
  LEDDriver led = LEDDriver(redPin, greenPin, bluePin);
  leds[index] = led;
  RGBColourDriver colDriver = RGBColourDriver(&led);
  stripDrivers[index] = colDriver;

  fadeDrivers[index] = FadeDriver(&colDriver);
  hueDrivers[index] = HueDriver(&led);
}