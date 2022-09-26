#include "ButtonsDriver.h"

#include "CommsParser.h"

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
ButtonsDriver:: ~ButtonsDriver(){
  
}
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