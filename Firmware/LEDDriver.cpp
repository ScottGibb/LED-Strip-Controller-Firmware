/**
 * @file LEDDriver.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief This LED Driver source file is used to outline the LEDDriver class through a set of setter and getter methods. A Non blocking PWM implementation is used.
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "LEDDriver.h"



/**
 * @brief Construct a new LEDDriver::LEDDriver object
 * LED Driver object is responsible for interfacing directly with the pwm hardware
 * @param[in] redPin Red RGB PWM Pin
 * @param[in] greenPin Green RGB PWM Pin
 * @param[in] bluePin Blue RGB PWM Pin
 */
LEDDriver::LEDDriver(uint8_t redPin, uint8_t greenPin, uint8_t bluePin){

ledPins[0] = redPin;
ledPins[1] = bluePin;
ledPins[2] = greenPin;

for(uint8_t index =0; index < LED_COLOUR_ENUM_LEN;index++){
  pinMode(ledPins[index], OUTPUT);
}

}

/**
 * @brief Destroy the LEDDriver::LEDDriver object
 * Resets the pin to INPUT mode to reduce power consumption
 */
LEDDriver::~LEDDriver(){
  for(uint8_t index =0; index < LED_COLOUR_ENUM_LEN;index++){
  pinMode(ledPins[index], INPUT);
}

}

/**
 * @brief Setter for PWM of individual colour of RGB LED
 * 
 * @param[in] colour the colour that pwm value is to be changed
 * @param[in] pwm the pwm to be used on the colour
 */
void LEDDriver::setPWM(enum LED_COLOUR colour, uint8_t pwm){
  analogWrite(ledPins[colour],pwm);


}

/**
 * @brief Setter for PWM of all RGB LEDS
 * 
 * @param[in] pwms an array containing the new pwm values to be applied to the RGB LED
 */
void LEDDriver::setPWMS(uint8_t* pwms){
for(uint8_t i =0; i < LED_COLOUR_ENUM_LEN; i++){
analogWrite(ledPins[i],pwms[i]);
}
}

/**
 * @brief Getter for the individual PWM values of the RGB LED
 * 
 * @param[in] colour selected colour 
 * @return[in] uint8_t the pwm cycle currently being used
 */
uint8_t LEDDriver::getPWM(enum LED_COLOUR colour){
  return ledPins[colour];
}