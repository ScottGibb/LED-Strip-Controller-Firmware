#include "StatusIndicator.h"

//Local Variables
uint32_t lastUpdateTime ={0};
bool pinState = {false};

void setupStatusIndicator(void){
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN,pinState);
}

void statusIndicatorLoop(void){

if(millis() - lastUpdateTime >REFRESH_PERIOD){
  digitalWrite(STATUS_LED_PIN,!pinState);
  pinState = !pinState;
  lastUpdateTime = millis();
}
}