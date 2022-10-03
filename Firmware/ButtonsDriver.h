#ifndef __BUTTONS_DRIVER_H__
#define __BUTTONS_DRIVER_H__

//Library Includes
#include <stdint.h>
#include <Arduino.h>

//Function Pointer
typedef void (*func_type)(void);

/**
 * @brief Buttons Driver Class
 * Class Declaration of Buttons Driver
 */
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