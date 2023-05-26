/**
 * @file ButtonsDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Buttons Driver Class Implementation source file, currently using software timed logic.
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ButtonsDriver.h"

// Library Includes
#include <Arduino.h>
#include <stdint.h>

ButtonsDriver::ButtonsDriver(const uint32_t *buttonPins, const uint8_t numButtons, const func_type *funcs) : buttonPins(buttonPins), numButtons(numButtons), functions(funcs)
{
  for (uint8_t index = 0; index < numButtons; index++)
  {
    pinMode(buttonPins[index], INPUT);
  }

  lastDebounceTimes = new uint32_t[numButtons];
  buttonStates = new int[numButtons];
  lastButtonStates = new int[numButtons];

  for (uint8_t index = 0; index < numButtons; index++)
  {
    lastDebounceTimes[index] = 0;
    lastButtonStates[index] = 1;
  }
}

ButtonsDriver::~ButtonsDriver()
{
  delete[] lastDebounceTimes;
  delete[] buttonStates;
  delete[] lastButtonStates;
}

void ButtonsDriver::loop()
{

  for (uint8_t i = 0; i < numButtons; i++)
  {
    int reading = digitalRead(buttonPins[i]);
    // Serial.print("Reading: "); Serial.print(i); Serial.print(" Is "); Serial.println(reading);

    if (reading != lastButtonStates[i])
    {
      lastDebounceTimes[i] = millis();
    }
    if ((millis() - lastDebounceTimes[i]) > MAX_DEBOUNCE_TIME)
    {
      // Serial.print("lastDebounceTime for "); Serial.print(i); Serial.print("Is ");Serial.println(lastDebounceTimes[i]);
      if (reading != buttonStates[i])
      {
        buttonStates[i] = reading;
        // Serial.println("--------------------------Updated State-----------------");

        //   // only toggle the LED if the new button state is HIGH
        if (buttonStates[i] == LOW)
        {
          // Serial.print("Button Pressed :"); Serial.println(i);
          functions[i]();
          //     //execute function call!
        }
      }
    }

    lastButtonStates[i] = reading;
  }
}