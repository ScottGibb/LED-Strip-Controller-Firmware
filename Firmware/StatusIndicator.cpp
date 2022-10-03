/**
 * @file StatusIndicator.cpp
 * @author Scott Gibb (smigbb@yahoo.com)
 * @brief Status Indicator logic source file containing soft timer implementatio  of the Status Indicator.
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "StatusIndicator.h"

//Constants
const uint32_t REFRESH_PERIOD = 200;

//Local Variables
uint32_t lastUpdateTime ={0};
bool pinState = {false};

/**
 * @brief Sets up Status Indicator LED Pin
 * 
 */
void setupStatusIndicator(void){
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN,pinState);
}

/**
 * @brief Status Indicator loop responsible for calling the software timer to update the status indicator
 * 
 */
void statusIndicatorLoop(void){

if(millis() - lastUpdateTime >REFRESH_PERIOD){
  digitalWrite(STATUS_LED_PIN,!pinState);
  pinState = !pinState;
  lastUpdateTime = millis();
}
}