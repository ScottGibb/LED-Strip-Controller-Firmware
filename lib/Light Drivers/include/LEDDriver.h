/**
 * @file LEDDriver.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief LED Driver Header file
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

// Library Includes
#include <stdint.h>

// LED PWM Constants
const uint8_t MAX_PWM = 255;
const uint8_t MIN_PWM = 0;
// Constants
const uint8_t NUM_LEDS = 3;
/**
 * @brief LED Colour ENUM used to define the hardware RGB LED
 *
 */
enum LED_COLOUR
{
  RED_ = 0,
  GREEN_ = 1,
  BLUE_ = 2
};
const uint8_t LED_COLOUR_ENUM_LEN = NUM_LEDS;

/**
 * @brief LED Driver Class Declaration
 * Responsible for outlining the low level functionality of the RGB LED and providing an abstracted interface for control
 *
 */
class LEDDriver
{
public:
  /**
   * @brief Construct a new LEDDriver::LEDDriver object
   * LED Driver object is responsible for interfacing directly with the pwm hardware
   * @param[in] RED_PIN Red RGB PWM Pin
   * @param[in] GREEN_PIN Green RGB PWM Pin
   * @param[in] BLUE_PIN Blue RGB PWM Pin
   */
  LEDDriver(const uint8_t RED_PIN, const uint8_t GREEN_PIN, const uint8_t BLUE_PIN);
  /**
   * @brief Destroy the LEDDriver::LEDDriver object
   * Resets the pin to INPUT mode to reduce power consumption
   */
  ~LEDDriver();
  /**
   * @brief Setter for PWM of individual colour of RGB LED
   *
   * @param[in] colour the colour that pwm value is to be changed
   * @param[in] pwm the pwm to be used on the colour
   */
  void setPWM(enum LED_COLOUR colour, uint8_t pwm);
  /**
   * @brief Setter for PWM of all RGB LEDS
   *
   * @param[in] pwms an array containing the new pwm values to be applied to the RGB LED
   */
  void setPWMS(uint8_t *pwms);
  /**
   * @brief Getter for the individual PWM values of the RGB LED
   *
   * @param[in] colour selected colour
   * @return[in] uint8_t the pwm cycle currently being used
   */
  uint8_t getPWM(enum LED_COLOUR colour);

private:
  uint8_t pwm[3] = {0};
  const uint8_t LED_PINS[LED_COLOUR_ENUM_LEN] = {0};
};

#endif//LED_DRIVER_H