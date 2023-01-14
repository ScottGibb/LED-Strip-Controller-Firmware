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

// Library Includes
using namespace std;

// System Includes
#include "Channels.h"
#include "Buttons.h"
#include "StatusIndicator.h"
#include "LEDDriver.h"
#include "HueDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "CommsParser.h"
#include "ButtonsDriver.h"
#include "ButtonHandler.h"
#include "FanController.h"
#include "PowerMonitor.h"
#include "PowerSensors.h"

// External Function Prototypes
extern void setup(void);
extern void loop(void);

// External variables
extern LEDDriver * leds;
extern RGBColourDriver * stripDrivers;
extern FadeDriver * fadeDrivers;
extern HueDriver * hueDrivers;
#endif //__MAIN_H__