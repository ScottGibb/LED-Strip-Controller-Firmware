
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
#define __MAIN_H__

//Library Includes
#include <Arduino.h>

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

//Extyernal variables
extern ColourDriver *stripOneDriver;
extern FadeDriver *stripOneFadeDriver;
extern ColourDriver *stripTwoDriver;
extern FadeDriver *stripTwoFadeDriver;
extern ColourDriver *stripThreeDriver;
extern FadeDriver *stripThreeFadeDriver;
extern ButtonsDriver *buttonsDriver;
#endif __MAIN_H__