/**
 * @file HueDriver.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Hue Driver Header file outlining the interface for controlling LEDs using HUE values instead of RGB values
 * @version 0.1
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __HUE_DRIVER_H__
#define __HUE_DRIVER_H__

// Project Includes
#include "LEDDriver.h"

/**
 * @brief HSB Struct
 *
 */
typedef struct HSB_t
{
  float hue;        /*360 Degree value 0-360*/
  float saturation; /*% Based Value 0-1*/
  float brightness; /*% Based value 0-1*/
} HSB_t;

/**
 * @brief HueDriver Class Responsible for controlling the LedDriver but with HSV values instead of RGB values
 *
 */
class HueDriver
{

public:
  /**
   * @brief Construct a new Hue Driver object
   * @param[in] ledDriver the chosen ledDriver object to be controlled using Hue Values
   */
  HueDriver(LEDDriver *ledDriver);
  /**
   * @brief Destroy the Hue Driver object
   *
   */
  ~HueDriver();
  /**
   * @brief Set the Hue object
   *
   * @param[in] hsb the new hsb
   */
  void setHue(HSB_t hsb);
  /**
   * @brief Get the Hue object
   * @return HSB_t the current hue state
   */
  HSB_t getHue(void);

private:
  LEDDriver *ledDriver;
  HSB_t currentHSB;
  /**
   * @brief Limiter Function, limits the values of hsb so that they are in the ranges specified earlier
   *
   * @param hsb
   */
  void convertLimits(HSB_t *hsb);
  /**
   * @brief Performs a constraint on the value so they dont go outside the limits specified
   *
   * @param value the value to be constrained
   * @param minValue minimum constraint
   * @param maxValue maximum constraint
   */
  void limiter(float *value, float minValue, float maxValue);
};

#endif