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
#ifndef __MAIN_H__
#define __MAIN_H__

#define MCU_CHOICE 0

// Library Includes
using namespace std;
#include <vector>
// System Includes
#include "LEDDriver.h"
#include "HueDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"

// External variables
extern vector<LEDDriver *> leds;
extern vector<RGBColourDriver *> stripDrivers;
extern vector<FadeDriver *> fadeDrivers;
extern vector<HueDriver *> hueDrivers;
#endif //__MAIN_H__