#ifndef __STATUS_INDICATOR_H__
#define __STATUS_INDICATOR_H__

//Library Includes
#include <stdint.h>
//Project Includes
#include "Pins.h"

const uint32_t REFRESH_PERIOD = 200;


extern void setupStatusIndicator(void);
extern void statusIndicatorLoop(void);






#endif