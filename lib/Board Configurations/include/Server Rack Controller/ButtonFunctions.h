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
#ifndef BOARD_CONFIGURATIONS_INCLUDE_SERVER_RACK_CONROLLER_BUTTON_FUNCTIONS_H
#define BOARD_CONFIGURATIONS_INCLUDE_SERVER_RACK_CONROLLER_BUTTON_FUNCTIONS_H

// Project Includes
#include "ButtonsDriver.h"

// System Includes
#include <stdint.h>

// External Variables
extern const uint8_t NUM_BUTTONS;
extern const uint32_t buttonPins[];
extern const func_type functions[];

// External Function Prototypes

/**
 * @brief Button One Logic
 *
 */
extern void buttonOneFunction(void);
/**
 * @brief Button Two Logic
 *
 */
extern void buttonTwoFunction(void);
/**
 * @brief Button Three Logic
 *
 */
extern void buttonThreeFunction(void);
/**
 * @brief Button Four Logic
 *
 */
extern void buttonFourFunction(void);

#endif // BUTTON_FUNCTIONS_H