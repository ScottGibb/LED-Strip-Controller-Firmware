/**
 * @file StatusIndicator.h
 * @author Scott Gibb (smgibb@yahoo.com)
 * @brief Header file associated with Status Indicator logic
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __STATUS_INDICATOR_H__
#define __STATUS_INDICATOR_H__

//Library Includes
#include <stdint.h>
#include <Arduino.h>
//Project Includes
#include "Channels.h"

//External Function Prototypes
extern void setupStatusIndicator(void);
extern void statusIndicatorLoop(void);


#endif