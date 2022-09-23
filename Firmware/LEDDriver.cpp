#include "LEDDriver.h"


LEDDriver::LEDDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){

ledPins[0] = redPin;
ledPins[1] = bluePin;
ledPins[2] = greenPin;

for(uint8_t index =0; index < LED_COLOUR_ENUM_LEN;index++){
  pinMode(ledPins[index], OUTPUT);
}

}
LEDDriver::~LEDDriver(){
  for(uint8_t index =0; index < LED_COLOUR_ENUM_LEN;index++){
  pinMode(ledPins[index], INPUT);
}

}


void LEDDriver::setPWM(enum LED_COLOUR colour, uint8_t pwm){
  analogWrite(ledPins[colour],pwm);


}

void LEDDriver::setPWMS(uint8_t* pwms){
for(uint8_t i =0; i < LED_COLOUR_ENUM_LEN; i++){
analogWrite(ledPins[i],pwms[i]);
}
}

uint8_t LEDDriver::getPWM(enum LED_COLOUR colour){
  return ledPins[colour];
}