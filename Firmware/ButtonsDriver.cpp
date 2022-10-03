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

/**
 * @brief Construct a new Buttons Driver:: Buttons Driver object
 * Buttons Driver Constructor. Each Array should be ordered such that when buttonPins[i] is pressed funcs[i] is called
 * @param[in] buttonPins A Pointer to the pins used for the buttons
 * @param[in] numButtons The Number of Buttons 
 * @param[in] funcs The function assigned to each button 
 */
ButtonsDriver::ButtonsDriver( uint32_t *buttonPins,  uint8_t numButtons, func_type *funcs){
  this->buttonPins = buttonPins;
  this->numButtons = numButtons;
  this->functions = funcs;

  for(uint8_t index = 0; index < numButtons; index++){
        pinMode(buttonPins[index], INPUT);
    }

    lastDebounceTimes =(uint32_t*) malloc(numButtons *sizeof(uint32_t));
    buttonStates =(int*) malloc(numButtons *sizeof(int));
    lastButtonStates =(int*) malloc(numButtons *sizeof(int));
    
  for(uint8_t index =0; index < numButtons; index++){
        lastDebounceTimes[index] =0;
        lastButtonStates[index] =1;
        

  }
}

/**
 * @brief ButtonsDriver Deconsructor
 * 
 * @return ButtonsDriver:: 
 */
ButtonsDriver:: ~ButtonsDriver(){
  
}

/**
 * @brief ButtonsDriver Main Loop
 * To be called once every iteration of the main loop of the firmware.
 */
void ButtonsDriver::loop(void){

  for(uint8_t i=0; i < numButtons;i++){
    int reading = digitalRead(buttonPins[i]);
    // Serial.print("Reading: "); Serial.print(i); Serial.print(" Is "); Serial.println(reading);
    
    if(reading != lastButtonStates[i]){
      lastDebounceTimes[i] = millis();
    }
    if((millis() - lastDebounceTimes[i])> MAX_DEBOUNCE_TIME){
      // Serial.print("lastDebounceTime for "); Serial.print(i); Serial.print("Is ");Serial.println(lastDebounceTimes[i]);
      if (reading != buttonStates[i]) {
        buttonStates[i] = reading;
      // Serial.println("--------------------------Updated State-----------------");

    //   // only toggle the LED if the new button state is HIGH
      if (buttonStates[i] == LOW) {
        // Serial.print("Button Pressed :"); Serial.println(i);
        functions[i]();
    //     //execute function call!
      }
    }

  }
  
  lastButtonStates[i] = reading;
}
}