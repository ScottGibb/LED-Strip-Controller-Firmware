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
#include "HueDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "CommsParser.h"
#include "ButtonsDriver.h"
#include "ButtonHandler.h"

//External Function Prototypes
extern void setup(void);
extern void loop(void);

//External variables
extern LEDDriver *ledOne;
extern RGBColourDriver *stripOneDriver;
extern HueDriver *stripOneHueDriver;
extern FadeDriver *stripOneFadeDriver;

extern LEDDriver *ledTwo;
extern RGBColourDriver *stripTwoDriver;
extern FadeDriver *stripTwoFadeDriver;
extern HueDriver *stripTwoHueDriver;

extern LEDDriver *ledThree;
extern RGBColourDriver *stripThreeDriver;
extern FadeDriver *stripThreeFadeDriver;
extern ButtonsDriver *buttonsDriver;
extern HueDriver *stripThreeHueDriver;

#endif  //__MAIN_H__