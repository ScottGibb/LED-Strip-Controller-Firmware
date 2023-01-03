/**
 * @file CommsParser.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief CommsParser Header File for used with UART communication over USB
 * @version 0.1
 * @date 2022-10-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __COMMS_PARSER_H__
#define __COMMS_PARSER_H__

// Library Includes
#include <stdint.h>

// Project Includes
#include "CommsStructures.h"

// External Function Prototypes
extern void setupComms(void);
extern void commsLoop(void);

#endif