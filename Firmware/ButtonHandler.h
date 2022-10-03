/**
 * @file ButtonHandler.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Button Handler Source Implemetnation File
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

//Project Includes
#include "ButtonsDriver.h"
#include "Main.h"

//External Variables
extern uint8_t NUM_BUTTONS;
extern uint32_t buttonPins[];
extern func_type functions[];

//External Function Prototypes
extern void buttonOneFunction(void);
extern void buttonTwoFunction(void);
extern void buttonThreeFunction(void);
extern void buttonFourFunction(void);
extern void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver);

#endif
