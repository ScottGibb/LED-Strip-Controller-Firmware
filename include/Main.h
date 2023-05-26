/**
 * @file Main.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Main Header file
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MAIN_H
#define MAIN_H

// System Includes
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "HueDriver.h"
#include "LEDDriver.h"

// Library Includes
#include <vector>
using namespace std;

/**
 * @brief Select the MCU Used in the Design
 *
 */
#define MCU_CHOICE 0

// External variables
extern vector<LEDDriver *> leds;
extern vector<RGBColourDriver *> stripDrivers;
extern vector<FadeDriver *> fadeDrivers;
extern vector<HueDriver *> hueDrivers;
#endif // MAIN_H