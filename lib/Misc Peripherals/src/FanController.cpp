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

// System Includes
#include <Arduino.h>

FanController::FanController(const uint32_t FAN_PIN) :FAN_PIN(FAN_PIN), pwm(0), duty(0)
{
  pinMode(this->FAN_PIN, OUTPUT);
}

FanController::~FanController()
{
}

void FanController::changeDuty(uint8_t newDuty)
{
  uint16_t newPWM = (newDuty / 100.0) * MAX_PWM;
  analogWrite(FAN_PIN, newPWM);
  this->pwm = newPWM;
  this->duty = newDuty;
}

uint8_t FanController::getDuty(void)
{
  return this->duty;
}