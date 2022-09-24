#ifndef __MAIN_H__
#define __MAIN_H__

//Library Includes
#include <Arduino.h>

//System Includes
#include "Channels.h"
#include "StatusIndicator.h"
#include "LEDDriver.h"
#include "ColourDriver.h"
#include "FadeDriver.h"
#include "CommsParser.h"


//External Method Headers
extern void setup(void);
extern void loop(void);

//Extyernal variables
extern ColourDriver *stripOneDriver;
extern FadeDriver *stripOneFadeDriver;
extern ColourDriver *stripTwoDriver;
extern FadeDriver *stripTwoFadeDriver;
extern ColourDriver *stripThreeDriver;
extern FadeDriver *stripThreeFadeDriver;
#endif __MAIN_H__