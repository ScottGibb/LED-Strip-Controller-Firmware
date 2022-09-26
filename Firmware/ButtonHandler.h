#ifndef __BUTTON_HANDLER_H__
#define __BUTTON_HANDLER_H__

#include "ButtonsDriver.h"
#include "Main.h"

//external Prototypes
extern void buttonOneFunction(void);
extern void buttonTwoFunction(void);
extern void buttonThreeFunction(void);
extern void buttonFourFunction(void);
extern void toggleButtonLogic(uint8_t *brightness, FadeState *state, ColourDriver *colDriver, FadeDriver *fadeDriver);

extern uint8_t NUM_BUTTONS;
extern uint32_t buttonPins[];
extern func_type functions[];

#endif
