#ifndef __BUTTONS_DRIVER_H__
#define __BUTTONS_DRIVER_H__

#include <stdint.h>
#include <Arduino.h>

typedef void (*func_type)(void);

class ButtonsDriver{

  private:
  uint32_t *buttonPins;
  uint8_t numButtons;
  uint32_t *lastDebounceTimes;
  int *buttonStates;
  int *lastButtonStates;
  const uint32_t MAX_DEBOUNCE_TIME = 50;
  func_type *functions;

public:
  ButtonsDriver( uint32_t *buttonPins,  uint8_t numButtons, func_type *funcs);
  ~ButtonsDriver();
  void loop(void);
};



#endif