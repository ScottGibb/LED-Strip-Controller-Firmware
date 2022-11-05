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

//System Includes
#include "Channels.h"
#include "Buttons.h"
#include "StatusIndicator.h"
#include "LEDDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "CommsParser.h"
#include "ButtonsDriver.h"
#include "ButtonHandler.h"

//External Function Prototypes
extern void setup(void);
extern void loop(void);

//External variables
extern RGBColourDriver *stripOneDriver;
extern FadeDriver *stripOneFadeDriver;
extern RGBColourDriver *stripTwoDriver;
extern FadeDriver *stripTwoFadeDriver;
extern RGBColourDriver *stripThreeDriver;
extern FadeDriver *stripThreeFadeDriver;
extern ButtonsDriver *buttonsDriver;
#endif  //__MAIN_H__