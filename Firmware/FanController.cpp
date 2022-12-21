/**
 * @file FanController.cpp
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief This class is responsible for controlling a Fan using PWM
 * @version 0.1
 * @date 2022-12-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "FanController.h"

//System Includes
#include <Arduino.h>


FanController::FanController(uint32_t fanPin){
    this->fanPin = fanPin;
    this->duty=0;
    this->pwm =0;
    pinMode(this->fanPin, OUTPUT);
}

FanController::~FanController(){

}

void FanController::changeDuty(uint8_t newDuty){
  uint16_t newPWM = (newDuty/100.0) * MAX_PWM;
  analogWrite(fanPin,newPWM);
  this->pwm = newPWM;
  this->duty = newDuty;
}

uint8_t FanController::getDuty(void){
    return this->duty;
}